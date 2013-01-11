/* Amar Shah
 * 
 * Introduction to Programming Languages CECS130-50
 * Lab Assignment #3
 * 25 May 2012
 *
 * A C program that simulates a calculator.  The user chooses an operation from a menu and then enters numbers as operands.
 * Additionally, the user may test an integer to see if it is prime.
 */

#include <stdio.h>  //  This program uses the standard input/output header. 
#include <ctype.h>

void getTwoFloats (float *, float *);
void getTwoIntegers (int *, int *);
float fAddTwoFloats (float, float);
float fMultiplyTwoFloats (float, float);
int iTakeMod (int, int);
int iIsPrime (int);

main()  
{
    /*  Program begins.  
     *
     *  Declaration of variables.  cOperationChoice represents the user's choice of calculator function, according to the menu.
     *  Depending on which operation is chosen, the user enters either two operands as floats, two operands as integers, or a
     *  single integer to be determined as 'prime' or 'not prime'.  The integer variable iPossibleFactor is used to determine
     *  whether the tested integer is prime.
     */
    char cOperationChoice;
	
    /*  The calculator simulation restarts after every operation until the user chooses 'Exit'.  Therefore, this loop continues 
     *  to execute until (cOperationChoice == '7') is true.
     */
    do {
        /*  Each time the calculator simulation restarts, some of the variables need to be initialized (in particular, 
         *  iPossibleFactor).  For clarity, the program is written so that all variables are initialized at the start of each 
         *  calculator simulation.  To avoid redundancy, the variables were not initialized in their declarations.
         */
		cOperationChoice = '\0';
        float fOperand1 = 0.0; float fOperand2 = 0.0;
        int iOperand1 = 0; int iOperand2 = 0;
        int iTestIfPrime = 0;
	
        //  The calculator menu is printed.
        printf("\nCalculator Menu:");
        printf("\n(1)\tAddition");
        printf("\n(2)\tSubtraction");
        printf("\n(3)\tMultiplication");
        printf("\n(4)\tDivision");
        printf("\n(5)\tModulus (integers only)");
        printf("\n(6)\tTest if prime (integers only)");
        printf("\n(7)\tExit\n\n");

        /*  The user is prompted to enter a choice from the menu.  This loop ensures that only values of '1' through '7' will be
         *  accepted.  If a user enters an unacceptable value, she will be prompted again.  The loop runs at least once because
         *  the char variable cOperationChoice has been initialized to '\0', whose ASCII value is outside the acceptable range.
         */
        while (!isdigit(cOperationChoice)) { 
            printf("\rPlease choose an operation: ");
            scanf(" %c", &cOperationChoice);
        }  //  End of while loop. 
        /*  The following switch statement directs program flow according to the user's choice from the menu.  Cases '1' through 
         *  '5' ("Addition" through "Modulus") use a similar procedure, except that Case '5' "Modulus" requires integer operands 
         *  instead of floats.
         */
        switch (cOperationChoice) {
            case '1':                                   //  Addition
                //  The two operands are entered as floats to accommodate a wider range of calculations.  
                getTwoFloats(&fOperand1, &fOperand2);               
                //  The operands and their result are displayed to four decimal places.
                printf ("%.4f + %.4f = %.4f\n", fOperand1, fOperand2, fAddTwoFloats(fOperand1, fOperand2));
                break;
            case '2':                                   //  Subtraction
                getTwoFloats(&fOperand1, &fOperand2);
                printf ("%.4f - %.4f = %.4f\n", fOperand1, fOperand2, fAddTwoFloats(fOperand1, 0 - fOperand2));
                break;
            case '3':                                   //  Multiplication
                getTwoFloats(&fOperand1, &fOperand2); 
				printf ("%.4f x %.4f = %.4f\n", fOperand1, fOperand2, fMultiplyTwoFloats(fOperand1, fOperand2));
                break;
            case '4':                                   //  Division
                getTwoFloats(&fOperand1, &fOperand2); 
                //  The following conditional statement ensures that division by zero is not attempted.
                if (fOperand2 != 0)
                    printf ("%.4f / %.4f = %.4f\n", fOperand1, fOperand2, fMultiplyTwoFloats(fOperand1, 1 / fOperand2));
                else
                    printf ("Division by zero is not allowed.\n");
                break;
            case '5':                                   //  Modulus
                getTwoIntegers(&iOperand1, &iOperand2); 
                //  As in the previous case, a conditional statement ensures that modulus by zero is not attempted.
                if (iOperand2 != 0)
                    printf ("%d mod %d = %d\n", iOperand1, iOperand2, iTakeMod(iOperand1, iOperand2));
                else
                    printf ("Modulus by zero is not allowed.\n");
                break;
            case '6':                                   //  Test if prime
                printf ("Enter the integer to be tested. ");
                scanf ("%d", &iTestIfPrime);
                //  The entered value will be tested only if it is greater than 1.
                if (iTestIfPrime > 1) {
                    /*  The following loop tests for primeness by calculating the successive values: iTestIfPrime mod 2, 
                     *  iTestIfPrime mod 3, iTestIfPrime mod 4, etc.  The value of iPossibleFactor is used as a counter
                     *  from 2 up to iTestIfPrime / 2 + 1. (That is, just over half of iTestIfPrime; it is not necessary 
                     *  to count any further.)  The loop terminates whenever one of the following conditions is satisfied: 
                     *  1) iTestIfPrime mod iPossibleFactor == 0 or 2) iPossibleFactor is too large.  The loop will always 
                     *  eventually terminate if iTestIfPrime has an integer value that is greater than one.
                     */
                    int iPossibleFactor = 1;
					do
                        iPossibleFactor++;	
                    while ((iPossibleFactor < iTestIfPrime / 2 + 1) && (iTestIfPrime % iPossibleFactor != 0));
                    /*  Once the loop terminates, the last value of iPossibleFactor is retained.  If iPossibleFactor's current value 
                     *  is indeed a non-trivial factor of iTestIfPrime (that is, iTestIfPrime mod iPossibleFactor == 0), then the 
                     *  primeness test has failed.  If the value of iTestIfPrime was entered as 2, it must be treated as a special 
                     *  case, so that a "Not prime" result will NOT be generated.
                     */
                    if ((iTestIfPrime % iPossibleFactor == 0) && (iTestIfPrime != 2))
                        printf ("Not prime: %d x %d = %d\n", iPossibleFactor, iTestIfPrime / iPossibleFactor, iTestIfPrime);
                    //  If an integer greater than 1 is not "Not prime", then it is prime.
                    else
                        printf ("%d is prime.\n", iTestIfPrime);
                }  //  End of conditional statement block.
                //  If, on the other hand, the entered integer is not greater than 1, an error is returned and the program continues.
                else
                    printf ("Only integers greater than 1 can be prime.\n");
                break;
			case '7':
                printf ("Good Bye!\n");
                break;
        }  //  End of switch protocol.
    } while (cOperationChoice != '0');  //  The loop will not terminate until the user-entered cOperationChoice has the value '7'.
}  //  End of main() function.  Program has terminated.  

void getTwoFloats (float *fTheFirst, float *fTheSecond) {
    printf ("Enter the first number: ");
    scanf ("%f", fTheFirst);
    printf ("Enter the second number: ");
    scanf ("%f", fTheSecond);
}
void getTwoIntegers (int *iTheFirst, int *iTheSecond) {
    printf ("Enter the first number: ");
    scanf ("%d", iTheFirst);
    printf ("Enter the second number: ");
    scanf ("%d", iTheSecond);
}
float fAddTwoFloats (float fAddend1, float fAddend2) {
    return fAddend1 + fAddend2;
}
float fMultiplyTwoFloats (float fFactor1, float fFactor2) {
    return fFactor1 * fFactor2;
}
int iTakeMod (int iDividend, int iDivisor) {
    return iDividend % iDivisor;
}
int iIsPrime (int iTestNumber) {
	return 1;
}