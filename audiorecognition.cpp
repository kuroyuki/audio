#include "audiorecognition.h"
#include "math.h"
#include <QTextStream>

audioRecognition::audioRecognition(QObject *parent) :
    QObject(parent)
{    
    //init dojo
    QString name = "audio";
    recognition = new dojo(name);
    //add input
    recognition->bindInput(&inputValue1, "audioInput");
    recognition->bindInput(&inputValue2, "audioInInput");

    //add output
    recognition->bindOutput("audioOutput", &outputValue);

    //init internal timer;
    timer = new QTimer();
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValues()));

    stream = new QTextStream(stdout);

    out = 0;

}
void audioRecognition::start(){
    //start dojo
    recognition->start();
    //start internal process
    timer->start();

    timeStamp = 0;
}
void audioRecognition::updateValues(){
    //update Input i=I*sin(2*PI*f*t+w)
    // I - amplitude, f - frequency, t - current time, w - phase
    float f = 1;
    float I = 0.5;
    float t = timeStamp*0.001;

    inputValue1 = 0.5+I*sin(2*PI*f*t);
    inputValue2 = 0.5+I*sin(2*PI*f*t+1);

    //use Output
    if(outputValue){
        *stream<<endl;
        *stream<<QString::number(timeStamp);
        outputValue = 0;
    }
    timeStamp += 10;    
}
