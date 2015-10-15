#include <stdio.h>

int main(int argc, char **argv){
	if (argc != 2){
		printf("Usage: ./bitcount <32bit Integer>\n");
		return 1;
	}

	int in_value = atoi(argv[1]);
	int count = 0;

	while(in_value > 0){
		count += in_value & 1;
		in_value = in_value >> 1;
	}

	printf("%d\n", count);
	return 0;
}
