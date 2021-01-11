#include "syscall.h"

#define THIS "ccc"
#define THAT "ddd"

const int N = 10; // Choose it large enough!

void puts(const char *s)
{
    const char *p; for (p = s; *p != '\0'; p++) putchar(*p);
}

void f(void *arg)
{
    const char *s = arg;
    int i;
    putchar('x');
    for (i = 0; i < N; i++)
        puts(s);
    ThreadExit();
}


int main()
{
    ThreadCreate(f, THIS);
    f(THAT);
    ThreadExit();
}
