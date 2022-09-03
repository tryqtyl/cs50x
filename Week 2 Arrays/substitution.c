#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//it takes 2h to solve this.

string encipher(string cipher, string plaintext);

int main(int argc, string argv[])
{
    //check argc
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //check length
    int length = strlen(argv[1]);
    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < length; i++)
    {
        //check non-alphabetic
        if (isalpha(argv[1][i]))
        {
            //ignore the repeat by comparing to other letter
            for (int ii = i + 1; ii < length; ii++)
            {
                if (tolower(argv[1][i]) == tolower(argv[1][ii]))
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    //get plain text
    string plaintext = get_string("plaintext:");
    //encipher
    printf("ciphertext:%s\n", (encipher(argv[1], plaintext)));
}

string encipher(string cipher, string plaintext)
{
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int position = toupper(plaintext[i]) - 'A';
            if (isupper(plaintext[i]))
            {
                plaintext[i] = toupper(cipher[position]);
            }
            else
            {
                plaintext[i] = tolower(cipher[position]);
            }

        }
    }
    return plaintext;
}