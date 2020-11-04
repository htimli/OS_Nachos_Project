#ifdef CHANGED
#include "syscall.h"   



int main()
{
    int MAX_SIZE = 5;
    char adrMips[MAX_SIZE] ;
    getString(adrMips,MAX_SIZE);
    putString(adrMips);
    return 0;
}
#endif