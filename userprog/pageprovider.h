#ifdef CHANGED
#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "copyright.h"
#include "bitmap.h"
#include "synch.h"

class PageProvider:dontcopythis
{
  public:
    PageProvider();

    int GetEmptyPage(); 
    void ReleasePage(int numPage);
    int  NumAvailPage();




  private:
  BitMap *bitmap;  
  Lock *mutex;




};


#endif //PAGEPROVIDER_H
#endif