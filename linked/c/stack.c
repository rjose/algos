#include <stdio.h>
#include <stdlib.h>

#define NUM_ITEMS       100

struct linkmem_t {
        short value;
        struct linkmem_t *link;
};


struct linkmem_t linkmem[NUM_ITEMS];
struct linkmem_t* top = NULL;
struct linkmem_t* avail = NULL;

int init();
int pushval(short val);
int popval(short* valp);

int main()
{
        short popped = 0;
        printf("Hello, C!\n");

        if (init() < 0)
                exit(1);

        // Push some values
        pushval(0xAA);
        pushval(0xBB);
        pushval(0xCC);

        // Pop a value
        popval(&popped);
        return 0;
}

int pushval(short val)
{
        struct linkmem_t *p = avail;

        // Overflow
        if (p == NULL)
                return -1;

        avail = p->link;        // avail is the next available memory
        p->value = val;

        // Make |p| the top of the stack
        p->link = top;
        top = p;

        return 0;
}

int popval(short* valp)
{
        struct linkmem_t *p = top;

        // Underflow
        if (p == NULL)
                return -1;

        top = p->link;          // Move top one down the stack
        *valp = p->value;

        // Free what's pointed to by p
        p->link = avail;
        avail = p;

        return 0;
}

int init()
{
        int i;

        avail = linkmem;

        for (i=0; i < NUM_ITEMS-1; i++)
                linkmem[i].link = &linkmem[i+1];

        linkmem[NUM_ITEMS-1].link = NULL;
        return 0;
}
