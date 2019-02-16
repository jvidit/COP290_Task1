#include<iostream>
#include<vector>
#include<cmath>
#include<stdlib.h>
#include "conv_helper.h"
#include "conv_openblas.h"
#include "OpenBLAS-0.2.20/cblas.h"


using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif


vvf openblas_conv(vvf a,vvf b,long pad_size)
{
    
    if(pad_size)
        padding(a,pad_size);
    
    //flip(b);
    
    
    long ans_size=a.size()-b.size()+1;
    vector< vector < float > > ans(ans_size);
    
    if(a.size()!=a[0].size() || b.size()!=b[0].size())
    {
        cout<<"Input Matrices are not square\n";
        return ans;
    }
    
    vvf top_a(ans_size*ans_size),top_b(b.size()*b.size());
    
    long ind=0;
    for(long i=0;i<ans_size;i++)
    {
        
        for(long j=0;j<ans_size;j++)
        {
            
            for(long x=0;x<b.size();x++)
            {
                for(long y=0;y<b.size();y++)
                    top_a[ind].push_back(a[i+x][j+y]);
            }
            ind++;
        }
    }
    
    ind=0;
    for(long i=0;i<b.size();i++)
    {
        for(long j=0;j<b.size();j++)
        {
            top_b[ind].push_back(b[i][j]);
            ind++;
        }
    }
    

    
    long m=top_a.size(),k=top_a[0].size(),n=top_b[0].size();
    
    
    double *topa,*topb,*topc;
    topa = (double *)malloc( m*k*sizeof(double));
    topb = (double *)malloc( k*n*sizeof(double));
    topc = (double *)malloc( m*n*sizeof(double));
    
    
    vvf_to_arr(top_a,topa);
    vvf_to_arr(top_b,topb);
    
    float start=clock();
    cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,m,n,k,1,topa, m, topb, k, 0, topc, m);
    float stop=clock()-start;
    cout<<flush;
    vvf top_ans=arr_to_vvf(topc,m,n);
     
    free(topa);
    free(topb);
    free(topc);
    
     
    
    
    
    ind=0;
    for(long i=0;i<ans_size;i++)
    {
        for(long j=0;j<ans_size;j++)
        {
            ans[i].push_back(top_ans[ind][0]);
            ind++;
        }
    }
    
    
    return ans;
}
///////////////////////////////////////////

