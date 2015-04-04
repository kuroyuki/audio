#include "dojosynapse.h"

dojoSynapse::dojoSynapse()
{

}

dojoSynapse::~dojoSynapse()
{

}
dojoInputSynapse::dojoInputSynapse(float* src, dojoNode* trg){
    source = src;
    target = trg;
}
float dojoInputSynapse::getVoltage(){
    return *source;
}
void dojoInputSynapse::ap(dojoNode *node){
    if(target == node){

    }
}

dojoOutputSynapse::dojoOutputSynapse(dojoNode* src, float* trg){
    source = src;
    target = trg;
}
float dojoOutputSynapse::getVoltage(){
    return 0;
}
void dojoOutputSynapse::ap(dojoNode *node){
    if(source == node){
        *target = 1;
    }
}

dojoChemicalSynapse::dojoChemicalSynapse(dojoNode* src, dojoNode* trg, dojoSynapseParams data){
    source = src;
    target = trg;

    params = data;
    cleft = 0;
}
float dojoChemicalSynapse::getVoltage(){
    float voltage =  cleft;
    cleft = 0;
    return voltage;
}
void dojoChemicalSynapse::ap(dojoNode *node){
    if(source == node){
        cleft = params.terminals;
    }
}
