#ifndef DOJO_H
#define DOJO_H

#include <QObject>
#include <QTimer>
#include <QHash>

#include "dojostructs.h"
#include "dojonode.h"

class dojo : public QObject
{
    Q_OBJECT
public:
    explicit dojo(QString str, QObject *parent = 0);
    void start();
    void bindInput(float* data, QString label);
    void bindOutput(QString label, float* data);    

private:
    void startNode(dojoNodeParams nodeParams);
    void bindNodes(dojoSynapseParams syn);

signals:

public slots:
    void processDojo();
private :

    QTimer timer;    

    QHash<dojoID, dojoNode*> nodeTable;

    dojoParams params;
    dojoID newNodeID;

    quint64 lifetime;
};

#endif // DOJO_H
