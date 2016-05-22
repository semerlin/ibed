#include "simplestatemachine.h"
#include "log4qt/logger.h"
#include <set>
#include <iostream>
#include <QMetaMethod>
#include <QDebug>
#include <QSet>
#include <QVariant>


LOG4QT_DECLARE_STATIC_LOGGER(log,SimpleStateMachine)

/**
 * @brief statemachine transition description
 */
struct TransitionDescription
{
    QString source;  //source state
    QString event;  //event to trigger state transtions
    QString condition;  //transition condition
    QString target;  //target state
    QString action;  //callback function before enter target state
    QString leaveCallback;  //callback function after leave source state
};


SimpleStateMachine::SimpleStateMachine(QObject *callee, const QString& initState) :
    m_callee(callee)
{
    Q_ASSERT_X(callee, "SimpleStateMachine::SimpleStateMachine",
                       "callee can not be null");
    setInitState(initState);
}

        
void SimpleStateMachine::setInitState(const QString &initState)
{
    m_initState = initState;
    //expand transitionTable
    m_transitionTable[m_initState];
}

void SimpleStateMachine::addTransition(const QString &source,
                                       const SimpleStateMachine::Transition &transition)
{

    m_transitionTable[source].push_back(transition);
    //expand transitionTable
    m_transitionTable[transition.target];
}

static void string2Method(const QString &string, boost::shared_ptr<QMetaMethod> &method,
                          const QMetaObject* metaObject, const QString &extra = "")
{
    if(string.isEmpty())
    {
        return;
    }

    QString sig = string + extra;

    int index = metaObject->indexOfMethod(QMetaObject::normalizedSignature(
                            sig.toAscii().constData()));

    Q_ASSERT_X(index != -1,"string2Struct",
              ("no such method :"+sig).toAscii().constData());

    method = boost::shared_ptr<QMetaMethod>(new QMetaMethod(metaObject->method(index)));
}

static SimpleStateMachine::Transition string2Struct(
        const TransitionDescription &transDesc,
        const QMetaObject *metaObject)
{

    SimpleStateMachine::Transition ret;

    ret.target = transDesc.target;
    ret.event = transDesc.event;

    string2Method(transDesc.condition, ret.condition, metaObject, "()");

    string2Method(transDesc.action, ret.action, metaObject, "(QString,QString)");

    string2Method(transDesc.leaveCallback, ret.leaveCallback, metaObject, "()");

    return ret;
}

static TransitionDescription parseOneLine(const QString &oneLine)
{
    //Init+beginEdit[onSomeItem]=Edit/OnEntry&OnExit
    //  ~~^~~    ~~~^~~~    ~~~~^~ ~~^~~   ~^~~~
    //  plus   cond(optional)  equal  slash  ampersand
    //src   event     condition  target  action   leaveCallback

    int plusPos = oneLine.indexOf('+');

    Q_ASSERT_X(plusPos != -1,"parseOneLine", "'+' not found!");

    TransitionDescription ret;

    //source state
    ret.source = oneLine.left(plusPos);

    int equalPos = oneLine.indexOf('=');

    Q_ASSERT_X(equalPos != -1,"parseOneLine", "'=' not found");

    QString rightPart = oneLine.right(oneLine.length() - equalPos - 1);

    Q_ASSERT_X(equalPos > plusPos + 1,"parseOneLine", "bad form, '+' pos > '=' pos");

    QString eventAndCond = oneLine.mid(plusPos + 1, equalPos - plusPos - 1);

    int leftSquareBracketPos = eventAndCond.indexOf('[');

    if(leftSquareBracketPos == -1)
    {
        ret.event=eventAndCond;
    }
    else
    {
        int rightSquareBracketPos = eventAndCond.indexOf(']');
        Q_ASSERT_X(rightSquareBracketPos != -1,"parseOneLine",
                "condition bracket not match");

        Q_ASSERT_X(rightSquareBracketPos > leftSquareBracketPos + 1,"parseOneLine",
                "bad form, rightSquare Bracket Pos > left SquareBracket Pos ");

        ret.event = eventAndCond.left(leftSquareBracketPos);
        ret.condition = eventAndCond.mid(leftSquareBracketPos + 1,
                rightSquareBracketPos - leftSquareBracketPos - 1);

    }


    int slashPos = rightPart.indexOf('/');
    int ampPos = rightPart.indexOf('&');

    bool hasAction = (slashPos != -1),
         hasLeaveCallback = (ampPos != -1);

    if(hasAction && hasLeaveCallback)
    {
        Q_ASSERT_X(slashPos < ampPos, "parseOneLine",
                "'/' pos should appear before '&' pos");
    }

    int targetEndPos = (hasAction ? slashPos :
                       (hasLeaveCallback ? ampPos :
                        rightPart.length()));

    ret.target = rightPart.left(targetEndPos);

    int actionEndPos = (hasLeaveCallback ? ampPos : rightPart.length());

    if(hasAction)
    {
        ret.action = rightPart.mid(slashPos + 1, actionEndPos - slashPos - 1);
        if(ret.action.isEmpty())
        {
            ret.action = "Enter" + ret.target;
        }
    }

    if(hasLeaveCallback)
    {
        ret.leaveCallback = rightPart.right(rightPart.length() - ampPos - 1);
        if(ret.leaveCallback.isEmpty())
        {
            ret.leaveCallback = "Leave" + ret.source;
        }
    }

    return ret;
}
void SimpleStateMachine::parseAddition(const char **desc, int lineNumber){

    for(int i = 0; i < lineNumber; ++i)
    {
        parseAddition(desc[i]);
    }
}

void SimpleStateMachine::parseAddition(const char *oneLine)\
{
    TransitionDescription transDesc = parseOneLine(oneLine);

    Transition transition = string2Struct(transDesc, m_callee->metaObject());

    addTransition(transDesc.source, transition);
}


const SimpleStateMachine::TransitionList& SimpleStateMachine::assertFind(const QString &str)
{
    Q_ASSERT_X(!(str.isEmpty()||str.isNull()),
            "SimpleStateMachine::assertFind",
            "current state is NULL or empty, maybe not call enterStateMachine?");

    Q_ASSERT_X(m_transitionTable.contains(str),
            "SimpleStateMachine::assertFind",
            QString("state not found:'"+str+"'").toAscii().constData());

    return m_transitionTable[str];
}



static const QString DUMMY_EVENT("dummy");

class EventFinder
{
public:
    EventFinder(const QString &str = DUMMY_EVENT) :
        toFind(str)
    {

    }

public:
    bool operator()(const SimpleStateMachine::Transition& transition)
    {
        return transition.event == toFind;
    }

private:
    QString toFind;
};

bool SimpleStateMachine::postEvent(const QString &event)
{
    const TransitionList &currentList = assertFind(m_currentState);

    TransitionList::const_iterator findBegin = currentList.begin(),
                                   findEnd = currentList.end();

    for(;;)
    {
        TransitionList::const_iterator transitionPos =
            std::find_if(findBegin, findEnd, EventFinder(event));

        if(transitionPos == findEnd)
        {
            return false;
        }

        bool result = executeTransition(*transitionPos);

        //may condition false
        if(result)
        {
            return true;
        }


        findBegin = transitionPos;
        ++findBegin;
    }

    return false;
}

bool SimpleStateMachine::executeTransition(const SimpleStateMachine::Transition &transition)
{
    log()->debug("executeTransition: %1+%2=%3",
                 m_currentState, transition.event, transition.target);

    bool conditionValue = false;

    //condition test
    if(transition.condition)
    {
        transition.condition->invoke(m_callee, Qt::DirectConnection,
                                     Q_RETURN_ARG(bool, conditionValue));

        log()->debug("test condition: %1 = %2",
                     transition.condition->signature(), conditionValue);

        if(!conditionValue)
        {
            return false;
        } 
    }

    //call leave callback function
    if(transition.leaveCallback)
    {
        log()->debug("leaveCallback: %1 ", transition.leaveCallback->signature());

        transition.leaveCallback->invoke(m_callee, Qt::DirectConnection);
    }

    //call enter new state function
    if(transition.action)
    {
        transition.action->invoke(m_callee, Qt::DirectConnection,
                                  Q_ARG(QString,m_currentState),
                                  Q_ARG(QString,transition.target));

        log()->debug("action: %1", transition.action->signature());

    }

    m_prevState = m_currentState;
    m_currentState = transition.target;

    return true;
}

void SimpleStateMachine::enterStateMachine()
{
    m_currentState = m_initState;
    m_prevState = m_initState;
    Q_ASSERT(checkReachability());
    postEvent(DUMMY_EVENT);
}

void SimpleStateMachine::reset()
{
    m_currentState = m_initState;
    m_prevState = m_initState;
}


static void recursiveReach(const QString &state,
                           const SimpleStateMachine::TransitionTableType &table,
                           QSet<QString> &canReach){

    if (canReach.find(state) != canReach.end())
    {
        //already reached
        return;
    }

    canReach.insert(state);

    foreach(const SimpleStateMachine::Transition &trans, table.value(state))
    {
        recursiveReach(trans.target, table, canReach);
    }
}

static QString setToString(const QSet<QString> &toConvert)
{
    QString ret = "QSet(";

    foreach(const QString &str, toConvert)
    {
        ret += str;
        ret.append(',');
    }

    ret.resize(ret.size() - 1);

    ret += ")";

    return ret;
}

bool SimpleStateMachine::checkReachability()
{
    QSet<QString> canReach;

    recursiveReach(m_initState, m_transitionTable, canReach);

    QSet<QString> uniqueKeys = QSet<QString>::fromList(m_transitionTable.uniqueKeys());

    uniqueKeys.subtract(canReach);

    if(!uniqueKeys.isEmpty())
    {
        log()->error("these state can not be reached: %1",
                     setToString(uniqueKeys));
    
        Q_ASSERT_X(false, "SimpleStateMachine::checkReachability",
                   "not all state can be reached,");
    }

    return true;
}


