#ifndef DOJOSTRUCTS_H
#define DOJOSTRUCTS_H

#include <QString>
#include <QHash>
#include <QVector3D>
#include <QJsonObject>
#include <QJsonDocument>

typedef unsigned int dojoID;

class dojoNode;

struct dojoSynapseParams{
    dojoID source;
    dojoID target;

    float terminals;

    QJsonObject toJson();
    void fromJson(QJsonObject json);
};

struct dojoNodeParams{
    dojoID id;
    float size;
    QVector3D position;

    QVector3D vector;
    QVector3D axon;
    float dendriteRadius;

    QJsonObject toJson();
    void fromJson(QJsonObject json);
};

struct dojoParams{
    QString name;
    int interval;
    QVector3D size;

    QList<dojoNodeParams> nodes;
    QList<dojoSynapseParams>synapses;
    QHash<QString, dojoID>labels;

    dojoParams();
    void fromJson(QJsonObject configJson);
    QJsonObject toJson();

    QList<dojoID> getPointNeighbours(QVector3D forPoint, float atDistance);
    bool isSynapseExist(dojoID source, dojoID target);
};

#endif // DOJOSTRUCTS_H
