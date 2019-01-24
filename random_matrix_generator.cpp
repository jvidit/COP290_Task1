#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char*argv[])
{
    
    fstream f1,f2;
    f1.open("mat1.txt");
    f2.open("mat2.txt");
    
    
    if(argc!=3)
        return 0;
    
    int x,y;
    sscanf(argv[1], "%d", &x);
    sscanf(argv[2], "%d", &y);
    
    
    for(long i=0;i<x*x;i++)
        f1<<rand()<<" ";

    for(long i=0;i<y*y;i++)
        f2<<rand()<<" ";
    
    return 0;
}
