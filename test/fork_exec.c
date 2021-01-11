#include "syscall.h"

// commande : ./nachos -rs 1234 -x ../test/fork_exec
//test : permet de lancer deux processus chacun son espace d'adressage et chacun execute le programme putchar 

int main ()
{    
    ForkExec("../test/putchar");
    ForkExec("../test/putchar");
    //while(1);
    return 0;
    
}