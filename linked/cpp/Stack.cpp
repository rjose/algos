#include <stdio.h>
#include "Stack.h"
#include "MemManager.h"


Stack::Stack(MemManager *memmgr)
{
        memManager = memmgr;
        top = NULL;
}

void Stack::push(int val)
{
        MemNode *node = memManager->allocateNode();
        node->setValue(val);
        node->setLink(top);
        top = node;
}

int Stack::pop()
{
        if (!top)
                throw -1;

        int result = top->getValue();
        MemNode *p = top;
        top = p->nextNode();
        p->free();

        return result;
}
