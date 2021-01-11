//demandé dans action 2.4 : lance 12 processus avec chacun 20 threads 
//commande : ./nachos -rs 1234 -x ../test/fork_exec_2 

//Erreur de segmentation

#include "syscall.h"
int main()
{
    int i;
    for (i=0;i<12;i++)
        ForkExec("../test/make_threads_3");
    return 0 ;    
}