#include <stdio.h>
#include "MemManager.h"
#include "Stack.h"

int main()
{
        printf("Howdy, C++!\n");
        MemManager memmgr;
        Stack stack(&memmgr);
        stack.push(0xAA);
        stack.push(0xBB);

        int v = stack.pop();
        return 0;
}
