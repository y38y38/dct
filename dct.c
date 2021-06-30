#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_X   (8)
#define MAX_Y   (8)

//#define DATA1
#define DATA2


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
#if 1
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
#else
int org[MAX_X * MAX_Y] =
{
0, 1 ,2, 3, 4, 5, 6, 7, 
8, 9, 10, 11, 12, 13, 14, 15,
16, 17, 18,19,20,21,22,23,
24,25,26,27,28,29,30,31,
32,33,34,35,36,37,38,39,
40,41,42,43,44,45,46,47,
48,49,50,51,52,53,54,55,
56,57,58,59,60,61,62,63,
};


#endif

#endif

#define BAISUU (65536)
#define MATH_COS_PI_4	 (46340)
#define MATH_SIN_PI_8    (25079)
#define MATH_COS_PI_8    (60547)
#define MATH_COS_3_PI_8  (25079)
#define MATH_SIN_3_PI_8  (60547)
#define MATH_SIN_PI_16   (12785)
#define MATH_COS_PI_16   (64276 )
#define MATH_SIN_5_PI_16 (54491 )
#define MATH_COS_5_PI_16 (36409)
#define MATH_SIN_3_PI_16 (36409)
#define MATH_COS_3_PI_16 (54491 )
#define MATH_SIN_7_PI_16 (62276 )
#define MATH_COS_7_PI_16 (12785)

void first_dct1(int32_t *in, int32_t *out) {
	int32_t step1[8];
	int32_t step2[8];
	int32_t step3[8];
	int32_t step4[8];

	//n+1
	step1[0] = in[0] + in[7];
	step1[1] = in[1] + in[6];
	step1[2] = in[2] + in[5];
	step1[3] = in[3] + in[4];

//	step1[4] = -1 * in[4] + in[3];
	step1[4] = in[3] - in[4];

//	step1[5] = -1 * in[5] + in[2];
	step1[5] = in[2] -in[5];

	//step1[6] = -1 * in[6] + in[1];
	step1[6] = in[1] - in[6];
	
	
	//step1[7] = -1 * in[7] + in[0];
	step1[7] = in[0] - in[7];


	//n+2

	step2[0] = step1[0] + step1[3];
	step2[1] = step1[1] + step1[2];
	//step2[2] = (-1) * step1[2] + step1[1];
	step2[2] =  step1[1] -step1[2];

	//step2[3] = (-1) * step1[3] + step1[0];
	step2[3] = step1[0] - step1[3];

	
	step2[4] = step1[4];

//	step2[5] = (step1[5] * (-1) * cos(M_PI / 4)) + (step1[6] * cos(M_PI/4)) ;
//	step2[5] =  (step1[6] * cos(M_PI/4)) - (step1[5]  * cos(M_PI / 4));
	step2[5] =  ((step1[6] * MATH_COS_PI_4)>>16) - ((step1[5]  * MATH_COS_PI_4)>>16);

	step2[6] = ((step1[6] * MATH_COS_PI_4)>>16) + ((step1[5] * MATH_COS_PI_4)>>16);

	step2[7] = step1[7];


	//n+3
 	step3[0] = ((step2[0] * MATH_COS_PI_4)>>16) + ((step2[1] * MATH_COS_PI_4)>>16);

	//step3[1] = (step2[1] * (-1) * cos(M_PI / 4) ) + (step2[0] * cos(M_PI/4));
	step3[1] =  ((step2[0] * MATH_COS_PI_4)>>16) - ((step2[1] *  MATH_COS_PI_4 )>>16);
	
	step3[2] = ((step2[2] * MATH_SIN_PI_8)>>16) + (( step2[3] * MATH_COS_PI_8)>>16);
	//step3[3] = (step2[3] * cos( 3 * M_PI / 8)) + (step2[2] * (-1) * sin( 3 *  M_PI / 8));
	step3[3] = ((step2[3] * MATH_COS_3_PI_8)>>16) - ((step2[2]  * MATH_SIN_3_PI_8)>>16);

	step3[4] = step2[4] + step2[5];
	//step3[5] = (-1) * step2[5] + step2[4];
	step3[5] = step2[4] - step2[5];


	//step3[6] = (-1) * step2[6] + step2[7];
	step3[6] = step2[7] - step2[6];

	step3[7] = step2[6] + step2[7];

	//n+4
	step4[0] = step3[0];
	step4[1] = step3[1];
	step4[2] = step3[2];
	step4[3] = step3[3];

	step4[4] = ((step3[4] * MATH_SIN_PI_16)>>16) + ((step3[7] * MATH_COS_PI_16)>>16);
	step4[5] = ((step3[5] * MATH_SIN_5_PI_16)>>16) + ((step3[6] * MATH_COS_5_PI_16)>>16);
	//step4[6] = (step3[6] * cos((3 * M_PI) / 16)) + (step3[5] * (-1) * sin((3 * M_PI)  / 16));
	step4[6] = ((step3[6] * MATH_COS_3_PI_16)>>16) - ((step3[5]  * MATH_SIN_3_PI_16)>>16);

	//step4[7] = (step3[7] * cos( 7 *  M_PI / 16)) + (step3[4] * (-1) * sin(( 7 * M_PI) / 16));
	step4[7] = ((step3[7] * MATH_COS_7_PI_16)>>16) - ((step3[4] *  MATH_SIN_7_PI_16)>>16);



	int32_t step5[8];
	step5[0] = step4[0];
	step5[1] = step4[4];
	step5[2] = step4[2];
	step5[3] = step4[6];
	step5[4] = step4[1];
	step5[5] = step4[5];
	step5[6] = step4[3];
	step5[7] = step4[7];

	//n+3
	out[0] = step5[0] >>1;
	out[1] = step5[1] >>1;
	out[2] = step5[2] >>1;
	out[3] = step5[3] >>1;
	out[4] = step5[4] >>1;
	out[5] = step5[5] >>1;
	out[6] = step5[6] >>1;
	out[7] = step5[7] >>1;
	return;

}



int dct_block_first(int * block, int *out) {
	int i,j;
	int32_t in[64];
	int32_t out1[64];
	int32_t out2[64];
	int32_t out3[64];
	int16_t out4[64];
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

	for(i=0;i<8;i++) {
		out4[(i*8)]   = (int16_t)out3[i];
		out4[(i*8)+1] = (int16_t)out3[8+i];
		out4[(i*8)+2] = (int16_t)out3[16+i];
		out4[(i*8)+3] = (int16_t)out3[24+i];
		out4[(i*8)+4] = (int16_t)out3[32+i];
		out4[(i*8)+5] = (int16_t)out3[40+i];
		out4[(i*8)+6] = (int16_t)out3[48+i];
		out4[(i*8)+7] = (int16_t)out3[56+i];
	}
	int x,y;
	printf("dct result int\n");
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            printf("%x ", out4[(y * MAX_X) + x]);
        }
        printf("\n");
    }
    printf("\n");

	return 0;
}



int  result[MAX_X * MAX_Y];
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




void getinputdata(FILE *in){
	char buf[1024];

	int counter = 0;
	for(;;) {
		char *ret = fgets(buf, 1024, in);
		if (ret == NULL) {
			printf("erro %d\n", __LINE__);
			return;
		}
		org[counter] = atoi(buf);

		counter++;
		if (counter == 64) {
			break;
		}
	}
	return;
}
int main(int argc, char **argv) {

	FILE *in = fopen(argv[1], "r");
	getinputdata(in);
	fclose(in);

    int x,y;
    printf("orginal\n");
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            printf("%d ", org[(y * MAX_X) + x]);
        }
        printf("\n");
    }
    printf("\n");

    printf("dct result\n");


	FILE *out = fopen(argv[2], "w");
	

	int h,v;

	dct_block_first(org, result);
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            printf("%d ", result[(v * MAX_X) + h]);
			fprintf(out, "%d\n", result[(v * MAX_X) + h]);
        }
        printf("\n");
    }
	fclose(out);

    return 0;
}
