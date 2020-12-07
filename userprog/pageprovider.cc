#ifdef CHANGED

#include "pageprovider.h"
#include "machine.h"
#include "system.h"


PageProvider::PageProvider(){
    bitmap=new BitMap (NumPhysPages);    
    mutex= new Lock("Lock_page_provider");    
}

int 
PageProvider::GetEmptyPage(){
    mutex->Acquire();
    int res =  bitmap->Find();
    //if -1 no bits are clear
    if(res != -1)
        memset(&machine->mainMemory[res],0,PageSize);   
    mutex->Release();
    return res ;        
}
void 
PageProvider::ReleasePage(int numPage){
    bitmap->Clear(numPage);
}
int
PageProvider::NumAvailPage(){
    return bitmap->NumClear ();
}





#endif