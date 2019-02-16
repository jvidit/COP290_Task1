#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "nonlinear.h"
#include "probability.h"
#include "pooling.h"
#include "conv_normal.h"
#include "conv_mkl.h"
#include "conv_openblas.h"
#include "conv_pthread.h"
using namespace std;

#ifndef vvf
#define vvf vector < vector < float > >
#endif

#define vvvf vector < vector < vector < float > > >

string ans_file="intermediate.txt";
string im_file="image_28.txt";
string conv1_file="conv1.txt";
string conv2_file="conv2.txt";
string fc1_file="fc1.txt";
string fc2_file="fc2.txt";
string test_file="test_sub3.txt";



///////////////file IO//////////
int read_vvvf(string filename,long out_channels,long kernel_size,long in_channels,vvvf arr[],float bias[])
{
    ifstream f;
    float temp_val;
   
    f.open(filename);
    if(!f)
    {
        cout<<"File "<<filename<<" not found in the same directory\n";
        return 0;
    }
    
    for(long ind=0;ind<out_channels;ind++)
    {
        vvvf v;
        for(int i=0;i<in_channels;i++)
        {
            
            vvf temp2;
            for(int j=0;j<kernel_size;j++)
            {
                
                vector <float> temp1;
                for(int k=0;k<kernel_size;k++)
                    temp1.push_back(0);
                temp2.push_back(temp1);
            }
            
            
            for(int j=0;j<kernel_size;j++)
            {
                for(int k=0;k<kernel_size;k++)
                    f>>temp2[j][k];
            }
            
            v.push_back(temp2);
            
            
        }
    
        arr[ind]=v;
    }
    
    for(long ind=0;ind<out_channels;ind++)
        f>>bias[ind];
    f.close();
    return 1;
}


void write_vvvf(string filename,vvvf v)
{
    ofstream f;
    f.open(filename);

    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<v[0].size();j++)
        {
            for(int k=0;k<v[0][0].size();k++)
                f<<v[i][j][k]<<endl;
        }
    }
    f.close();
}


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
            ans[j].push_back(0);
    }
    
    for(long i=0;i<c;i++)
    {
        for(long j=0;j<r;j++)
            f>>ans[i][j];
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


/////////////////3D functions/////////////////
vvf threeDconv(vvvf v1,vvvf v2,float bias,string conv_type)
{
    long depth=v1.size();
    long m=v1[0].size(),n=v2[0].size();
    long s=m-n+1;
    
    
    vvf ans;
    
    
    
    if(strcmp(conv_type.c_str(),"normal")==0)
        ans=normal_conv(v1[0],v2[0],0);
    else if(strcmp(conv_type.c_str(),"pthread")==0)
        ans=pthread_conv(v1[0],v2[0],0);
    else if(strcmp(conv_type.c_str(),"mkl")==0)
        ans=mkl_conv(v1[0],v2[0],0);
    else
        ans=openblas_conv(v1[0],v2[0],0);
    
    
    for(int ind=1;ind<depth;ind++)
    {
        vvf temp;
        if(strcmp(conv_type.c_str(),"normal")==0)
            temp=normal_conv(v1[ind],v2[ind],0);
        else if(strcmp(conv_type.c_str(),"pthread")==0)
            temp=pthread_conv(v1[ind],v2[ind],0);
        else if(strcmp(conv_type.c_str(),"mkl")==0)
            temp=mkl_conv(v1[ind],v2[ind],0);
        else
            temp=openblas_conv(v1[ind],v2[ind],0);
        
        for(int i=0;i<s;i++)
        {
            for(int j=0;j<s;j++)
                ans[i][j]+=temp[i][j];
        }
    }
    
    for(int i=0;i<s;i++)
    {
        for(int j=0;j<s;j++)
            ans[i][j]+=bias;
    }
    return ans;
}

vvvf threeDpool(vvvf v)
{
    long depth=v.size();
    long n=v[0].size();
    
    vvvf ans;

    for(int ind=0;ind<depth;ind++)
    {
        vvf temp=max_pool(v[ind],2);
        ans.push_back(temp);
    }
    return ans;
}

void threeDrelu(vvvf&v)
{
    long depth=v.size();
    for(int ind=0;ind<depth;ind++)
        relu(v[ind]);
}



vvvf layer_conv(string filename,vvvf in,long out_channels,long in_channels,long kernel_size,string conv_type)
{
    vvvf out(out_channels);
    vvvf filter_arr[out_channels];
    float bias[out_channels];
    
    
    int a=read_vvvf(filename,out_channels,kernel_size,in_channels,filter_arr,bias);
    
    //write_vvf(test_file,normal_conv(in[0],filter_arr[0][0],0));
    
    for(long i=0;i<out_channels;i++)
    {
        out[i]=threeDconv(in,filter_arr[i],bias[i],conv_type);
        //write_vvf(test_file,out[0]);
    }
    return out;
}
//////////////////////////////////////////////


int main(int argc, char * argv[])
{
    
    if(argc!=3)
    {
        cout<<"Invalid arguments\n";
        return 0;
    }
    
    
    string im_png=argv[1];
    string system_call="python preprocess.py ."+im_png;

    system(system_call.c_str());
    
    long im_size=28;
    vvvf in1(1);
    read_vvf(im_file,im_size,im_size,in1[0]);
   
    
    ////////////Layer 1///////
    //////in1 + filter1 -> in2/////////////
    long out_channels1=20;
    long in_channels1=1;
    long kernel_size_1=5;
    
    vvvf in2=layer_conv(conv1_file,in1,out_channels1,in_channels1,kernel_size_1,argv[2]);
    //////////////
    
    
    //////Layer 2//////////
    //////////in2 -> in2, pooled///////
    in2=threeDpool(in2);
    //////////////
    
    
    
    ////////////Layer 3///////
    //////in2 + filter2 -> in3/////////////
    long out_channels2=50;
    long in_channels2=20;
    long kernel_size_2=5;
    vvvf in3=layer_conv(conv2_file,in2,out_channels2,in_channels2,kernel_size_2,argv[2]);
    //////////////
    
    write_vvvf(test_file,in3);
    
    
    
    //////Layer 4//////////
    //////////in3 -> in3, pooled///////
    in3=threeDpool(in3);
    //////////////
    
    
   
    ////////////Layer 5///////
    //////in3 + fc1 -> in4/////////////
    long out_channels3=500;
    long in_channels3=50;
    long kernel_size_3=4;
    vvvf in4=layer_conv(fc1_file,in3,out_channels3,in_channels3,kernel_size_3,argv[2]);
    threeDrelu(in4);
    //////////////
   

    
    ////////////Layer 6//////
    //////in4 + fc2 -> in5////////
    long out_channels4=10;
    long in_channels4=500;
    long kernel_size_4=1;
    vvvf in5=layer_conv(fc2_file,in4,out_channels4,in_channels4,kernel_size_4,argv[2]);
    ////////
   

    vector < float > ans_prob (out_channels4);
    vector < pair<float,int> > ans_prob_final (out_channels4);
    
    for(int i=0;i<out_channels4;i++)
        ans_prob[i]=in5[i][0][0];
    softmax(ans_prob);

    
    for(int i=0;i<out_channels4;i++)
        ans_prob_final[i]=make_pair(ans_prob[i],i);
    
    
    
    sort(ans_prob_final.begin(),ans_prob_final.end());
    
    
    cout<<"TOP CLASSES\n";
    for(int i=9;i>=5;i--)
        cout<<ans_prob_final[i].second<<" "<<ans_prob_final[i].first*100<<endl;
    
    
    return 0;
}
