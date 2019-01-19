#include<vector>
#include<cmath>
#include "probability.h"


using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif

////////////Probability functions////////////
float sigmoid(float a)                                          //returns sigmoid of a float
{   return 1/(1+exp(-a));   }

void sigmoid(vector<float>&v)
{
    long n=v.size();
    for(long i=0;i<n;i++)
        v[i]=sigmoid(v[i]);
}



void softmax(vector<float>&v)
{
    long n=v.size();
    float s=0;
    for(long i=0;i<n;i++)
        s+=exp(v[i]);
    
    for(long i=0;i<n;i++)
        v[i]=(exp(v[i]))/s;
}
/////////////////////////////////////////////
