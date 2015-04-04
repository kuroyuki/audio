#include "dojonode.h"

dojoNode::dojoNode(dojoNodeParams data)
{
    voltage = 0;
    params = data;
}
void dojoNode::processNode(){
    //sum all sources
    float synapticVoltage = 0;
    for (int i = 0; i < sources.size(); ++i) {
        synapticVoltage += sources[i]->getVoltage();
    }
    voltage += synapticVoltage;

    //check for threshold
    if(voltage > 1){
        //send ap to all targets
        for (int i = 0; i < targets.size(); ++i) {
            targets.at(i)->ap(this);
        }
        //send ap to all sources
        for (int i = 0; i < sources.size(); ++i) {
            sources.at(i)->ap(this);
        }
        //reset voltage
        voltage = 0;
    }
}

void dojoNode::addSource(dojoSynapse* input){
    sources<<input;
}
void dojoNode::addTarget(dojoSynapse* output){
    targets<<output;
}
QVector3D dojoNode::getAxonPosition(){
    return params.axon;
}
dojoID dojoNode::getID(){
    return params.id;
}
