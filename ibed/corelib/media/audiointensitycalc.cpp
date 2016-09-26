#include "audiointensitycalc.h"
#include "qmath.h"
#include "math.h"
#include <QVector>
#include "bitops.h"

static int BitReverse(int j, int nu)
{
    int j2;
    int j1 = j;
    int k = 0;
    for (int i = 1; i <= nu; i++)
    {
        j2 = j1 / 2;
        k = 2 * k + j1 - 2 * j2;
        j1 = j2;
    }

    return k;
}

static QVector<double> FFTDb(const QVector<double> &source)
{
    int sourceLen = source.size();
    int nu = (int)(qLn(sourceLen) / qLn(2));
    int halfSourceLen = sourceLen / 2;
    int nu1 = nu - 1;
    QVector<double> xre;
    QVector<double> xim;
    QVector<double> decibel;
    xre.resize(sourceLen);
    xim.resize(sourceLen);
    decibel.resize(halfSourceLen);
    double tr, ti, p, arg, c, s;
    for (int i = 0; i < sourceLen; i++)
    {
        xre[i] = source[i];
        xim[i] = 0.0f;
    }
    int k = 0;
    for (int l = 1; l <= nu; l++)
    {
        while (k < sourceLen)
        {
            for (int i = 1; i <= halfSourceLen; i++)
            {
                p = BitReverse(k >> nu1, nu);
                arg = 2 * (double)M_PI * p / sourceLen;
                c = (double)qCos(arg);
                s = (double)qSin(arg);
                tr = xre[k + halfSourceLen] * c + xim[k + halfSourceLen] * s;
                ti = xim[k + halfSourceLen] * c - xre[k + halfSourceLen] * s;
                xre[k + halfSourceLen] = xre[k] - tr;
                xim[k + halfSourceLen] = xim[k] - ti;
                xre[k] += tr;
                xim[k] += ti;
                k++;
            }
            k += halfSourceLen;
        }
        k = 0;
        nu1--;
        halfSourceLen = halfSourceLen / 2;
    }
    k = 0;
    int r;
    while (k < sourceLen)
    {
        r = BitReverse(k, nu);
        if (r > k)
        {
            tr = xre[k];
            ti = xim[k];
            xre[k] = xre[r];
            xim[k] = xim[r];
            xre[r] = tr;
            xim[r] = ti;
        }
        k++;
    }
    for (int i = 0; i < sourceLen / 2; i++)
    {
        decibel[i] = 10.0 * log10((float)(qSqrt((xre[i] * xre[i]) + (xim[i] * xim[i]))));
    }

    return decibel;
}


AudioIntensityCalc::AudioIntensityCalc()
{

}

int AudioIntensityCalc::calcIntensity(const QByteArray &data)
{
    QVector<double> wave;
    wave.resize(data.size() / 2);
    int h = 0;
    qint16 tempVal = 0;
    for (int i = 0; i < wave.size(); i += 2)
    {
        tempVal = (data.at(i + 1) & 0xff);
        tempVal <<= 8;
        tempVal += (data[i] & 0xff);
        wave[h] = (double)(tempVal); //采样位数为16bit
        ++h;
    }

    double sum = 0.0;
    QVector<double> sound = FFTDb(wave);
    foreach(const double &data, sound)
    {
        sum += data;
    }

    int val = sum / sound.size();

    return val;
}

void AudioIntensityCalc::getIntensity(const QByteArray &data)
{
    QByteArray calData = data;
    int size = calData.size();
    quint32 hweight = Bitops::generic_hweight32(size);
    if(hweight == 0)
        return ;
    else if(hweight == 1)
    {
        emit intensityChanged(calcIntensity(calData));
    }
    else
    {
        //get first 1 pos
        quint32 realSize = 1 << (Bitops::generic_fls(size) - 1);
        calData.remove(realSize, size - realSize);

        emit intensityChanged(calcIntensity(calData));
    }
}

