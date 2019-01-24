#ifndef vvf
#define vvf vector < vector < float > >
#endif

using namespace std;

struct c_element_struct;

void pthread_dgemm (double* A,double *B, double *C , long long x, long long y,long long z);


void* c_element (void* arg);

vvf pthread_conv(vvf a,vvf b,long pad_size);
