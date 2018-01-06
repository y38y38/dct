#include <stdio.h>
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
    for (v=0;v<MAX_Y;v++) {
        for (h=0;h<MAX_X;h++) {
            result[(v * MAX_X) + h] = dct(h, v);
            printf("%lf ", result[(v * MAX_X) + h]);
        }
        printf("\n");
    }
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
