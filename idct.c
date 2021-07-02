#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utility.h"


#define MAX_X   (8)
#define MAX_Y   (8)


int  result[MAX_X * MAX_Y];

double idct_result[MAX_X * MAX_Y];


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



int main(int argc, char **argv) {

	FILE *in = fopen(argv[1], "r");
	getinputdata(in, result);
	fclose(in);

    int x,y;
    memset(idct_result, 0x0, sizeof(idct_result));

#if 1
    
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            idct_result[(y * MAX_X) + x] = idct(x, y);
        }
    }
#endif
	FILE *out = fopen(argv[2], "w");
	

	int h,v;

	for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
			fprintf(out, "%f\n", idct_result[(v * MAX_X) + h]);
        }
    }
	fclose(out);



    return 0;
}

