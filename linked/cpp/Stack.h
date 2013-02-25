#ifndef STACK_H
#define STACK_H

class MemManager;
class MemNode;

class Stack
{
        public:
                Stack(MemManager *memmgr);
                void push(int val);
                int pop();

        private:
                MemManager *memManager;
                MemNode *top;
};

#endif
