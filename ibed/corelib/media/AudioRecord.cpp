#include "AudioRecord.h"

CAudioRecord::CAudioRecord()
{
    m_alsa_can_pause = 0;
}

CAudioRecord::~CAudioRecord()
{
    snd_pcm_hw_params_free(params);
    snd_pcm_close(handle);
}
/********************************************************************************
* 函数: void AudioRecord::InitAudioRecord(void)
* 描述: 初始化录音
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
int CAudioRecord::InitAudioRecord(void)
{
    int rc;
    int channels = 1;
    int frequency = 8000;
    unsigned int val;
    int dir = 0;

    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if(rc < 0)
    {
        perror("open PCM device failed:\n");
        return -1;
    }
    snd_pcm_hw_params_malloc(&params); //分配params结构体
    if(rc < 0)
    {
        perror("snd_pcm_hw_params_alloca:\n");
        return -1;
    }
    rc = snd_pcm_hw_params_any(handle, params);//初始化params
    if(rc < 0)
    {
        perror("snd_pcm_hw_params_any:\n");
        return -1;
    }
    rc = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED); //初始化访问权限
    if(rc < 0)
    {
        perror("snd_pcm_hw_set_access:\n");
        return -1;
    }
    rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_U8);//采样位数
    if(rc < 0)
    {
        perror("snd_pcm_hw_params_set_format:\n");
        return -1;
    }
    rc = snd_pcm_hw_params_set_channels(handle, params, channels); //设置声道,1表示单声>道，2表示立体声
    if(rc < 0)
    {
        perror("snd_pcm_hw_params_set_channels:\n");
        return -1;
    }
    val = frequency;
    rc = snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir); //设置频率
    if(rc < 0)
    {
        perror("snd_pcm_hw_params_set_rate_near:\n");
        return -1;
    }
    rc = snd_pcm_hw_params(handle, params);
    if(rc < 0)
    {
        perror("snd_pcm_hw_params:\n");
        return -1;
    }
    rc = snd_pcm_hw_params_get_period_size(params, &frames, &dir); //获取周期长度
    if(rc < 0)
    {
        perror("snd_pcm_hw_params_get_period_size:\n");
        return -1;
    }

    m_alsa_can_pause = snd_pcm_hw_params_can_pause(params);

    return 0;
}
/********************************************************************************
* 函数: void StartRecordNet(char *buffer, int size)
* 描述: 录音到网络
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioRecord::StartRecordNet(char *buffer, int size)
{
    ReadData(buffer, size);
}
/********************************************************************************
* 函数: void CAudioRecord::ReadData(char *buffer, int size)
* 描述: 读数据
* 输入: none
* 输出: none
* 返回: 写入结果
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioRecord::ReadData(char *buffer, int size)
{
    if(snd_pcm_state(handle) != SND_PCM_STATE_DISCONNECTED)
    {
        int ret;

        while((ret = snd_pcm_readi(handle, buffer, size)) < 0)
        {
            if(ret == -EPIPE)
            {
                /* EPIPE means underrun */
                //fprintf(stderr, "underrun occurred\n");
                //完成硬件参数设置，使设备准备好
                snd_pcm_prepare(handle);
            }
            else
            {
                fprintf(stderr, "error from writei: %s\n", snd_strerror(ret));
            }
        }
    }
}
/********************************************************************************
* 函数: void CAudioRecord::StopRecord(void)
* 描述: 停止录音
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioRecord::StopRecord(void)
{
    snd_pcm_drop(handle);
}
/********************************************************************************
* 函数: void CAudioRecord::StartRecord(void)
* 描述: 开始录音
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioRecord::StartRecord(void)
{
    snd_pcm_prepare(handle);
}
/********************************************************************************
* 函数: void AudioRecord::PauseRecord()
* 描述: 暂停录音
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioRecord::PauseRecord()
{
    if(m_alsa_can_pause)
    {
        snd_pcm_pause(handle, 1);
    }
    else
    {
        snd_pcm_drop(handle);
    }
}
/********************************************************************************
* 函数: void AudioRecord::ResumeRecord()
* 描述: 恢复录音
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioRecord::ResumeRecord()
{
    if(snd_pcm_state(handle) == SND_PCM_STATE_SUSPENDED)
    {
        while(snd_pcm_resume(handle) == -EAGAIN)
            sleep(1);
    }

    if(m_alsa_can_pause)
    {
        snd_pcm_pause(handle, 0);
    }
    else
    {
        snd_pcm_prepare(handle);
    }
}
/********************************************************************************
* 函数: void AudioRecord::run()
* 描述: 线程执行函数
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioRecord::run()
{

}
