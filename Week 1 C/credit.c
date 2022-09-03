#include <cs50.h>
#include <stdio.h>

bool CHECKSUM(long digits, long card_number)
{
long single_digit;
long checksum = 0;
while (card_number != 0)
{
    single_digit = card_number % 10;
	card_number = card_number / 10;
	// sum on odd digits.
	checksum += single_digit;
    single_digit = card_number % 10;
	card_number = card_number / 10;
	// time 2, then % and / , then add them all
	checksum += (single_digit * 2 / 10) + (single_digit * 2 % 10);
}
if (checksum % 10 == 0)
{
return true;
}
else
return false;
}

int main(void)
{
long number = get_long("Enter the number:");
// the length of the number
// f2d is the first 2-digit number
long f2d = number;
int length = 2;
while ( f2d > 100 )
{
	f2d = f2d / 10;
	length++;
}

if ( (length == 15) && (f2d == 34 || f2d == 37) && (CHECKSUM(length,number)) )
{
printf ("AMEX\n");
}
else if ( (length == 16) && (f2d > 50) && (f2d < 56) && (CHECKSUM(length,number)) )
{
printf("MASTERCARD\n");
}
else if ( ((length == 16) || (length == 13)) && (f2d / 10 == 4) && (CHECKSUM(length,number)))
{
printf("VISA\n");
}
else
{
printf("INVALID\n");
}
}