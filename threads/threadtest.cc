// threadtest.cc 
//      Simple test case for the threads assignment.
//
//      Create two threads, and have them context switch
//      back and forth between themselves by calling Thread::Yield, 
//      to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

//----------------------------------------------------------------------
// SimpleThread
//      Loop 10 times, yielding the CPU to another ready thread 
//      each iteration.
//
//      "which" is simply a number identifying the thread, for debugging
//      purposes.
//----------------------------------------------------------------------

void
SimpleThread (void *arg)
{
    int which = (long) arg;
    int num;

    for (num = 0; num < 10; num++)
      {
	  printf ("*** thread %d looped %d times\n", which, num);
	  currentThread->Yield ();//je passe la main à l'autre 
      //sinon pas de temporisateur dans nachos comme linux 
      }
}

//----------------------------------------------------------------------
// ThreadTest
//      Set up a ping-pong between two threads, by forking a thread 
//      to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest ()
{
    DEBUG ('t', "Entering SimpleTest\n");

    Thread *t = new Thread ("forked thread");
    
    t->Start (SimpleThread, (void*) 1);//le thread 0 cree le 1 et le met dans la liste des thread prets
    
    //et continue de s'executer 
    SimpleThread (0);
}
