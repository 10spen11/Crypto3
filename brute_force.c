

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "md5.h" 

// input : ./prog filename

char pass[5]; // 4 character password, with null at end for printing
char hash[8]; // 8 character password
int intHash; // int representation of the hash
int* hash_pointer, * pass_pointer, * temp;
int n, result, *temp;
MD5_CTX mdContext;  // needed to compute MD5

typedef enum {false, true} bool;

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

// Increment the password and return the number of carry-overs
int increment_pass(char* pass)
{
	bool updated;
	int index = 0;
	do
	{
		updated = false;
		if (pass[index] == 'z')
		{
			pass[index] = '0';
			updated = true;
			index++;
		}
		else if (pass[index] == '9')
		{
			pass[index] = 'A';
		}
		else if (pass[index] == 'Z')
		{
			pass[index] = 'a';
		}
		else
		{
			pass[index] = pass[index] + 1;
		}

	} while (updated && index < 4);

	return index;
}

int getHash()
{
	MD5Init(&mdContext);  // compute MD5 of password
	MD5Update(&mdContext, pass_pointer, 4);
	MD5Final(&mdContext);
	temp = (int*)& mdContext.digest[12];

	return *temp;
}

main(int argc, char *argv[])
{
   hash_pointer = (int *) hash; // get an int pointer to the password store
   *hash_pointer = 0; // all nulls in password field
   if (argc!= 1) {printf("Usage: No Arguments\n", argv[0]); exit(0);};
   hash_pointer = (int *) hash; // get an int pointer to the password store
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
	do {
		
		result = getHash(pass); // result is 32 bits of MD5 -- there is a BUG here, oh well.
		
		if (result == intHash)
		{
			success = true;
			break;
		}
		carries = increment_pass(pass);

		if (carries >= 2)
		{
			// output to file
			//printf("Pass: %s Hash: %x\n", pass, result); // print a human readable version of hash (using hex conversion)
		}

	} while (carries < 4);

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

