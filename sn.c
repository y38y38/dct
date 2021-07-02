#include <stdio.h>
#include <math.h>
#include "utility.h"
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

int org[64];
double idct_result[64];


int main(int argc, char **argv) {
	short in_data[64];
	short out_data[64];


	FILE *in = fopen(argv[1], "r");
	getinputdata(in, org);
	fclose(in);

	FILE *in2 = fopen(argv[2], "r");
	getinputdoubledata(in2, idct_result);
	fclose(in2);



	for (int i=0;i<64;i++) {
		in_data[i] = (short)org[i];
	}
	for (int i=0;i<64;i++) {
		out_data[i] = (short)idct_result[i];
//		printf("result %d %lf\n", out_data[i], idct_result[i]);
	}
	int max_diff;
	double psnr = sn(in_data, out_data, 64, 10, &max_diff );
	if (max_diff > 10) {
		printf("err");
	}
	printf("psnr %lf %d\n", psnr, max_diff);
    return 0;
}
