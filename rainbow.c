

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
		//printf("\nString : %s int : %d", main_table[i].pass, main_table[i].hash);
	}

	fclose(fptr);
}



// returns which index the final hash is located at
// returns -1 if it is not in the table
int getIndexOfHash(int hash)
{
	int minIndex = 0;
	int maxIndex = TABLE_HEIGHT - 1;

	while (minIndex < maxIndex)
	{

		// define what we're searching for
		int indexToQuestion = (minIndex + maxIndex) / 2; //cut the list in half
		int questionedHash = main_table[indexToQuestion].hash;

		//printf("Questioning index: %i Hash: %i Wanted: %i\n", indexToQuestion, questionedHash, hash);

		//we've found what we're searching for
		if (questionedHash == hash)
		{
			maxIndex = indexToQuestion;
			minIndex = indexToQuestion;
		}
		else if (hash > questionedHash) // the hash we are looking for is above the index we're looking at
		{
			minIndex = indexToQuestion + 1; // raise the min index
		}
		else // the hash we are looking for is below the index we're looking at
		{
			maxIndex = indexToQuestion - 1; // lower the max index
		}
	}
	
	if ((minIndex == maxIndex) && (main_table[minIndex].hash == hash))
	{
		while (main_table[minIndex].hash == hash)
		{
			minIndex--;
		}
		return minIndex + 1;
	}
	else
	{
		return -1;
	}
}


// TODO
// Scans the entry at the given index for the intHash given
// sets the password to the password immediately preceeding the hash
bool searchRainbowEntry(int index, int intHash, char * pass)
{
	
	struct hash_entry entry = main_table[index];
	char currentPass[5];
	for (int i = 0; i < 5; ++i)
	{
		currentPass[i] = entry.pass[i];
	}
	int currentHash = getHash(currentPass);
	for (int i = 0; i < TABLE_WIDTH; ++i)
	{
		//printf("%i: Current Password: %s Current Hash: %i Desired hash: %i\n", i, currentPass, currentHash, intHash);
		if (currentHash == intHash)
		{
			break;
		}
		inverseHash(currentHash, currentPass); // go on to the next password
		currentHash = getHash(currentPass); // hash the password for checking
	}
	if (currentHash != intHash)
	{
		//printf("False alarm\n");
		return false;
	}
	else
	{
		for (int i = 0; i < 5; ++i)
		{
			pass[i] = currentPass[i];
		}
		return true;
	}
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
							  // if hash too short, will be detected later.

	check_hash(hash); // sanity check

	intHash = strtoul(hash, NULL, 16);

	result = intHash;

	bool success = false;
	bool isValid;
	for (int i = 0; i < TABLE_WIDTH; ++i)
	{

		int index = getIndexOfHash(result);
		while (index != -1 && main_table[index].hash == result)
		{
			//printf("Searching index: %i Iterated %i times\n", index, i);
			isValid = searchRainbowEntry(index, intHash, pass);
			
			if (isValid)
			{
				success = true;
				break;
			}
			index++;
		}

		if (success == true)
		{
			break;
		}

		inverseHash(result, pass);
		result = getHash(pass); // result is 32 bits of MD5 -- there is a BUG here, oh well.
		//printf("Pass: %s Hash: %i Iterated %i times\n", pass, result, i);
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

