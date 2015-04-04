#include "dojostructs.h"
#include <QJsonArray>
#include <QHashIterator>

dojoParams::dojoParams(){
    interval = 10;
    size = QVector3D(1,1,1);
}
//
//import/export functions
//
void dojoParams::fromJson(QJsonObject json){
    //restore dojo config
    name = json.take("name").toString();
    interval = json.take("interval").toDouble();

    QJsonObject sizeJson = json.take("size").toObject();
    size.setX(sizeJson.take("x").toDouble());
    size.setY(sizeJson.take("y").toDouble());
    size.setZ(sizeJson.take("z").toDouble());

    //restore nodes
    QJsonArray nodesArray = json.take("nodes").toArray();
    for(int i=0;i<nodesArray.size();i++){
        QJsonObject nodeJson = nodesArray.at(i).toObject();
        dojoNodeParams node;
        node.fromJson(nodeJson);
        nodes.append(node);
    }
    //restore synapses
    QJsonArray synArray = json.take("synapses").toArray();
    for(int i=0;i<synArray.size();i++){
        QJsonObject synJson = synArray.at(i).toObject();
        dojoSynapseParams syn;
        syn.fromJson(synJson);
        synapses.append(syn);
    }
    //restore labels
    QJsonArray labArray = json.take("labels").toArray();
    for(int i=0;i<labArray.size();i++){
        QJsonObject labJson = labArray.at(i).toObject();
        labels[labJson.take("label").toString()] = labJson.take("id").toDouble();
    }
}
QJsonObject dojoParams::toJson(){
    QJsonObject configJson;
    configJson.insert("name", name);
    configJson.insert("interval", (double)interval);
    QJsonObject sizeJson;
    sizeJson.insert("x", size.x());
    sizeJson.insert("y", size.y());
    sizeJson.insert("z", size.z());
    configJson.insert("size", sizeJson);

    QJsonArray nodesArray;
    for(int i=0;i<nodes.length();i++){
        nodesArray.append(nodes[i].toJson());
    }
    configJson.insert("nodes", nodesArray);

    QJsonArray synArray;
    for(int i=0;i<synapses.length();i++){
        synArray.append(synapses[i].toJson());
    }
    configJson.insert("synapses", synArray);

    QJsonArray labArray;
    QHashIterator<QString, dojoID> i(labels);
    while (i.hasNext()) {
        i.next();

        QJsonObject labJson;
        labJson.insert("label", i.key());
        labJson.insert("id", (double)i.value());

        labArray.append(labJson);
    }
    configJson.insert("labels", labArray);

    return configJson;
}

QJsonObject dojoNodeParams::toJson(){
    QJsonObject json;
    json.insert("id", (float)id);

    QJsonObject positionJson;
    positionJson.insert("x", position.x());
    positionJson.insert("y", position.y());
    positionJson.insert("z", position.z());
    json.insert("position", positionJson);
    json.insert("size", size);

    QJsonObject vectorJson;
    vectorJson.insert("x", vector.x());
    vectorJson.insert("y", vector.y());
    vectorJson.insert("z", vector.z());
    json.insert("vector", vectorJson);

    QJsonObject axonJson;
    axonJson.insert("x", axon.x());
    axonJson.insert("y", axon.y());
    axonJson.insert("z", axon.z());
    json.insert("axon", axonJson);

    json.insert("radius", (float)dendriteRadius);

    return json;
}
void dojoNodeParams::fromJson(QJsonObject json){
    id = json.take("id").toInt();
    size = json.take("size").toDouble();

    QJsonObject positionJson = json.take("position").toObject();
    position.setX(positionJson.take("x").toDouble());
    position.setY(positionJson.take("y").toDouble());
    position.setZ(positionJson.take("z").toDouble());

    QJsonObject vectorJson = json.take("vector").toObject();
    vector.setX(vectorJson.take("x").toDouble());
    vector.setY(vectorJson.take("y").toDouble());
    vector.setZ(vectorJson.take("z").toDouble());

    QJsonObject axonJson = json.take("axon").toObject();
    axon.setX(axonJson.take("x").toDouble());
    axon.setY(axonJson.take("y").toDouble());
    axon.setZ(axonJson.take("z").toDouble());

    dendriteRadius = json.take("radius").toDouble();
}

QJsonObject dojoSynapseParams::toJson(){
    QJsonObject json;
    json.insert("source", (float)source);
    json.insert("target", (float)target);
    json.insert("terminals", (float)terminals);
    return json;
}

void dojoSynapseParams::fromJson(QJsonObject json){
     source = json.take("source").toInt();
     target = json.take("target").toInt();
     terminals = json.take("terminals").toInt();
}
//
//specific functions
//
QList<dojoID> dojoParams::getPointNeighbours(QVector3D forPoint, float atDistance){
    QList<dojoID> list;

    for(int i=0;i<nodes.size();i++){
        QVector3D diff = nodes[i].position - forPoint;
        if(diff.length() < (atDistance+(nodes[i].size/2)))
            list << nodes[i].id;

    }
    return list;
}
bool dojoParams::isSynapseExist(dojoID source, dojoID target){
    for(int i=0;i<synapses.size();i++){
        if(synapses[i].source == source && synapses[i].target == target)
            return true;
    }
    return false;
}
