

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



store(char * pass, int hash)
{
	// TODO make it store the values
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
	int hash;
	char tempPass[4];
	for (int i = 0; i < 4; ++i)
		tempPass[i] = pass[i];

	for (int i = 0; i < TABLE_WIDTH; ++i)
	{
		hash = getHash(tempPass);
		inverseHash(hash, tempPass);
	}

	return hash;
}

main(int argc, char *argv[])
{
	int carries;

	for (int i = 0; i < TABLE_HEIGHT; ++i)
	{
		result = getFinalHash(pass); // result is 32 bits of MD5 -- there is a BUG here, oh well.
		store(pass, result);


		carries = increment_pass(pass);

	}

// Note if you store hashes, do not use human readable HEX, 
// but write the integer to file, raw bits.
 
};

