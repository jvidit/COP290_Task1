#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <vector>

using namespace std;

#define vd vector < double >

double mean(vd v)
{
    double ans=0;
    for(int i=0;i<10;i++)
        ans+=v[i];
    
    return ans/double(10);
}

double stddev(vd v)
{
    double mu=mean(v);
    
    double ans=0;
    for(int i=0;i<10;i++)
        ans+=(v[i]-mu)*(v[i]-mu);
    return sqrt(ans/double(10));
}




int main()
{
    double temp;
    fstream f1,f2;
    f1.open("data.txt");
    f2.open("time.txt");
    
    int arr[5]={100,150,200,250,300};
    
    for(int i=0;i<5;i++)
    {
        vd v1,v2,v3;
        for(int j=0;j<10;j++)
        {
            f1>>temp;
            v1.push_back(temp/1000);
            f1>>temp;
            v2.push_back(temp/1000);
            f1>>temp;
            v3.push_back(temp/1000);
        }
        for(int j=0;j<10;j++)
        {
            f2<<v1[j]<<" pthread-"<<arr[i]<<" "<<mean(v1)<<" "<<stddev(v1)<<endl;
            f2<<v2[j]<<" openblas-"<<arr[i]<<" "<<mean(v2)<<" "<<stddev(v2)<<endl;
            f2<<v3[j]<<" mkl-"<<arr[i]<<" "<<mean(v3)<<" "<<stddev(v3)<<endl;
        }
    }
    return 0;
}
