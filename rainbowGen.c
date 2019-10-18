

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "md5.h" 
#include "rainbowFuncs.h"

// input : ./prog filename

char pass[5]; // 4 character password, with null at end for printing
char hash[8]; // 8 character password
int intHash; // int representation of the hash
int *hash_pointer, * pass_pointer, * temp;
int n, result, *temp;
MD5_CTX mdContext;  // needed to compute MD5



void store(char* pass, int hash)
{
	// TODO make it store the values

    FILE *fptr;
    fptr = fopen("./rainbow-hashes.txt", "a");
    if(fptr == NULL)
    {
        printf("Problems opening the rainbow-hashing file!");
    }
    fprintf(fptr, "%s %d\n", pass, hash);
    fclose(fptr);
}


int getHash()
{
	MD5Init(&mdContext);  // compute MD5 of password
	MD5Update(&mdContext, pass_pointer, 4);
	MD5Final(&mdContext);
	temp = (int*)& mdContext.digest[12];

	return *temp;
}

check_hash(char * hash)
{
  int i = 0;
  for (i=0;i<8;i++) { 
       if (!(((hash[i] >= 'a') && (hash [i] <= 'f'))
             || ((hash[i] >= '0') && (hash [i] <= '9')))) {
                   printf("Hash not as per specifications\n");
                   exit(0);
       };
  };
};

// returns the hash that results from the end of a rainbow table
int getFinalHash(char* pass)
{
	int hash = 0;
	char tempPass[5];
	for (int i = 0; i <= 4; ++i)
		tempPass[i] = pass[i];
	
	for (int i = 0; i < TABLE_WIDTH; ++i)
	{
		hash = getHash();
		inverseHash(hash, tempPass);
	}

	return hash;
}

main(int argc, char *argv[])
{
    pass_pointer = (int*)pass; // get an int pointer to the password store

    for (int i = 0; i < 4; ++i)
    {
        pass[i] = '0'; // all 0s in password field
    }

	int carries;

	for (int i = 0; i < TABLE_HEIGHT; ++i)
	{
		result = getFinalHash(pass); // result is 32 bits of MD5 -- there is a BUG here, oh well.
		store(&pass, result);
		carries = increment_pass(pass);
	}

// Note if you store hashes, do not use human readable HEX, 
// but write the integer to file, raw bits.
 
};

