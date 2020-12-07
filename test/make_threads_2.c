#include "syscall.h"

// commande : ./nachos -rs 1234 -x ../test/make_threads_2
//test : permet de lancer deux threads et le thread main chacun écrit une chaine de caractère differente 

void f (void *arg)
{
    putString(arg);
    ThreadExit();   
}


int main ()
{       
    ThreadCreate(f,(void*)"TOTO ");
    ThreadCreate(f,(void*)" lzlz ");

    putString(" titi");
    ThreadExit();       
    return 0;
    
}