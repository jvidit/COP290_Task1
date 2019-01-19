#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "nonlinear.h"
#include "probability.h"
#include "pooling.h"
#include "convolution.h"
using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif

string ans_file="ans.txt";

//////////////Printing////////////
void pr(vvf v)
{
    long n=v.size();
    long m=v[0].size();
    
    for(long i=0;i<n;i++)
    {
        for(long j=0;j<m;j++)
            cout<<v[i][j]<<" ";
        cout<<endl;
    }
}

void pr(vector<float> v)
{
    long n=v.size();
    for(long i=0;i<n;i++)
        cout<<v[i]<<" ";
    cout<<endl;
}
///////////////////////////////////
///////exceptions/////////
void conv_error()
{
    cout<<"Error: Invalid usage of function\nconvolution <type_of_convolution(normal/matrix_mult)> <padsize> <matrix1.txt> <matrix1_numrows> <matrix2.txt> <matrix2_numrows> \n";
}

void relu_error()
{   cout<<"Error: Invalid usage of function\nrelu <matrix.txt> <matrix_numrows> <matrix_numcolums>\n";   }

void tanh_error()
{   cout<<"Error: Invalid usage of function\ntanh <matrix.txt> <matrix_numrows> <matrix_numcolumns>\n";   }

void pool_error()
{
    cout<<"Error: Invalid usage of function\npooling <pool_type(max/avg)> <stride> <matrix.txt> <matrix_numrows>\n";
}

void softmax_error()
{
    cout<<"Error: Invalid usage of function\nsoftmax <vector_length> <vector.txt>\n";
}

void sigmoid_error()
{
    cout<<"Error: Invalid usage of function\nsigmoid <vector_length> <vector.txt>\n";
}

/////////////////////////



///////////////file IO//////////
int read_vvf(string filename,long r,long c,vvf&v)
{
    ifstream f;
    f.open(filename);
    if(!f)
    {
        cout<<"File "<<filename<<" not found in the same directory\n";
        return 0;
    }
    vvf ans(r);
    float temp=0;
    for(long i=0;i<c;i++)
    {
        for(long j=0;j<r;j++)
        {
            f>>temp;
            ans[j].push_back(temp);
        }
    }
    f.close();
    
    v=ans;
    return 1;
}


int read_vvf(string filename,long n,vector<float>&v)
{
    ifstream f;
    f.open(filename);
    if(!f)
    {
        cout<<"File "<<filename<<" not found\n";
        return 0;
    }
    vector<float> ans(n);
    float temp=0;
    for(long i=0;i<n;i++)
    {
        f>>temp;
        ans[i]=temp;
    }
    f.close();
    v=ans;
    return 1;
}


void write_vvf(string filename,vvf ans)
{
    long r=ans.size(),c=ans[0].size();
    ofstream f;
    f.open(filename);
   
    for(long i=0;i<r;i++)
    {
        for(long j=0;j<c;j++)
            f<<ans[i][j]<<" ";
        f<<endl;
    }
    f.close();
    
}


void write_vvf(string filename,vector<float> v)
{
    long n=v.size();
    ofstream f;
    f.open(filename);
    
    for(long i=0;i<n;i++)
        f<<v[i]<<" ";
    f<<endl;
    f.close();
}



long tonum(string s)
{
    stringstream convert(s);
    long n;
    
    if(!(convert>>n))
        n=-1;
    if(n==-1)
    {
        cout<<"Error: Invalid argument\n";
        return 0;
    }
    return n;
    
}
////////////////////////////////////




int main(int argc, char * argv[])
{
    vvf v1,v2,v3;
    vector<float> a1;
    if(argc<2)
    {
        cout<<"No function specified\n";
        return 0;
    }
    
    if(strcmp(argv[1],"convolution")==0)                                        //convolution
    {
        if(argc!=8)
        {
            conv_error();
            return 0;
        }
        
        long n1=tonum(argv[5]);
        long n2=tonum(argv[7]);
        long padsize=tonum(argv[3]);
        if(!n1 || !n2 || padsize<0)
        {
            conv_error();
            return 0;
        }
        
        long t1=read_vvf(argv[4], n1, n1, v1);
        long t2=read_vvf(argv[6], n2, n2, v2);
        
        if(!t1 or !t2)
        {
            conv_error();
            return 0;
        }
        
        if(strcmp(argv[2],"normal"))
        {
            v3=normal_conv(v1, v2, padsize);
            write_vvf(ans_file, v3);
        }
        else if(strcmp(argv[2],"matrix_mult"))
        {
            v3=mm_conv(v1, v2,padsize);
            write_vvf(ans_file, v3);
        }
        else
            conv_error();
    }
    
    
    
    
    else if(strcmp(argv[1],"relu")==0)
    {
        if(argc!=5)
        {
            relu_error();
            return 0;
        }
        
        long r=tonum(argv[3]);
        long c=tonum(argv[4]);
        if(!r || !c)
        {
            relu_error();
            return 0;
        }
        long t1=read_vvf(argv[2], r, c, v1);
        if(!t1)
        {
            relu_error();
            return 0;
        }
       
        relu(v1);
        write_vvf(ans_file, v1);
    }
    
    
    
    else if(strcmp(argv[1],"tanh")==0)
    {
        if(argc!=5)
        {
            tanh_error();
            return 0;
        }
        
        long r=tonum(argv[3]);
        long c=tonum(argv[4]);
        if(!r || !c)
        {
            tanh_error();
            return 0;
        }
        long t1=read_vvf(argv[2], r, c, v1);
        if(!t1)
        {
            tanh_error();
            return 0;
        }
        
        tanh(v1);
        write_vvf(ans_file, v1);
    }
    
    
    
    else if(strcmp(argv[1],"pooling")==0)
    {
        if(argc!=6)
        {
            pool_error();
            return 0;
        }
        
        long stride=tonum(argv[3]), n=tonum(argv[5]);
        
        if(!stride || !n)
        {
            pool_error();
            return 0;
        }
        
        long t1=read_vvf(argv[4], n, n, v1);
        if(!t1)
        {
            pool_error();
            return 0;
        }
        
        if(strcmp(argv[2],"max")==0)
        {
            v1=max_pool(v1, stride);
            write_vvf(ans_file, v1);
        }
        else if(strcmp(argv[2], "avg")==0)
        {
            v1=avg_pool(v1, stride);
            write_vvf(ans_file, v1);
        }
        else
            pool_error();
    }
    
    
    else if(strcmp(argv[1], "softmax")==0)
    {
        if(argc!=4)
        {
            softmax_error();
            return 0;
        }
        
        long n=tonum(argv[2]);
        if(!n)
        {
            softmax_error();
            return 0;
        }
        
        long t1=read_vvf(argv[3], n, a1);
        if(!t1)
        {
            softmax_error();
            return 0;
        }
        
        softmax(a1);
        write_vvf(ans_file, a1);
    }
    
    
    else if(strcmp(argv[1], "sigmoid")==0)
    {
        if(argc!=4)
        {
            sigmoid_error();
            return 0;
        }
        
        long n=tonum(argv[2]);
        if(!n)
        {
            sigmoid_error();
            return 0;
        }
        
        long t1=read_vvf(argv[3], n, a1);
        if(!t1)
        {
            sigmoid_error();
            return 0;
        }
        
        sigmoid(a1);
        write_vvf(ans_file, a1);
    }

    else
        cout<<"Error: Invalid function name\n";
    
    return 0;
}



