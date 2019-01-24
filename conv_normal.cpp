#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include "conv_helper.h"
#include "conv_normal.h"


using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif


vvf normal_conv(vvf a,vvf b,long pad_size)
{
   
    if(pad_size)
        padding(a,pad_size);
    
    flip(b);
    
    
    long ans_size=a.size()-b.size()+1;
    vvf ans(ans_size);
    
    if(a.size()!=a[0].size() || b.size()!=b[0].size())
    {
        cout<<"Input Matrices are not square\n";
        return ans;
    }
    
    for(long i=0;i<ans.size();i++)
    {
        for(long j=0;j<ans.size();j++)
        {
            float s=0;
            for(long x=0;x<b.size();x++)
            {
                for(long y=0;y<b.size();y++)
                    s+=a[i+x][j+y]*b[x][y];
            }
            ans[i].push_back(s);
        }
    }
    return ans;
}

