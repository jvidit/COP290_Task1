#ifndef vvf
#define vvf vector < vector < float > >
#endif

using namespace std;

void vvf_to_arr(vvf v, double ans[]);

vvf arr_to_vvf(double arr[],long r,long c);


////////////Padding///////////////
void padding(vvf &v, long pad);

////////////////////////////////////


////////////Matrix Multiplication//////////////
vvf mat_mul(vvf a,vvf b);

///////////////////////////////////////////////


///////////////Normal Convolution//////////////
void flip(vvf&v);



vvf normal_conv(vvf a,vvf b,long pad_size);



vvf mm_conv(vvf a,vvf b,long pad_size);
///////////////////////////////////////////

