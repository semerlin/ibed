#include "AudioPlay.h"
#include <QFile>

/* wav文件头结构体 */
struct WAV_HEADER
{
    char rld[4]; //riff 标志符号
    int rLen;
    char wld[4]; //格式类型（wave）
    char fld[4]; //"fmt"

    int fLen; //sizeof(wave format matex)

    short wFormatTag; //编码格式
    short wChannels; //声道数
    int nSamplesPersec ; //采样频率
    int nAvgBitsPerSample;//WAVE文件采样大小
    short wBlockAlign; //块对齐
    short wBitsPerSample; //WAVE文件采样大小

    char dld[4]; //”data“
    int wSampleLength; //音频数据的大小
};

CAudioPlay::CAudioPlay()
{
    m_nDataBlock = 0;
    frames = 0;
    handle = 0;
    params = 0;
    m_buffer = 0;
    BUF_SIZE = 0;
    m_name = "";
    m_bLocal = false;
    m_alsa_can_pause = 0;
    m_isPlaying = false;
}
CAudioPlay::~CAudioPlay()
{
    quit();
    wait();

    snd_pcm_hw_params_free(params);
    snd_pcm_close(handle);
}
/********************************************************************************
* 函数: int CAudioPlay::AudioInit(void)
* 描述: 音频初始化
* 输入: none
* 输出: none
* 返回: 初始化结果
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
int CAudioPlay::AudioInit(const QString &name)
{
    int rc;

    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
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

    GetAudioType(name);
    m_name = name;
    m_alsa_can_pause = snd_pcm_hw_params_can_pause(params);
//    m_buffer = (char*)malloc((m_nDataBlock * frames));
//    BUF_SIZE = m_nDataBlock * frames;

    //系统音量设置
    snd_mixer_open(&mixer, 0);
    snd_mixer_attach(mixer, "default");
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    pcm_element = snd_mixer_first_elem(mixer);
    pcm_element = snd_mixer_elem_next(pcm_element);

    snd_mixer_selem_set_playback_volume_range(pcm_element, 0, 20);

    snd_mixer_selem_set_playback_volume(pcm_element, SND_MIXER_SCHN_FRONT_LEFT, 20);
    snd_mixer_selem_set_playback_volume(pcm_element, SND_MIXER_SCHN_FRONT_RIGHT, 20);

//    start();

    return 0;
}
/********************************************************************************
* 函数: int CAudioPlay::GetAudioType(const char *name)
* 描述: 获取文件头
* 输入: none
* 输出: none
* 返回: 获取结果
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
int CAudioPlay::GetAudioType(const QString &name)
{
    int rc;
    FILE *fp;
    WAV_HEADER wav_header;

    fp = fopen(name.toLatin1().data(), "rb");
    if(fp == NULL)
    {
        perror("open file failed:\n");
        return 1;
    }

    fread(&wav_header, 1, sizeof(wav_header), fp);
    fclose(fp);

    int channels = wav_header.wChannels;
    int frequency = wav_header.nSamplesPersec;
    int bit = wav_header.wBitsPerSample;
    m_nDataBlock = wav_header.wBlockAlign;
    unsigned int val;
    int dir = 0;

    //采样位数
    switch(bit / 8)
    {
    case 1:
        rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_U8);
        if(rc < 0)
        {
            perror("snd_pcm_hw_params_set_format:\n");
            return -1;
        }
        break;
    case 2:
        rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
        if(rc < 0)
        {
            perror("snd_pcm_hw_params_set_format:\n");
            return -1;
        }
        break;
    case 3:
        rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S24_LE);
        if(rc < 0)
        {
            perror("snd_pcm_hw_params_set_format:\n");
            return -1;
        }
        break;
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

    return 0;
}
/********************************************************************************
* 函数: void CAudioPlay::StartPlayNet(QByteArray datagram)
* 描述: 开始网络播放
* 输入: 网络数据数组
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::StartPlayNet(QByteArray datagram)
{
//    int length = 0;
//    int cnt = 0;

//    length = datagram.size();
//    while(length > 0)
//    {
//        if(length / BUF_SIZE > 0)
//        {
//            for(int i = 0; i < BUF_SIZE; i++)
//            {
//                m_buffer[i] = datagram[i + cnt * BUF_SIZE];
//            }
//            WriteData(m_buffer, frames);

//            length -= BUF_SIZE;
//            cnt++;
//        }
//        else
//        {
//            for(int i = 0; i < length; i++)
//            {
//                m_buffer[i] = datagram[i + cnt * BUF_SIZE];
//            }
//            WriteData(m_buffer, (length / m_nDataBlock));

//            length = 0;
//            cnt = 0;
//        }
//    }

    WriteData(datagram.data(), datagram.size());
}
/********************************************************************************
* 函数: void CAudioPlay::StartPlayLocal(void)
* 描述: 开始本地播放
* 输入: 文件名
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::StartPlayLocal(void)
{
    StartPlay();
    start();
    m_bLocal = true;
    m_isPlaying = true;
}

bool CAudioPlay::isPlaying() const
{
    return m_isPlaying;
}
/********************************************************************************
* 函数: void CAudioPlay::run()
* 描述: 线程执行函数
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::run()
{
    FILE *fp;
    int size = frames * m_nDataBlock;
    char buffer[size];

    fp = fopen(m_name.toLatin1().data(), "rb");
    if(fp == NULL)
    {
        perror("open file failed:\n");
    }
    fseek(fp, 44, SEEK_SET); //定位歌曲到数据区
    while((fread(buffer, 1, size, fp) != 0) && (m_bLocal == true))
    {
        WriteData(buffer, frames);
        msleep(1);
    }
    fclose(fp);
//    StopPlay();

    //    QFile file(name);
    //    if(!file.open(QIODevice::ReadOnly))
    //    {
    //        qDebug()<<file.errorString()<<endl;
    //    }
    //    file.seek(44);
    //    QByteArray(datagram) = file.readAll();
    //    file.close();

    //    WriteData(datagram.data(), datagram.size());
}
/********************************************************************************
* 函数: int CAudioPlay::WriteData(void *buffer, int size)
* 描述: 写数据
* 输入: none
* 输出: none
* 返回: 写入结果
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::WriteData(char *buffer, int size)
{
    if(snd_pcm_state(handle) != SND_PCM_STATE_DISCONNECTED)
    {
        int ret;

        while((ret = snd_pcm_writei(handle, buffer, size)) < 0)
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
* 函数: void CAudioPlay::StopPlay(void)
* 描述: 停止播放
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::StopPlay(void)
{
    if(m_bLocal == true)
    {
        m_bLocal = false;
        wait();
    }

    snd_pcm_drop(handle);
    m_isPlaying = false;
//    handle = NULL;

//    free(m_buffer);
}
/********************************************************************************
* 函数: void CAudioPlay::StartPlay(void)
* 描述: 开始播放
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::StartPlay(void)
{
    snd_pcm_prepare(handle);
}
/********************************************************************************
* 函数: void CAudioPlay::PausePlay(void)
* 描述: 暂停播放
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::PausePlay(void)
{
    if(m_bLocal == true)
    {
        m_bLocal = false;
        quit();
        wait();
    }

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
* 函数: void CAudioPlay::ResumePlay(void)
* 描述: 继续播放
* 输入: none
* 输出: none
* 返回: none
* 作者: zcj
* 版本: V1.0
**********************************************************************************/
void CAudioPlay::ResumePlay(void)
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
