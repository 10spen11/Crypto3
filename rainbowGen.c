

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "rainbowFuncs.h"

// input : ./prog filename

char pass[5]; // 4 character password, with null at end for printing
char hash[8]; // 8 character password
int intHash; // int representation of the hash
int *hash_pointer, * temp;
int n, *temp;
unsigned int result;


struct hash_entry {
	char pass[5];
	int hash;
} main_table[TABLE_HEIGHT];
int mainTableIndex = 0;

void sortTable();

int compareEntries(const void* a, const void* b)
{
	struct hash_entry* a2 = (struct hash_entry*) a;
	struct hash_entry* b2 = (struct hash_entry*) b;
	return (b2->hash > a2->hash)?-1:1;
}

void store(char* pass, int hash)
{
	for (int i = 0; i < 5; ++i)
		main_table[mainTableIndex].pass[i] = pass[i];
	main_table[mainTableIndex].hash = hash;
	mainTableIndex++;
}

void storeFinal()
{
	FILE* fptr;
	sortTable();

	fptr = fopen("./rainbow-hashes.txt", "w");
	if (fptr == NULL)
	{
		printf("Problems opening the rainbow-hashing file!");
		return;
	}
	for (int i = 0; i < TABLE_HEIGHT; ++i)
	{
		fprintf(fptr, "%s %d\n", main_table[i].pass, main_table[i].hash);
	}
	
	fclose(fptr);
}

void sortTable()
{
	qsort(main_table, TABLE_HEIGHT, sizeof(struct hash_entry), compareEntries);
	
}

// returns the hash that results from the end of a rainbow table
int getFinalHash(char* pass)
{
	unsigned int hash = 0;
	char tempPass[5];
	for (int i = 0; i <= 4; ++i)
		tempPass[i] = pass[i];


	for (int i = 0; i < TABLE_WIDTH; ++i)
	{
		hash = getHash(tempPass);
		inverseHash(hash, tempPass);

		
	}

	return hash;
}

void main(int argc, char *argv[])
{
	/*
	FILE* fptr;
	fptr = fopen("./rainbow-hashes.txt", "w");
	fclose(fptr);
	*/
    for (int i = 0; i < 4; ++i)
    {
        pass[i] = '0'; // all 0s in password field
    }

	int carries;

	for (int i = 0; i < TABLE_HEIGHT; ++i)
	{
		result = getFinalHash(pass); // result is 32 bits of MD5 -- there is a BUG here, oh well.
		store(pass, result);
		carries = increment_pass(pass);
	}

	storeFinal();

// Note if you store hashes, do not use human readable HEX, 
// but write the integer to file, raw bits.
 
};

