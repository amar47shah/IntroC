//  Program to try input validation in functions.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void InputDigit (char *);

main ()
{
	char cDigit = '\0';
    InputDigit (&cDigit);
    printf ("You chose %c\n", cDigit);
}

void InputDigit (char *cDigitChoice)
{
	*cDigitChoice = '\0';
	const int iStringLength = 10;
	char cInputString[iStringLength + 1];
	int i;
	for (i = 0; i < iStringLength; i++)
		cInputString[i] = '0';
	while (!isdigit(*cDigitChoice)) {
	    printf ("\rInput the digit. ");
	    scanf ("%s", cInputString);
        if (strlen(cInputString) == 1)
			*cDigitChoice = cInputString[0];
//		printf ("%s\n", cInputString);
//		if (*cDigitChoice != '\0') 
//			printf ("%c\n", *cDigitChoice);
//		else
//			printf ("You did not enter a character.\n");
	}
	//*cDigitChoice = '\0';
	//while (!isdigit(*cDigitChoice)) {
	//	printf ("\rInput the digit. ");
	//    scanf ("%c", cDigitChoice);
	//}
}