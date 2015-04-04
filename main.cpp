#include <QCoreApplication>
#include "audiorecognition.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    audioRecognition app;
    app.start();
    return a.exec();
}
