#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define MAX_X   (8)
#define MAX_Y   (8)

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
	step3[3] = (step2[3] * sin( M_PI / 8)) + (step2[2] * (-1) * cos(  M_PI / 8));

	step3[4] = step2[4] + step2[5];
	step3[5] = (-1) * step2[5] + step2[4];
	step3[6] = (-1) * step2[6] + step2[7];
	step3[7] = step2[6] + step2[7];

	step4[0] = step3[0];
	step4[1] = step3[1];
	step4[2] = step3[2];
	step4[3] = step3[3];

	step4[4] = (step3[4] * sin(M_PI / 16)) + (step3[7] * cos(M_PI/16));
	step4[5] = (step3[5] * cos((3 * M_PI) / 16)) + (step3[6] * sin(3 * M_PI/ 16));
	step4[6] = (step3[6] * cos((3 * M_PI) / 16)) + (step3[5] * (-1) * sin((3 * M_PI)  / 16));
	step4[7] = (step3[7] * sin(  M_PI / 16)) + (step3[4] * (-1) * cos(( M_PI) / 16));

	double step5[8];
	step5[0] = step4[0];
	step5[1] = step4[4];
	step5[2] = step4[2];
	step5[3] = step4[6];
	step5[4] = step4[1];
	step5[5] = step4[5];
	step5[6] = step4[3];
	step5[7] = step4[7];


	out[0] = step5[0] * 0.5;
	out[1] = step5[1] * 0.5;
	out[2] = step5[2] * 0.5;
	out[3] = step5[3] * 0.5;
	out[4] = step5[4] * 0.5;
	out[5] = step5[5] * 0.5;
	out[6] = step5[6] * 0.5;
	out[7] = step5[7]  * 0.5;
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
	for(i=0;i<64;i++) {
		out[i] = out3[i];
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
    int x,y,h,v;
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
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            result[(v * MAX_X) + h] = dct(h, v);
            printf("%lf ", result[(v * MAX_X) + h]);
        }
        printf("\n");
    }
#else
	dct_block_first(org, result);
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            printf("%lf ", result[(v * MAX_X) + h]);
        }
        printf("\n");
    }
#endif

    printf("\n");

    
    printf("idct result\n");
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            idct_result[(y * MAX_X) + x] = idct(x, y);
            printf("%lf ", idct_result[(y * MAX_X) + x]);
        }
        printf("\n");
    }
    printf("\n");


    return 0;
}
