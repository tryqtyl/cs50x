#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//it takes 1.5 hour to complete this

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text:");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", (int)round(index));
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }
    return count;
}