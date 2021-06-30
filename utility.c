#include <stdio.h>

#include <stdlib.h>

#include "utility.h"


void getinputdata(FILE *in,  int *data)
{
	char buf[1024];

	int counter = 0;
	for(;;) {
		char *ret = fgets(buf, 1024, in);
		if (ret == NULL) {
			printf("erro %d\n", __LINE__);
			return;
		}
		data[counter] = atoi(buf);

		counter++;
		if (counter == 64) {
			break;
		}
	}
	return;
}

void getinputdoubledata(FILE *in,  double *data)
{
	char buf[1024];

	int counter = 0;
	for(;;) {
		char *ret = fgets(buf, 1024, in);
		if (ret == NULL) {
			printf("erro %d\n", __LINE__);
			return;
		}
		data[counter] = atof(buf);

		counter++;
		if (counter == 64) {
			break;
		}
	}
	return;
}

