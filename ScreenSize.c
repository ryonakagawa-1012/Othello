#include <stdio.h>
#include <handy.h>

int main()
{
    double w, h;

    HgScreenSize(&w, &h);

    printf("%f,%f", w, h);

    return 0;
}