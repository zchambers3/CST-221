//Zack Chambers
//CST 221
//January 20, 2019
//John Zupan

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main() {
srand(time(NULL));
	int r;
	r=rand()%4096;
	printf(" \n%i",r);
	printf(" \nbinary = 0x%08x", r);
	printf(" \nhexadecimal = %04x",r);
	printf(" \nNumber is Shifted By 16 Bits : %d\n",r << 16);
return 0;
}
