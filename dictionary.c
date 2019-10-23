

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


#include "rainbowFuncs.h"

// input : ./prog filename

char pass[5]; // 4 character password, with null at end for printing
char hash[8]; // 8 character password
int intHash; // int representation of the hash
int* hash_pointer, * pass_pointer, * temp;
int n, result, * temp;

#define WORD_COUNT 500

struct password {
	char pass[5];
} main_table[WORD_COUNT];

void load_word_table()
{
	FILE* fptr;
	fptr = fopen("./words.txt", "r");
	if (fptr == NULL)
	{
		printf("Problems opening the words file!");
		return;
	}
	int i = 0;
	for(int i = 0; i < WORD_COUNT; ++i)
	{
		fscanf(fptr, "%s\n", &main_table[i].pass);
		//printf("\nString : %s int : %d", main_table[i].pass, main_table[i].hash);
	}

	fclose(fptr);
}



void main(int argc, char* argv[])
{
	load_word_table();

	hash_pointer = (int*)hash; // get an int pointer to the password store
	*hash_pointer = 0; // all nulls in password field
	if (argc != 1) { printf("Usage: No Arguments\n", argv[0]); exit(0); };
	hash_pointer = (int*)hash; // get an int pointer to the password store
	printf("Enter a 8 character hex value to un-hash: "); fflush(0);
	n = read(0, hash_pointer, 8); // get 8 bytes, ignore extra
							  // if hash too short, will be detected later.

	check_hash(hash); // sanity check

	intHash = strtoul(hash, NULL, 16);

	bool success = false;

	for (int upperCase = 0; upperCase <= 32; upperCase += 32)
	for (int i = 0; i < WORD_COUNT && success == false; ++i)
	{
		for(int j = 0; j < 4; ++j)
			pass[j] = main_table[i].pass[j] - upperCase;
		result = getHash(pass);
		if (result == intHash)
		{
			success = true;
		}
	}

	if (success == true)
	{
		pass[4] = '\0';
		printf("Found Password: %s\n", pass);
	}
	else
	{
		printf("No password found\n");
	}

// Note if you store hashes, do not use human readable HEX, 
// but write the integer to file, raw bits.

};

