#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//each row group is 4 seperate elements
#define ROW_GROUP_WIDTH 4
#define ROW_WIDTH 16
#define BASE_SIZE 8

void print_char_hex(int c){
	const char* hexa_chars = "0123456789ABCDEF";

	printf("%c%c",hexa_chars[(c/16)%16],hexa_chars[c%16]);
};

void write_base(char* base, int base_num){
	const char* hexa_chars = "0123456789ABCDEF";
	int i = 0;

	while (base_num > 0){
		base[BASE_SIZE - 1 - i] = hexa_chars[base_num%16];
		base_num/=16;
		i++;
	}
};

void clear_base(char* base){
	for (int i = 0; i < BASE_SIZE; i++){
		base[i] = '0';
	}
};

int main(int argc, char **argv){
	FILE* file;

	if(argc < 2){
		printf("Please put a path to the file\n");
		return 0;
	}

	file = fopen(argv[1],"r");

	if(!file){
		printf("Invalid path to file\n");
		return 0;
	}

	char base[BASE_SIZE+1] = {'\0'};
	clear_base(base);
	char ascii[ROW_WIDTH+1] = {'\0'};


	int ch;
	int i = 0;
	int pos = i%ROW_WIDTH;

	while ((ch = getc(file)) != EOF){
		pos = i%ROW_WIDTH;
		if (ch > 126 || ch < 33) ascii[pos] = '.';
		else ascii[pos] = ch;

		if (pos == 0){
			write_base(base,i);
			printf("%s|",base);
		}else printf(" ");
		if (pos%ROW_GROUP_WIDTH == 0) printf(" ");

		print_char_hex(ch);

		if (pos == ROW_WIDTH-1) printf("  |%s\n",ascii);
		i++;
	}

	pos = i%ROW_WIDTH;
	if (i%ROW_WIDTH == 0) return 0;

	ascii[pos] = '\0';
	for (int j = 0; j < (ROW_WIDTH - pos)*3 + ROW_WIDTH/ROW_GROUP_WIDTH - (pos-1)/(ROW_WIDTH/ROW_GROUP_WIDTH) - 1; j++){
		printf(" ");
	}

	printf("  |%s\n",ascii);


	return 0;
};
