#include "syscall.h"


// commande : ./nachos -rs 1234 -x ../test/make_threads
//test : thread crée qui lance un putchar ici le while(1) pour que thread main ne 
         //se termine pas avant notre thread on gérer par la suite du tp la terminason du programme 

void f (void * arg)
{
    
    putchar((int)arg);
    ThreadExit();
    
    
    
}



int main ()
{    
    ThreadCreate(f,(void*)'f');
    while(1);
    ThreadExit();

    
    return 0;
    
}