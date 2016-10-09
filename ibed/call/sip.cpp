#include "sip.h"
#include <pjsua-lib/pjsua.h>
#include <QTimer>
#include <QMetaType>

#define THIS_FILE "SIP"

CallState Sip::m_prevState = Idle;
CallState Sip::m_curState = Idle;
pjsua_call_id Sip::m_callId = 0;

Sip::Sip() :
    m_id(-1),
    m_domain(""),
    m_isRegistered(false),
    m_timer(new QTimer(this)),
    m_prev(Idle),
    m_cur(Idle)
{
    qRegisterMetaType<CallState>("CallState");
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    m_timer->start();
}

Sip::~Sip()
{
    pjsua_destroy();
}

bool Sip::init()
{
    pj_status_t status;

    /* Create pjsua first! */
    status = pjsua_create();
    if(status != PJ_SUCCESS)
        return false;

    /* Init pjsua */
    pjsua_config cfg;
    pjsua_logging_config log_cfg;
    pjsua_config_default(&cfg);

    cfg.cb.on_incoming_call = &onIncomingCall;
    cfg.cb.on_call_media_state = &onCallMediaState;
    cfg.cb.on_call_state = &onCallState;

    pjsua_logging_config_default(&log_cfg);
    log_cfg.console_level = 4;

    status = pjsua_init(&cfg, &log_cfg, NULL);

    if (status != PJ_SUCCESS)
        return false;


    /* Add UDP transport. */
    pjsua_transport_config trans_cfg;

    pjsua_transport_config_default(&trans_cfg);
    trans_cfg.port = 5060;
    status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &trans_cfg, NULL);
    if(status != PJ_SUCCESS)
        return false;

    /* Initialization is done, now start pjsua */
    status = pjsua_start();
    if(status != PJ_SUCCESS)
        return false;

    return true;
}

bool Sip::reg(const QString &name, const char *passwd, const QString &domain)
{
    m_isRegistered = false;
    pj_status_t status;

    m_domain = domain;
    /* Register to SIP server by creating SIP account. */
    pjsua_acc_config cfg;
    pjsua_acc_config_default(&cfg);
    char uri[PJSIP_MAX_URL_SIZE];

    //sip:name@address
    pj_ansi_snprintf(uri, PJSIP_MAX_URL_SIZE,
                  "sip:%s@%s", name.toLatin1().data(), domain.toLatin1().data());

    cfg.id = pj_str(uri);

    //server address
    //sip:address
    char reg_uri[PJSIP_MAX_URL_SIZE];
    pj_ansi_snprintf(reg_uri, PJSIP_MAX_URL_SIZE, "sip:%s", domain.toLatin1().data());

    cfg.reg_uri = pj_str(reg_uri);
    cfg.cred_count = 1;
    cfg.cred_info[0].realm = pj_str("*");
    cfg.cred_info[0].scheme = pj_str("digest");
    cfg.cred_info[0].username = pj_str(name.toLatin1().data());
    cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
//    cfg.cred_info[0].data = pj_str(passwd.toLatin1().data());
    cfg.cred_info[0].data = pj_str((char*)passwd);

    status = pjsua_acc_add(&cfg, PJ_TRUE, &m_id);

    if(status != PJ_SUCCESS)
        return false;

    m_isRegistered = true;
    return true;
}

//在minisipserver服务器上添加SIP账号，名称：101
//使用另外的客户端注册
//拨打101，命令格式：“sip:101@100.100.100.199”
int Sip::dial(const QString &num)
{
    if(!m_isRegistered)
       return -1;

    pj_status_t status;

    char tmp_uri[PJSIP_MAX_URL_SIZE];
    pj_ansi_snprintf(tmp_uri, PJSIP_MAX_URL_SIZE,
                     "sip:%s@%s",
                     num.toLatin1().data(), m_domain.toLatin1().data());

    /* If argument is specified, it's got to be a valid SIP URL */
    status = pjsua_verify_url(tmp_uri);
    if (status != PJ_SUCCESS)
        return -2;

    pj_str_t uri = pj_str(tmp_uri);

    status = pjsua_call_make_call(m_id, &uri, 0, NULL, NULL, NULL);
    if(status != PJ_SUCCESS)
        return -3;

    return 0;
}

void Sip::answer()
{
    /* Automatically answer incoming calls with 200/OK */
    pjsua_call_answer(m_callId, 200, NULL, NULL);
}

void Sip::hangup()
{
    pjsua_call_hangup_all();
}

void Sip::destroy()
{
    pjsua_destroy();
}

void Sip::reset()
{
    m_prev = Idle;
    m_prevState = Idle;
    m_cur = Idle;
    m_curState = Idle;
}

void Sip::onIncomingCall(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata)
{
    pjsua_call_info ci;

    PJ_UNUSED_ARG(acc_id);

    PJ_UNUSED_ARG(rdata);

    pjsua_call_get_info(call_id, &ci);

//    PJ_LOG(3, (THIS_FILE, "Incoming call from %.*s!!",

//    (int)ci.remote_info.slen,

//    ci.remote_info.ptr));

    m_prevState = m_curState;
    m_curState = static_cast<CallState>(ci.state);
    m_callId = call_id;
    /* Automatically answer incoming calls with 200/OK */
//    pjsua_call_answer(call_id, 200, NULL, NULL);
}

void Sip::onCallState(pjsua_call_id call_id, pjsip_event *e)
{
    pjsua_call_info ci;

    PJ_UNUSED_ARG(e);

    pjsua_call_get_info(call_id, &ci);

    m_prevState = m_curState;
    m_curState = static_cast<CallState>(ci.state);
}

void Sip::onCallMediaState(pjsua_call_id call_id)
{
    pjsua_call_info ci;

    pjsua_call_get_info(call_id, &ci);

    if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE) {

    // When media is active, connect call to sound device.

    pjsua_conf_connect(ci.conf_slot, 0);

    pjsua_conf_connect(0, ci.conf_slot);
    }
}

void Sip::onTimeOut()
{
    if((m_prev != m_prevState) || (m_cur != m_curState))
    {
        m_prev = m_prevState;
        m_cur = m_curState;
        emit stateChanged(m_prev, m_cur);
    }
}
