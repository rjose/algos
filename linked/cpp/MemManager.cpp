#include "MemManager.h"
#include <stdio.h>

MemManager::MemManager()
{
        for (int i=0; i < NumNodes-1; i++) {
                nodes[i].setLink(&nodes[i+1]);
        }
        nodes[NumNodes-1].setLink(NULL);
        available = &nodes[0];
        printf("Constructed MemManager!\n");
}

MemNode *MemManager::allocateNode()
{
        MemNode *result = available;
        available = result->nextNode();
        result->setMemManager(this);
        return result;
}


void MemManager::free(MemNode *node)
{
        node->setLink(available);
        available = node;
}
