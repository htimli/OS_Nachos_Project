//TP 2 Action I4


#ifdef CHANGED  

#ifndef USERTHREAD_H
#define USERTHREAD_H

typedef struct 
    {
        int f ;
        int arg;
    }SCHMURTZ;

extern  int do_ThreadCreate(int f,int arg);
extern void do_threadExit();




#endif
#endif