#ifdef CHANGED
#include "syscall.h"    //fichier ajouter lors du tp1


void print (char c , int n )
{
    int i ;
    //#if 0  
    for(i=0;i<n;i++){
        putchar(c+i);
    }
    putchar('\n');
    //#endif
}

int main()
{    
    print('b',4);
   // Halt();
   return 0;
}
#endif