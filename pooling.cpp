#include<iostream>
#include<vector>
#include<cmath>
#include "pooling.h"


using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif




////////////////////Pooling///////////////
vvf max_pool(vvf a,long stride)
{
    vvf ans(a.size()/stride);
    if(a.size()!=a[0].size())
    {
        cout<<"Input Matrice isnt square\n";
        return ans;
    }
    if(a.size()%stride)
    {
        cout<<"Stride isnt a divisor of input matrix size\n";
        return ans;
    }
    
    for(long i=0;i<a.size();i+=stride)
    {
        for(long j=0;j<a.size();j+=stride)
        {
            float temp=-1*MAXFLOAT;
            for(long x=0;x<stride;x++)
            {
                for(long y=0;y<stride;y++)
                    temp=max(temp,a[i+x][j+y]);
            }
            ans[i/stride].push_back(temp);
        }
    }
    return ans;
}

vvf avg_pool(vvf a,long stride)
{
    vvf ans(a.size()/stride);
    if(a.size()!=a[0].size())
    {
        cout<<"Input Matrice isnt square\n";
        return ans;
    }
    if(a.size()%stride)
    {
        cout<<"Stride isnt a divisor of input matrix size\n";
        return ans;
    }
    
    for(long i=0;i<a.size();i+=stride)
    {
        for(long j=0;j<a.size();j+=stride)
        {
            float temp=0;
            for(long x=0;x<stride;x++)
            {
                for(long y=0;y<stride;y++)
                    temp+=a[i+x][j+y];
            }
            ans[i/stride].push_back(temp/(stride*stride));
        }
    }
    return ans;
}

/////////////////////////

