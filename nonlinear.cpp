#include <vector>
#include <cmath>
#include "nonlinear.h"

using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif


///////////////non linear activations///////
float relu(float a)                                             //relu returns value if value greater than 0, otherwise 0
{   return max((float)0,a);    }

void relu(vvf&v)
{
    long n=v.size();
    long m=v[0].size();
    
    for(long i=0;i<n;i++)
    {
        for(long j=0;j<m;j++)
            v[i][j]=relu(v[i][j]);
    }
}


void tanh(vvf&v)
{
    long n=v.size();
    long m=v[0].size();
    
    for(long i=0;i<n;i++)
    {
        for(long j=0;j<m;j++)
            v[i][j]=tanh(v[i][j]);
    }
}
