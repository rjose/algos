#include <stdio.h>
#include "MemNode.h"
#include "MemManager.h"

MemNode::MemNode()
{
        link = NULL;
        value = 0;
}

void MemNode::setLink(MemNode *next)
{
        link = next;
}


void MemNode::setValue(int val)
{
        value = val;
}

int MemNode::getValue()
{
        return value;
}

MemNode *MemNode::nextNode()
{
        return link;
}


void MemNode::setMemManager(MemManager *mgr)
{
        memManager = mgr;
}

void MemNode::free()
{
        if (!memManager)
                throw -1;
        memManager->free(this);
}
