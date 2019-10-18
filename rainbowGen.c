

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

// returns the char associated with the number, i.e. the index used to determine its use
char associatedChar(int num)
{
	if (0 <= num && num <= 9)
	{
		return '0' + num;
	}
	else if (10 <= num && num <= 35)
	{
		return 'A' + num;
	}
	else if (36 <= num && num <= 61)
	{
		return 'a' + num;
	}
	else // Invalid number
	{
		return '\0';
	}


}

int getHash()
{
	MD5Init(&mdContext);  // compute MD5 of password
	MD5Update(&mdContext, pass_pointer, 4);
	MD5Final(&mdContext);
	temp = (int*)& mdContext.digest[12];

	return *temp;
}

inverseHash(int hash, char* reverse)
{
	hash %= 14776336;

	for (int i = 0; i < 4; ++i)
	{
		reverse[i] = associatedChar(hash % 62);
		hash /= 62;
	}
}

// returns the hash that results from the end of a rainbow table
int getFinalHash(char* pass)
{
	int hash;
	char tempPass[4];
	for (int i = 0; i < 4; ++i)
		tempPass[i] = pass[i];

	for (int i = 0; i < 62 * 62; ++i)
	{
		hash = getHash(tempPass);
		inverseHash(hash, tempPass);
	}

	return hash;
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

	for (int i = 0; i < 5000; ++i)
	{
		result = getFinalHash(pass); // result is 32 bits of MD5 -- there is a BUG here, oh well.
		store(pass, hash);


		carries = increment_pass(pass);

	}

// Note if you store hashes, do not use human readable HEX, 
// but write the integer to file, raw bits.
 
};

