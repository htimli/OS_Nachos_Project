#ifdef CHANGED  

#include <stdlib.h>
#include "userprog.h"
#include "system.h"
#include "syscall.h"


void StartUserProg(void * ){
    
    DEBUG ('s', "from StartUserProg  \n");

    currentThread->space->InitRegisters();  

    machine->Run ();

   
}

int do_ForkExec(char *s){
    
    DEBUG ('s', "from do_ForkExec  \n");
    
    OpenFile *executable = fileSystem->Open (s);

    AddrSpace *newSpace = new AddrSpace(executable); 

    Thread *t = new Thread ("newProcess");

    t->space = newSpace;

    nbProcess++;

    t->Start(StartUserProg,NULL);

    currentThread->Yield(); 
	return 0;
}

    

#endif