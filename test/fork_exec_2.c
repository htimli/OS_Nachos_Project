//demandé dans action 2.3 
//commande : ./nachos -rs 1234 -x ../test/fork_exec_2
//Erreur de segmentation

#include "syscall.h"
void main()
{
ForkExec("../test/userpages0");
ForkExec("../test/userpages1");
}