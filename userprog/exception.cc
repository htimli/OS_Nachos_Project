// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#ifdef CHANGED
#include "userthread.h"
#include "userprog.h"
#endif


//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------
#ifdef CHANGED //partie 5 action 2 
    
	int copyStringFromMachine(int from,char*to,unsigned size,bool*fin)
	{
			int i;
			*fin=false;
			for(i= 0;(unsigned)i<size;i++){
				int ch;
				machine->ReadMem(from,1,&ch);
				
				if(ch=='\0'){
					*fin =true; 
					break;
				}
				to[i]=ch;

				from++;	
			}	

		to[i]='\0';
		return i;
	}
	int copyStringToMachine(char* from, int to,unsigned size)
	{
		int  i;
			
			
				for(i= 0;(unsigned)i<size;i++){
				
				machine->WriteMem(to,1,from[i]);
				
				if(from[i]=='\0')
					break;

				to++;
				}

		
		machine->WriteMem(to,1,'\0');

		return i;
		
	}
#endif 

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);
    int address = machine->registers[BadVAddrReg];

    switch (which)
      {
	case SyscallException:
          {
	    switch (type)
	      {
		case SC_Halt:
		  {
		    DEBUG ('s', "Shutdown, initiated by user program.\n");
		    interrupt->Halt ();
		    break;
		  }
		case SC_Exit:
		  { 
			printf("\nExit  : arg = %d \n",machine->ReadRegister (4));
			printf("\nnbProcess = %d \n",nbProcess);
			nbProcess--;						
			if(nbProcess==0)
				interrupt->Halt ();
			else {
				free(currentThread->space);
				currentThread->Finish(); 	
			}	
		    break; 
		  }
		#ifdef CHANGED
		case SC_PutChar:
		{
			DEBUG ('s', "PutChar debug \n");
			consoledriver->PutChar(machine->ReadRegister (4));

			break;
		}
		case SC_PutString:	
		{	
			DEBUG ('s', "PutString debug \n");

			int a=0;
			bool fin =false;
			
			char to[MAX_STRING_SIZE];
			int ptr = machine->ReadRegister(4);
			while(!fin){
				
				ptr=ptr+a;
				a=copyStringFromMachine(ptr,to,MAX_STRING_SIZE,&fin);	
				consoledriver->PutString(to);								
			}

			break;
		}
		case SC_GetString : 
		{
			DEBUG('s',"getString debug \n");
			int size=machine->ReadRegister(5);
			char from[size];
			consoledriver->GetString(from,size);
			int to=machine->ReadRegister(4);	
			
			
			copyStringToMachine(from,to,size);
						
			break;
		}
		case SC_GetChar	:
		{
			DEBUG ('s', "getChar debug \n");
			//machine->WriteRegister(2,consoledriver->GetChar());
			int c = consoledriver->GetChar();

			if(c==(int)EOF)
				printf("FIN DU FICHIER ! ");
			else 	
				machine->WriteRegister(2,c);			
			break;
		}
		case SC_GetInt	:
		{
			DEBUG ('s', "getInt debug \n");	
			
			//on a gérer juste les entier qui ont max 5 chiffre voire 4 chifres si l'entier est négatif
			//par manque de temps

			char from[5];
			int n ;
			consoledriver->GetString(from,5);
			sscanf(from,"%d",&n);
			
			
			int to = machine->ReadRegister(4);
			
			
			machine->WriteMem(to,4,n);
				
			break;
		}
		case SC_PutInt	:
		{
			DEBUG ('s', "PutInt debug \n");

			int n =machine->ReadRegister(4);
			
			int count = 1,nombre=n;

			//pour calculer le nombre de chiffre d'un entier 
			if (nombre < 0)
			{
				nombre = -nombre;
			}
			while (nombre >= 10)
			{
				nombre /= 10;
				count++;
			}
						
			//count +2 si jamais l'entier est négatif pour stocké le signe 			
			char s[count+2];
			snprintf(s,count+2,"%d",n);
			consoledriver->PutString(s);
				
			break;
		}
		case SC_ThreadCreate:
		{
			DEBUG ('s', "ThreadCreat debug \n");
			int f = machine->ReadRegister(4);
			int arg = machine->ReadRegister(5);
			DEBUG ('s', "ThreadCreat debug valeur de f=%d  \n",f);
			int r = do_ThreadCreate(f,arg);

			machine->WriteRegister(2,r); //TODO:gerer le cas =-1


			break;
		}
		case SC_ThreadExit:
		{
			DEBUG ('s', "ThreadExit debug \n");
			do_threadExit();
			break;
		}
		case SC_ForkExec:
		{
			DEBUG ('s', "ForkExec debug \n");

			int a=0;
			bool fin =false;
			
			char to[MAX_STRING_SIZE];
			int ptr = machine->ReadRegister(4);
			while(!fin){
				
				ptr=ptr+a;
				a=copyStringFromMachine(ptr,to,MAX_STRING_SIZE,&fin);	
				// on a pas gérer le cas ou la chaine est trop longue
			}	
			DEBUG ('s', "chaine copié = %s \n",to);

			do_ForkExec(to);

			break;
		}
		#endif
		/****************************************essai**************************/
		#ifdef CHANGED
		case SC_Print:
		{			
			int ptr = machine->ReadRegister(4);
			DEBUG ('s', "appel of essai \n");
			for(;;){
				int ch;
				machine->ReadMem(ptr,1,&ch);

				if(ch=='\0')
					break;
				printf("%c",ch);

				ptr++;	
			}
			break;
		}
		#endif
		//*********************************************************

		default:
		  {
		    printf("Unimplemented system call %d\n", type);
		    ASSERT(FALSE);
		  }
	      }

	    // Do not forget to increment the pc before returning!
	    UpdatePC ();
	    break;
	  }

	case PageFaultException:
	  if (!address) {
	    printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
	    ASSERT (FALSE);
	  } else {
	    printf ("Page Fault at address %x at PC %x\n", address, machine->registers[PCReg]);
	    ASSERT (FALSE);	// For now
	  }
	  break;

	case ReadOnlyException:
	  printf ("Read-Only at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case BusErrorException:
	  printf ("Invalid physical address at address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case AddressErrorException:
	  printf ("Invalid address %x at PC %x\n", address, machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case OverflowException:
	  printf ("Overflow at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	case IllegalInstrException:
	  printf ("Illegal instruction at PC %x\n", machine->registers[PCReg]);
	  ASSERT (FALSE);	// For now
	  break;

	default:
	  printf ("Unexpected user mode exception %d %d %x at PC %x\n", which, type, address, machine->registers[PCReg]);
	  ASSERT (FALSE);
	  break;
      }
}
