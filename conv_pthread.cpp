#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <pthread.h>
#include "conv_helper.h"
#include "conv_pthread.h"

using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif


struct c_element_struct {
	double *a, *b, *c;
	long long x,y,z;
	int thread_no; 

};


void* c_element (void* arg)
{
	struct c_element_struct *arg_struct =
			(struct c_element_struct*) arg;
	int no_of_threads=4;
	double *a=  arg_struct->a;
	double *b=  arg_struct->b;
	double *c=  arg_struct->c;
	int thread_no=arg_struct->thread_no;
	long long x = arg_struct->x;
	long long y = arg_struct->y;
	long long z = arg_struct->z;
	free(arg);
	long long start_row=(x*thread_no)/no_of_threads;
	long long end_row=(x*(thread_no+1))/no_of_threads;
	for(long long m=start_row;m<end_row;m++){
		for(long long n=0;n<z;n++){
			double sum = 0;
			for (long long i = 0; i < arg_struct->y; i++) {
				sum += a[x*i+m]*b[y*n+i];
			}
			c[n*x+m]= sum;
			
		}
	}
	pthread_exit(0);
}


double* pthread_dgemm (double* a,double *b,  long long x, long long y,long long z)
{
    
    const int s=3000;
    static double c[s*s];
    
    /*
    static double a[s*s];
	static double b[s*s];
	
    

	for(long long i=0;i<x*y;i++)
        a[i]=A[i];
	
	for(long long i=0;i<y*z;i++)
        b[i]=B[i];
    */
    
    int no_of_threads=4;
	pthread_t tids[no_of_threads];

	for (long long i = 0; i < no_of_threads; i++) {
			c_element_struct *arg = (c_element_struct*)malloc(sizeof(*arg));
			arg->a=a;
			arg->b=b;
			arg->c=c;
			arg->x=x;
			arg->y=y;
			arg->z=z;
			arg->thread_no=i;
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_create(&tids[i], &attr, c_element, arg);
			

			
	}
    
    
	
	for (long long i = 0; i < no_of_threads; i++)
		pthread_join(tids[i], NULL);
			
    
    return c;
    
			
}

vvf pthread_conv(vvf a,vvf b,long pad_size)
{
    
    if(pad_size)
        padding(a,pad_size);
    
    //flip(b);
    
    
    long ans_size=a.size()-b.size()+1;
    vvf ans(ans_size);
    
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
    
    
    
    vvf_to_arr(top_a,topa);
    vvf_to_arr(top_b,topb);
    
    double start=clock();
    topc=pthread_dgemm(topa,topb,m,k,n);
    //cout<<clock()-start<<endl;
    
    vvf top_ans=arr_to_vvf(topc,m,n);
    
    free(topa);
    free(topb);
    
    
    
    
    
    
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


