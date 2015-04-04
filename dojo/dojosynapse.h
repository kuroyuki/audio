#ifndef DOJOSYNAPSE_H
#define DOJOSYNAPSE_H

#include "dojostructs.h"


class dojoSynapse
{
public:
    dojoSynapse();
    ~dojoSynapse();
    virtual float getVoltage()= 0;
    virtual void ap(dojoNode* node)= 0;
};

class dojoInputSynapse : public dojoSynapse
{
public:
    dojoInputSynapse(float* src, dojoNode* trg);
    float getVoltage();
    void ap(dojoNode* node);

private:

    float* source;
    dojoNode* target;
};
class dojoOutputSynapse : public dojoSynapse
{
public:
    dojoOutputSynapse(dojoNode* src, float* trg);
    float getVoltage();
    void ap(dojoNode* node);

private:    

    dojoNode* source;
    float* target;
};
class dojoChemicalSynapse : public dojoSynapse
{
public:
    dojoChemicalSynapse(dojoNode* src, dojoNode* trg, dojoSynapseParams data);
    float getVoltage();
    void ap(dojoNode* node);

private:
   dojoSynapseParams params;
   float cleft;

   dojoNode* source;
   dojoNode* target;
};
#endif // DOJOSYNAPSE_H
