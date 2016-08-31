#ifndef AUDIOINTENSITYCALC_H
#define AUDIOINTENSITYCALC_H

#include <QObject>

class AudioIntensityCalc : public QObject
{
    Q_OBJECT

public:
    AudioIntensityCalc();

public:
    int calcIntensity(const QByteArray &data);

public slots:
    void getIntensity(const QByteArray &data);

signals:
    void intensityChanged(int val);
};

#endif // AUDIOINTENSITYCALC_H
