#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define MAX_X   (8)
#define MAX_Y   (8)

//#define DATA1
//#define DATA2


#define __BUTTERFLY1__


#ifdef DATA1
int org[MAX_X * MAX_Y] =
{
-172, -172, -172, -173, -175, -170, -158, -131, 
-171, -172, -173, -173, -170, -159, -137, -117, 
-172, -172, -171, -166, -154, -136, -117, -103, 
-172, -170, -164, -152, -133, -115, -98 , -94 ,
-170, -165, -153, -136, -113, -96 , -87 , -96 ,
-160, -150, -139, -122, -103, -93 , -91 , -104, 
-145, -134, -125, -115, -107, -102, -104, -114, 
-130, -119, -113, -111, -112, -114, -118, -125, 
};

#else

int org[MAX_X * MAX_Y] =
{
93 ,77, 52, 64, 77, 63, 65, 72, 
60, 64, 42, 45, 69, 68, 64, 69 ,
-40, -27, -38, -36, -8, 11, 18, 24, 
33, 38, 33, 24, 23, 21, 13, 8, 
89, 92, 92, 84, 78, 70, 59, 57, 
70, 72, 76, 74, 78, 86, 88, 92, 
63, 63, 68, 67, 65, 67, 67, 65, 
64, 65, 70, 70, 68, 65, 64, 66, 
};
#endif

int abs22(int val)
{
    if (val < 0) {
        //printf("m\n");
        return val * -1;
    } else {
        //printf("p\n");
        return val;
    }
}
int max(int a, int b)
{
    if( a > b) {
        return a;
    } else {
        return b;
    }
}
double sn( short *data1, short *data2, int num, int bit_num, int * max_diff)
{
	int sn_sum;
	*max_diff = 0;
	sn_sum = 0;
	for (int i = 0;i < num; i++) {

		short temp1 = *(data1 + i);
		short temp2 = *(data2 + i);
		//temp1 = temp1 >> (16 - bit_num);
		//temp2 = temp2 >> (16 - bit_num);
        //printf("%d %d\n",temp1, temp2);

		int a,b;
		a = (int)temp1;
		b = (int)temp2;

		int diff;
		diff = a;
		diff -= b;

        int abs = abs22(diff);
        *max_diff = max(*max_diff, abs);
		int x2 = diff * diff;

		sn_sum += x2;

	}
	double rmse = (double)sn_sum / num;

	rmse = sqrt(rmse);

	int max = ((1 << bit_num) - 1);

	double psnr = (rmse != 0) ? -20 * log10(rmse/max) : 120;

	return psnr;
}




void first_dct1(double *in, double *out) {
	double step1[8];
	double step2[8];
	double step3[8];
	double step4[8];


	step1[0] = in[0] + in[7];
	step1[1] = in[1] + in[6];
	step1[2] = in[2] + in[5];
	step1[3] = in[3] + in[4];
	step1[4] = -1 * in[4] + in[3];
	step1[5] = -1 * in[5] + in[2];
	step1[6] = -1 * in[6] + in[1];
	step1[7] = -1 * in[7] + in[0];



	step2[0] = step1[0] + step1[3];
	step2[1] = step1[1] + step1[2];
	step2[2] = (-1) * step1[2] + step1[1];
	step2[3] = (-1) * step1[3] + step1[0];

	
	step2[4] = step1[4];

	step2[5] = (step1[5] * (-1) * cos(M_PI / 4)) + (step1[6] * cos(M_PI/4)) ;
	step2[6] = (step1[6] * cos(M_PI/4)) + (step1[5] * cos(M_PI / 4));

	step2[7] = step1[7];



	step3[0] = (step2[0] * cos(M_PI / 4)) + (step2[1] * cos(M_PI/4));
	step3[1] = (step2[1] * (-1) * cos(M_PI / 4) ) + (step2[0] * cos(M_PI/4));

	step3[2] = (step2[2] * sin(M_PI / 8)) + ( step2[3] * cos(M_PI/8));
	step3[3] = (step2[3] * cos( 3 * M_PI / 8)) + (step2[2] * (-1) * sin( 3 *  M_PI / 8));

	step3[4] = step2[4] + step2[5];
	step3[5] = (-1) * step2[5] + step2[4];
	step3[6] = (-1) * step2[6] + step2[7];
	step3[7] = step2[6] + step2[7];

	step4[0] = step3[0];
	step4[1] = step3[1];
	step4[2] = step3[2];
	step4[3] = step3[3];

	step4[4] = (step3[4] * sin(M_PI / 16)) + (step3[7] * cos(M_PI/16));
	step4[5] = (step3[5] * sin((5 * M_PI) / 16)) + (step3[6] * cos(5 * M_PI/ 16));
	step4[6] = (step3[6] * cos((3 * M_PI) / 16)) + (step3[5] * (-1) * sin((3 * M_PI)  / 16));
	step4[7] = (step3[7] * cos( 7 *  M_PI / 16)) + (step3[4] * (-1) * sin(( 7 * M_PI) / 16));

	double step5[8];
	step5[0] = step4[0];
	step5[1] = step4[4];
	step5[2] = step4[2];
	step5[3] = step4[6];
	step5[4] = step4[1];
	step5[5] = step4[5];
	step5[6] = step4[3];
	step5[7] = step4[7];


	out[0] = step5[0] >>1;
	out[1] = step5[1] >>1;
	out[2] = step5[2] >>1;
	out[3] = step5[3] >>1;
	out[4] = step5[4] >>1;
	out[5] = step5[5] >>1;
	out[6] = step5[6] >>1;
	out[7] = step5[7]  >>1;
	return;

}


int dct_block_first(int * block, double *out) {
	int i,j;
	double in[64];
	double out1[64];
	double out2[64];
	double out3[64];
	for(i=0;i<64;i++) {
		in[i] = (double)block[i];
	}

	for(i=0;i < 64;i+=8) {
		first_dct1(in + i, out1 + i);
	}

	for(i=0;i<8;i++) {
		for(j=0;j<8;j++) {
				out2[i * 8 + j] = out1[j * 8 + i];
		}
	}

	for(i=0;i<64;i+=8) {
		first_dct1(out2 + i, out3 + i);
	}
	for(i=0;i<8;i++) {
		out[(i*8)] = out3[i];
		out[(i*8)+1] = out3[8+i];
		out[(i*8)+2] = out3[16+i];
		out[(i*8)+3] = out3[24+i];
		out[(i*8)+4] = out3[32+i];
		out[(i*8)+5] = out3[40+i];
		out[(i*8)+6] = out3[48+i];
		out[(i*8)+7] = out3[56+i];
	}

	return 0;
}



double result[MAX_X * MAX_Y];
double idct_result[MAX_X * MAX_Y];

double dct(int h, int v)
{
    int x=0,y=0;
    double value = 0;
    for(y=0;y<MAX_Y;y++) {
        for(x=0;x<MAX_X;x++) {
            double kc = cos((M_PI * v * ((2.0 * y) + 1.0)) / 16.0) * cos((M_PI * h * ((2.0 * x) + 1.0)) / 16.0);
            value += org[(y * 8) + x] *  kc;
        }
    }
    if ((h==1) && (v==0)) {
        //printf("\n h1 v0 %lf\n", value);
    }
    if ( h == 0) {
        value *= 0.5 / sqrt(2.0);
    } else {
        value *= 0.5;
    }
    if (v == 0) {
        value *= 0.5 / sqrt(2.0);
    } else {
        value *= 0.5;
    }

    return value;
}

#ifdef __CUDA__
__global__ void kernel(int * src, double *dst, int h, int v)
{
    int x=0,y=0;
    double value = 0;
    for(y=0;y<MAX_Y;y++) {
        for(x=0;x<MAX_X;x++) {
            double kc = cos((M_PI * v * ((2.0 * y) + 1.0)) / 16.0) * cos((M_PI * h * ((2.0 * x) + 1.0)) / 16.0);
            value += src[(y * 8) + x] *  kc;
        }
    }
    if ((h==1) && (v==0)) {
        //printf("\n h1 v0 %lf\n", value);
    }
    if ( h == 0) {
        value *= 0.5 / sqrt(2.0);
    } else {
        value *= 0.5;
    }
    if (v == 0) {
        value *= 0.5 / sqrt(2.0);
    } else {
        value *= 0.5;
    }
	*dst = value;
}
void dct_cuda(int* src, double *dst) {
#if 0
    int x,y,h,v;
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            result[(v * MAX_X) + h] = dct(h, v);
            printf("%lf ", result[(v * MAX_X) + h]);
        }
        printf("\n");
    }
#else

	int *cuda_src;
	double *cuda_dst;

	cudaMalloc((void**)&cuda_src, sizeof(int) * 64);
	cudaMalloc((void**)&cuda_dst, sizeof(double) * 64);
	cudaMemcpy(cuda_src,src, sizeof(int) * 64, cudaMemcpyHostToDevice);

    int h,v;
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            
			kernel<<<1,1>>>(cuda_src, &cuda_dst[(v * MAX_X) + h], h, v);
            //printf("%lf ", result[(v * MAX_X) + h]);
        }
    }

	cudaDeviceSynchronize();

	cudaMemcpy(dst, cuda_dst, sizeof(double) * 64, cudaMemcpyDeviceToHost);
	cudaFree(cuda_src);
	cudaFree(cuda_dst);

    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            //printf("%lf ", result[(v * MAX_X) + h]);
            printf("%lf ", dst[(v * MAX_X) + h]);
        }
        printf("\n");
	}
#endif
	return;
}
#endif

double idct(int x, int y)
{
    int h=0,v=0;
    double value = 0;
    double c_u=0;
    double c_v=0;
    for(h=0;h<MAX_Y;h++) {
        for(v=0;v<MAX_X;v++) {
            if (h==0) {
                c_u = 0.5 / sqrt(2.0);
            } else {
                c_u = 0.5;
            }
            if (v==0) {
                c_v = 0.5 /sqrt(2.0);
            } else {
                c_v = 0.5;
            }
            value += c_v * c_u * result[(v * MAX_X) + h] * cos((M_PI * v * ( (2.0 * y) + 1.0)) / 16.0) * cos((M_PI * h  * ((2.0 * x) + 1.0)) / 16.0);
        }
    }
    return value;
}

int main(void) {
    int x,y;
    memset(idct_result, 0x0, sizeof(idct_result));
    printf("orginal\n");
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            printf("%d ", org[(y * MAX_X) + x]);
        }
        printf("\n");
    }
    printf("\n");

    printf("dct result\n");
#if 1


	int h,v;

#ifdef __CUDA__
	dct_cuda(org, result);
#elif defined(__BUTTERFLY1__)
	dct_block_first(org, result);
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            printf("%lf ", result[(v * MAX_X) + h]);
        }
        printf("\n");
    }

#else
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            result[(v * MAX_X) + h] = dct(h, v);
            printf("%lf ", result[(v * MAX_X) + h]);
        }
        printf("\n");
    }

#endif

#else
#endif

    printf("\n");
#if 1
    
    printf("idct result\n");
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            idct_result[(y * MAX_X) + x] = idct(x, y);
            printf("%lf ", idct_result[(y * MAX_X) + x]);
        }
        printf("\n");
    }
    printf("\n");
#endif
	short in_data[64];
	short out_data[64];

	for (int i=0;i<64;i++) {
		in_data[i] = (short)org[i];
	}
	printf("out\n");
	for (int i=0;i<64;i++) {
		out_data[i] = (short)idct_result[i];
//		printf("result %d %lf\n", out_data[i], idct_result[i]);
	}
	int max_diff;
	double psnr = sn(in_data, out_data, 64, 10, &max_diff );

	printf("psnr %lf %d\n", psnr, max_diff);
    return 0;
}
