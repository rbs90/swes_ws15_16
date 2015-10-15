#include <stdio.h>

int main(int argc, char **argv){
	if (argc != 2){
		printf("Usage: ./bitreverse <0-255>\n");
		return 1;
	}

	unsigned char byte_in = (unsigned char) atoi(argv[1]);
	printf("%d\n", (unsigned char) ~byte_in);
	return 0;
}
