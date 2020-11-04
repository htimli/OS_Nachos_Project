#ifdef CHANGED  

#include"userthread.h"
#include <stdlib.h>
#include "system.h"
#include "syscall.h"



void StartUserThread(void *shmurtz){
    DEBUG ('s', "from StartUserThread  \n");
    int i;
    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister (i, 0);

   
    DEBUG ('s', "from StartUserThread valeur de f=%d  \n",((SCHMURTZ *)shmurtz)->f);
    machine->WriteRegister (PCReg,((SCHMURTZ *)shmurtz)->f);
    
    machine->WriteRegister(4,((SCHMURTZ *)shmurtz)->arg);
    
    
    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

    machine->WriteRegister (StackReg, currentThread->space->AllocateUserStack ());//l add

    machine->Run ();
   
}

int do_ThreadCreate(int f,int arg){

   
    
    //verfier si il y a tjr de l'espace pour la pile du thread sinon -1

    SCHMURTZ *shmurtz;
    shmurtz = (SCHMURTZ*)malloc(sizeof(SCHMURTZ)) ;
    shmurtz->f= f;
    shmurtz->arg= arg;
    Thread *t = new Thread ("forked thread");
     DEBUG ('s', "from do_ThreadCreate valeur de f=%d  \n",shmurtz->f);
    t->Start(StartUserThread,(void *)shmurtz);
    currentThread->Yield ();
    
    return 0;


}
void do_threadExit(){
    DEBUG ('s', "from do_ThreadExit \n");
    currentThread->Finish();   
}


#endif