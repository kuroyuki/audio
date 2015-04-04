#ifndef DOJONODE_H
#define DOJONODE_H

#include <QList>
#include "dojosynapse.h"
#include "dojostructs.h"

class dojoNode
{
public:
    dojoNode(dojoNodeParams data);
    void processNode();

    void addSource(dojoSynapse* input);
    void addTarget(dojoSynapse* output);
    void addSource(dojoNode* source);
    void addTarget(dojoNode* target);

    QVector3D getAxonPosition();
    dojoID getID();

private:

    QList<dojoSynapse*> sources;
    QList<dojoSynapse*> targets;

    dojoNodeParams params;

    float voltage;
};

#endif // DOJONODE_H
