#include "md5.h" 

#define TABLE_HEIGHT 500
#define TABLE_WIDTH 20



typedef enum { false, true } bool;


void check_hash(char* hash)
{
	int i = 0;
	for (i = 0; i < 8; i++) {
		if (!(((hash[i] >= 'a') && (hash[i] <= 'f'))
			|| ((hash[i] >= '0') && (hash[i] <= '9')))) {
			printf("Hash not as per specifications\n");
			exit(0);
		};
	};
};

unsigned int getHash(char* pass)
{
	MD5_CTX mdContext;  // needed to compute MD5
	unsigned int *temp;

	MD5Init(&mdContext);  // compute MD5 of password
	MD5Update(&mdContext, pass, 4);
	MD5Final(&mdContext);
	temp = (int*)& mdContext.digest[12];

	return *temp;
}

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
	char selected;
	//printf("Selected integer: %i ", num);
	if (0 <= num && num <= 9)
	{
		selected = '0' + num;
	}
	else if (10 <= num && num <= 35)
	{
		selected = 'A' + num - 10;
	}
	else if (36 <= num && num <= 61)
	{
		selected = 'a' + num - 36;
	}
	else // Invalid number
	{
		selected = '\0';
	}
	//printf("Selected character: %c\n", selected);
	return selected;
}

void inverseHash(unsigned int hash, char* reverse)
{
	//printf("Hash: %d ", hash);
	//hash %= 14776336;

	for (int i = 0; i < 4; ++i)
	{
		reverse[i] = associatedChar(hash % 62);
		hash /= 62;
	}

	//printf("Pass: %s\n", reverse);
}