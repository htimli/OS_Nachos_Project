#include "syscall.h"

// commande : ./nachos -rs 1234 -x ../test/make_threads_3
//test : permet de lancer plusieurs threads là en locumrence 20 threads chaque écrit 4 fois 'a' comme demandé 

void g (void * arg)
{
    int n=4;
    volatile int i ;
    for(i=0 ;i<n;i++){
        putchar((int)arg);
    }
    ThreadExit();   
}


int main ()
{    
       
    int i;
    for(i=0 ; i<20 ;i++)
        ThreadCreate(g,(void*)'a');

    ThreadExit();
       
    return 0;
    
}