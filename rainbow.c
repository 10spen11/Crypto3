

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



struct hash_entry {
	char pass[5];
	int hash;
} main_table[TABLE_HEIGHT];

void load_hash_table()
{
	FILE* fptr;
	fptr = fopen("./rainbow-hashes.txt", "r");
	if (fptr == NULL)
	{
		printf("Problems opening the rainbow-hashing file!");
	}
	int i = 0;
	for(int i = 0; i < TABLE_HEIGHT; ++i)
	{
		fscanf(fptr, "%s %d\n", &main_table[i].pass, &main_table[i].hash);
		printf("\nString : %s int : %d", main_table[i].pass, main_table[i].hash);
	}

	fclose(fptr);
}



// TODO
// returns which index the final hash is located at
// returns -1 if it is not in the table
int getIndexOfHash(int hash)
{
	return -1;
}


// TODO
// Scans the entry at the given index for the intHash given
// sets the password to the password immediately preceeding the hash
void searchRainbowEntry(int index, int intHash, char * pass)
{

}


void main(int argc, char* argv[])
{
	load_hash_table();

	hash_pointer = (int*)hash; // get an int pointer to the password store
	*hash_pointer = 0; // all nulls in password field
	if (argc != 1) { printf("Usage: No Arguments\n", argv[0]); exit(0); };
	hash_pointer = (int*)hash; // get an int pointer to the password store
	printf("Enter a 8 character hex value to un-hash: "); fflush(0);
	n = read(0, hash_pointer, 8); // get 8 bytes, ignore extra
							  // if password too short, will be detected later.

	check_hash(hash); // sanity check

	intHash = (int)strtol(hash, NULL, 16);

	for (int i = 0; i < 4; ++i)
		pass[i] = '0'; // all 0s in password field

	pass_pointer = (int*)pass; // get an int pointer to the password store

	pass[4] = '\0';


	int carries;
	bool success = false;
	for (int i = 0; i < TABLE_WIDTH; ++i)
	{

		result = getHash(pass); // result is 32 bits of MD5 -- there is a BUG here, oh well.

		int index = getIndexOfHash(result);
		if (index != -1)
		{
			searchRainbowEntry(index, intHash, pass);
			success = true;
			break;
		}

		inverseHash(result, pass);

	}

	if (success)
	{
		pass[4] = '\0';
		printf("Found Password: %s\n", pass);
	}
	else
	{
		printf("No password found\n");
	}
	printf("%x\n", result); // print a human readable version of hash (using hex conversion)

// Note if you store hashes, do not use human readable HEX, 
// but write the integer to file, raw bits.

};

