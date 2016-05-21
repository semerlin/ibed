#ifndef SIMPLESTATEMACHINE_H
#define SIMPLESTATEMACHINE_H

#include "framework_global.h"

#include <boost/shared_ptr.hpp>
#include <QString>
#include <QHash>


/**
 * @brief 简单的状态机
 *
 * 本实现:
 * event/state均基于String,引用一QObject作为实际执行者，
 * action 和 condition 直接调用QObject的对应名字函数
 * 使用一种简单的状态转换描述（参考Boost MSM eUML）
 * Source+event[condition]=Target/Action&LeaveCallback
 *
 *
 * 语法说明
 * 不允许有额外的空格，[condition]/Action&LeaveCallback可选
 * condition 将调用callee的condition函数
 *
 * Action 不存在但斜杠(slash)存在时，调用Enter${Target}()
 * /Action 存在时，Transition执行将调用callee.Action(fromState,toState)
 *
 * LeaveCallback 不存在但&存在时，调用Leave${Source}
 *
 * 例如：
 * Init+clik[onItem]=Select/CallbackAction&
 * 则接受到clik事件时，onItem()==true 将引发状态从Init->Select
 *
 * 调用Leave回调，此处未指定，则按照规则调用LeaveInit()
 *
 * 并调用CallbackAction("Init","Select")
 *
 *
 *
 * 状态转换时回调函数的调用时机
 *
 * 1 调用LeaveCallback
 * 2 调用Action(fromState,toState)
 * 3 状态转换完成
 *
 * 因此在LeaveCallback中，currentState为fromState
 * Action(fromState,toState)中,prevState为上次状态（比fromState更早）
 *
 *
 * 特殊的dummy event
 *
 * 在一些状态机初始化中，直接按照condition从Init进入特定状态会比较方便
 * dummy event即可完成此任务
 * 默认情况下，初始状态为Init
 *
 *
 * Debug模式下，若状态不可达或者condition/action不能调用，将引发断言
 *
 *        
 */
class FRAMEWORKSHARED_EXPORT  SimpleStateMachine
{
public:
    /**
     * @brief construct statemachine
     * @param callee
     */
    SimpleStateMachine(QObject * callee, const QString &initState = "Init");

    struct Transition
    {
        QString event;
        boost::shared_ptr<QMetaMethod> condition;
        boost::shared_ptr<QMetaMethod> action;
        boost::shared_ptr<QMetaMethod> leaveCallback;
        QString target;
    };

    typedef QList<Transition> TransitionList;

    /**
     * @brief one source may have more than one transtionlist.
     * for example:
     *     Init+event1=target1/
     *     Init+event2=target2/
     */
    typedef QHash<QString, TransitionList> TransitionTableType;

    /**
     * @brief current state
     * @return reference of current state
     */
    const QString& currentState() const
    {
        return m_currentState;
    }

    /**
     * @brief previous state
     * @return reference of previous state
     */
    const QString& prevState() const
    {
        return m_prevState;
    }

    /**
     * @brief add one transition
     * @param source: source state
     * @param transition: transtion desciption
     */
    void addTransition(const QString& source, const Transition& transition);

    /**
     * @brief parse addition
     * @param desc: transiton description
     * @param lineNumber: line number
     */
    void parseAddition(const char ** desc,int lineNumber);
    /**
     * @brief parse addition
     * @param oneLine: transition description
     */
    void parseAddition(const char* oneLine);

    /**
     * @brief post an event
     * @param event: event name
     * @return return true if it trigger any transition, otherwise false
     */
    bool postEvent(const QString& event);

    /**
     * @brief enter statemachine
     */
    void enterStateMachine();

    /**
     * @brief reset statemachine to the beginning state,
     *        no transtions will be triggered.
     */
    void reset();

private:
    /**
     * @brief set initial state
     * @param initState: initial state
     */
    void setInitState(const QString &initState);

    /**
     * @brief execute transtion
     * @param transition
     * @return
     */
    bool executeTransition(const Transition &transition);

    /**
     * @brief check if all QMetaObject functions can be invoked
     * @return true: check passed
     *         false: check failed
     */
    bool checkCallable();

    /**
     * @brief check to make sure that all state can be reached
     * @return
     */
    bool checkReachability();

    /**
     * @brief find a source's TransitionList, if not, an assert
     *        error will occured
     * @param source: source name
     * @return
     */
    const TransitionList& assertFind(const QString &source);

private:
    QObject *m_callee;
    QString m_initState;
    QString m_currentState;
    QString m_prevState;
    TransitionTableType m_transitionTable;
};


#endif /* SIMPLESTATEMACHINE_H */
