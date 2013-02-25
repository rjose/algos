#ifndef MEM_NODE_H
#define MEM_NODE_H

class MemManager;

class MemNode
{
        public:
                MemNode();
                void setLink(MemNode *next);
                void setValue(int val);

                int getValue();
                MemNode *nextNode();
                void setMemManager(MemManager *mgr);
                void free();

        private:
                int value;
                MemNode *link;
                MemManager *memManager;
};

#endif
