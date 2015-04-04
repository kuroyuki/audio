#ifndef AUDIORECOGNITION_H
#define AUDIORECOGNITION_H

#include <QObject>
#include <QTimer>
#include <QTextStream>

#include "dojo/dojo.h"

#define PI 3.14159265

class audioRecognition : public QObject
{
    Q_OBJECT
public:
    explicit audioRecognition(QObject *parent = 0);
    void start();

signals:

public slots:
    void updateValues();
private :
    dojo* recognition;

    float inputValue1, inputValue2;
    float outputValue;

    QTimer* timer;
    int timeStamp;

    QTextStream* stream;

    //
    float out;

};

#endif // AUDIORECOGNITION_H
