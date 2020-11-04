#include "syscall.h"


void f (void * arg)
{
    //TODO
    putchar((int)arg);
    putchar('b');
    ThreadExit();
    
}



int main ()
{    
    ThreadCreate(f,(void*)'f');
    //putchar('k');
    while(1);
    ThreadExit();

    
    return 0;
    
}