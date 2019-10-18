const int TABLE_HEIGHT = 5000;
const int TABLE_WIDTH = 62 * 62;

typedef enum { false, true } bool;

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

inverseHash(int hash, char* reverse)
{
	hash %= 14776336;

	for (int i = 0; i < 4; ++i)
	{
		reverse[i] = associatedChar(hash % 62);
		hash /= 62;
	}
}