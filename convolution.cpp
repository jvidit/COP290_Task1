#include<iostream>
#include<vector>
#include<cmath>
#include "convolution.h"
//#include "mkl.h"
#include "OpenBLAS-0.2.20/cblas.h"


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


////////////Matrix Multiplication//////////////
vvf mat_mul(vvf a,vvf b)
{
    
    long r1=a.size(),c1=a[0].size();
    long r2=b.size(),c2=b[0].size();
    vvf  ans(r1);
    if(c1!=r2)
    {
        cout<<"Matrices not compatible\n";
        return ans;
    }
    
    
    for(long i=0;i<r1;i++)
    {
        for(long j=0;j<c2;j++)
        {
            float s=0;
            for(long k=0;k<r2;k++)
                s+=a[i][k]*b[k][j];
            ans[i].push_back(s);
        }
    }
    return ans;
}

///////////////////////////////////////////////


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



vvf mm_conv(vvf a,vvf b,long pad_size)
{
    
    if(pad_size)
        padding(a,pad_size);
    
    flip(b);
    
    
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
    
    
    float start=clock();
    vvf top_ans=mat_mul(top_a, top_b);
    cout<<clock()-start<<endl;
     
    
    
    long m=top_a.size(),k=top_a[0].size(),n=top_b[0].size();
    
    /*
    double *topa,*topb,*topc;
    topa = (double *)mkl_malloc( m*k*sizeof(double),64);
    topb = (double *)mkl_malloc( k*n*sizeof(double),64);
    topc = (double *)mkl_malloc( m*n*sizeof(double),64);
    
    
    vvf_to_arr(top_a,topa);
    vvf_to_arr(top_b,topb);
    
    float start=clock();
    cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,m,n,k,1,topa, m, topb, k, 0, topc, m);
    cout<<clock()-start<<endl;
     
    vvf top_ans=arr_to_vvf(topc,m,n);
     
    mkl_free(topa);
    mkl_free(topb);
    mkl_free(topc);
    */
     
    
    
    
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

