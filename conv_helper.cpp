#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include "conv_helper.h"



using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif

////////////////vvf to 2D///////////////
void vvf_to_arr(vvf v, double ans[])
{
    long r=v.size();
    long c=v[0].size();
    long ind=0;
    for(long j=0;j<c;j++)
    {
        for(long i=0;i<r;i++)
        {
            ans[ind]=v[i][j];
            ind++;
        }
    }
    
}


vvf arr_to_vvf(double arr[],long r,long c)
{
    vvf v(r);
    int ind=0;
    for(long j=0;j<c;j++)
    {
        for(long i=0;i<r;i++)
        {
            v[i].push_back(arr[ind]);
            ind++;
        }
    }
    return v;
}
//////////////////////////////////

////////////Padding///////////////
void padding(vvf &v, long pad)
{
    long n=v.size();
    for(long i=0;i<pad;i++)
    {
        vector<float> temp1,temp2;
        v.insert(v.begin(),temp1);
        v.push_back(temp2);
        for(long j=0;j<n;j++)
        {
            v[0].push_back(0);
            v[v.size()-1].push_back(0);
        }
    }
    
    for(long i=0;i<v.size();i++)
    {
        for(long j=0;j<pad;j++)
        {
            v[i].push_back(0);
            v[i].insert(v[i].begin(), 0);
        }
    }
}
////////////////////////////////////



///////////////Normal Convolution//////////////
void flip(vvf&v)
{
    long r=v.size(),c=v[0].size();
    
    for(long i=0;i<r/2;i++)
    {
        for(long j=0;j<c;j++)
        {
            float temp=v[i][j];
            v[i][j]=v[r-1-i][c-1-j];
            v[r-1-i][c-1-j]=temp;
        }
    }
    
    if(r&1)
    {
        for(int j=0;j<c/2;j++)
        {
            float temp=v[r/2][j];
            v[r/2][j]=v[r/2][c-1-j];
            v[r/2][c-1-j]=temp;
        }
    }
}


