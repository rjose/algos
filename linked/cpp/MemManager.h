#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include "MemNode.h"

const int NumNodes = 100;

class MemManager {
        public:
                MemManager();
                MemNode *allocateNode();
                void free(MemNode *node);

        private:
                MemNode nodes[NumNodes];
                MemNode *available;
};

#endif
