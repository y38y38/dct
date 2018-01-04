#include <stdio.h>
#include <math.h>

/*      y  x */
int org[8][8] =
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

double dct(int h, int v)
{
    int x=0,y=0;
    double value = 0;
    for(y=0;y<8;y++) {
        for(x=0;x<8;x++) {
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

int main(void) {
    int x,y,h,v;
    double result;
    printf("orginal\n");
    for (y=0;y<8;y++) {
        for (x=0;x<8;x++) {
            printf("%d ", org[y][x]);
        }
        printf("\n");
    }
    printf("\n");

    printf("result\n");
    for (h=0;h<8;h++) {
        for (v=0;v<8;v++) {
            result = dct(h, v);
            printf("%lf ", result);
        }
        printf("\n");
    }
    return 0;
}
