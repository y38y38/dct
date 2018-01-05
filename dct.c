#include <stdio.h>
#include <math.h>

#define MAX_X   (8)
#define MAX_Y   (8)
/*      y  x */
int org[MAX_Y][MAX_X] =
{
{-172, -171, -172, -172, -170, -160, -145, -130}, 
{-172, -172, -172, -170, -165, -150, -134, -119}, 
{-172, -173, -171, -164, -153, -139, -125, -113}, 
{-173, -173, -166, -152, -136, -122, -115, -111}, 
{-175, -170, -154, -133, -113, -103, -107, -112}, 
{-170, -159, -136, -115, -96 , -93 , -102, -114}, 
{-158, -137, -117, -98 , -87 , -91 , -104, -118}, 
{-131, -117, -103, -94 , -96 , -104, -114, -125}, 
};

double result[MAX_Y][MAX_X];
double idct_result[MAX_Y][MAX_X];

double dct(int h, int v)
{
    int x=0,y=0;
    double value = 0;
    for(y=0;y<MAX_Y;y++) {
        for(x=0;x<MAX_X;x++) {
            value += org[y][x] *  cos((M_PI * v * ((2.0 * y) + 1.0)) / 16.0) * cos((M_PI * h * ((2.0 * x) + 1.0)) / 16.0);
        }
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

double idct(int y, int x)
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
            value += c_v * c_u * result[h][v] * cos((M_PI * v * ( (2.0 * y) + 1.0)) / 16.0) * cos((M_PI * h  * ((2.0 * x) + 1.0)) / 16.0);
        }
    }
    return value;
}

int main(void) {
    int x,y,h,v;
    printf("orginal\n");
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            printf("%d ", org[y][x]);
        }
        printf("\n");
    }
    printf("\n");

    printf("dct result\n");
    for (h=0;h<MAX_Y;h++) {
        for (v=0;v<MAX_X;v++) {
            result[h][v] = dct(h, v);
            printf("%lf ", result[h][v]);
        }
        printf("\n");
    }
    printf("\n");

    
    printf("idct result\n");
    for (y=0;y<MAX_Y;y++) {
        for (x=0;x<MAX_X;x++) {
            idct_result[y][x] = idct(y, x);
            printf("%lf ", idct_result[y][x]);
        }
        printf("\n");
    }
    printf("\n");


    return 0;
}
