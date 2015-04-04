#include "dojo.h"
#include <QFile>

dojo::dojo(QString str, QObject *parent) :
    QObject(parent)
{
    params.name = str;

    QString fileName = params.name+".dojo";
    QFile file(fileName);
    if(!file.exists()){
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QJsonDocument jdoc(params.toJson());
        file.write(jdoc.toJson());
        file.close();
    }
    else {
        file.open(QIODevice::ReadWrite | QIODevice::Text);

        QJsonDocument jdoc;
        jdoc = QJsonDocument::fromJson(file.readAll());

        params.fromJson(jdoc.object());
    }

    //restore nodes
    for (int i = 0; i < params.nodes.size(); ++i) {
       startNode(params.nodes.at(i));
    }
    //restore synapses
    for (int i = 0; i < params.synapses.size(); ++i) {      
       dojoSynapseParams syn = params.synapses.at(i);
       if(nodeTable.contains(syn.source) && nodeTable.contains(syn.target)){
           dojoNode* sourceNode = nodeTable.value(syn.source);
           dojoNode* targetNode = nodeTable.value(syn.target);

           dojoChemicalSynapse* synapse = new dojoChemicalSynapse(sourceNode, targetNode, syn);
           sourceNode->addTarget(synapse);
           targetNode->addSource(synapse);
       }
    }
    newNodeID = params.nodes.size();

    lifetime = 0;
    //init timer
    timer.setInterval(params.interval);
    connect(&timer, SIGNAL(timeout()), this, SLOT(processDojo()));   
}
void dojo::start(){

    timer.start();
}
void dojo::processDojo(){    
    foreach (dojoNode* node, nodeTable)
         node->processNode();

    lifetime += params.interval;
    //each 1 sec
    if(lifetime%100 < params.interval){
        //save config
        QString fileName = params.name+".dojo";
        QFile file(fileName);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QJsonDocument jdoc(params.toJson());
        file.write(jdoc.toJson());
        file.close();
    }
    //each 10 sec
   if(lifetime%10000 < params.interval){
        //grow nodes
        foreach (dojoNode* node, nodeTable){
             QList<dojoID> newTargets = params.getPointNeighbours(node->getAxonPosition(), 5);
             for(int i=0;i<newTargets.length();i++){
                 dojoID source = node->getID();
                 dojoID target = newTargets[i];
                 if(source !=  target && !params.isSynapseExist(source, target)){
                     dojoSynapseParams newSyn;
                     newSyn.terminals = 1;
                     newSyn.source = source;
                     newSyn.target = target;
                     bindNodes(newSyn);
                 }
             }
        }
    }
}

void dojo::startNode(dojoNodeParams nodeParams){
    //creating node with the defined parameters
    dojoNode* newNode = new dojoNode(nodeParams);
    //save its pointer in local table
    nodeTable[nodeParams.id] = newNode;
}

void dojo::bindInput(float* data, QString label){
    if(params.labels.contains(label)){
        dojoID nodeID = params.labels[label];
        if(nodeTable.contains(nodeID)){
            dojoNode* targetNode = nodeTable.value(nodeID);

            dojoInputSynapse* input = new dojoInputSynapse(data, targetNode);
            targetNode->addSource(input);
        }
    }
}

void dojo::bindOutput(QString label, float* data){
    if(params.labels.contains(label)){
        dojoID nodeID = params.labels[label];
        if(nodeTable.contains(nodeID)){
            dojoNode* sourceNode = nodeTable.value(params.labels[label]);
            dojoOutputSynapse* output = new dojoOutputSynapse(sourceNode, data);
            sourceNode->addTarget(output);
        }
    }
}
void dojo::bindNodes(dojoSynapseParams syn){
    if(nodeTable.contains(syn.source) && nodeTable.contains(syn.target)){
        dojoNode* sourceNode = nodeTable.value(syn.source);
        dojoNode* targetNode = nodeTable.value(syn.target);

        dojoChemicalSynapse* synapse = new dojoChemicalSynapse(sourceNode, targetNode, syn);
        sourceNode->addTarget(synapse);
        targetNode->addSource(synapse);

        params.synapses << syn;
    }
}
