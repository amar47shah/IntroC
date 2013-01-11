/*  Amar Shah
 * 
 *  Introduction to Programming Languages CECS130-50
 *  Lab Assignment #4
 *  3 June 2012
 *
 *  A C program that simulates a calculator.  The user chooses an operation from a menu 
 *  and then enters numbers as operands.  The program uses a separate function for each
 *  of the calculator's operations as well as additional functions for displaying the 
 *  menu and obtaining input.  Calculation takes place within functions instead of in 
 *  the main body of the program.  Existing code is reused whenever possible.
 */

/*  This program uses several headers from the C library.  ctype.h contains the function
 *  isdigit, which returns a nonzero value if and only if its argument is a digit ('0'-
 *  '9').  stdio.h contains printf and scanf.  stdlib.h contains the functions atof and 
 *  atoi, which convert character strings into numerical values.  string.h contains 
 *  strlen, which returns the length of a character string minus its terminal null character.
 */
#include <ctype.h>
#include <stdio.h>   
#include <stdlib.h>
#include <string.h>


/*  Here are the prototypes of functions included in this program.                           */
void printMenu ();                        /*  Prints the menu.                               */
void getChoice (char *);                  /*  Obtains user's menu choice.                    */
void getFloat (int, float *);             /*  Obtains a float value from the user.           */
void getInteger (int, int *);             /*  Obtains an integer value from the user.        */
int iHowManySigDigs (float);              /*  Determines the number of decimal places        *
                                           *      necessary to display a float.              */
float fAddTwoFloats (float, float);       /*  Returns the sum of two floats.                 */
float fSubtractTwoFloats (float, float);  /*  Returns the difference of two ordered floats.  */
float fMultiplyTwoFloats (float, float);  /*  Returns the product of two floats.             */
float fDivideTwoFloats (float, float);    /*  Returns the quotient of two ordered floats.    */
int iTakeMod (int, int);                  /*  Takes the remainder under integer division.    */
int iSmallestNonTrivialFactor (int);      /*  Returns an integer's smallest factor which     *
                                           *      is > 1.  (For use in determining whether   *
                                           *      the integer is prime.)                     */
int iFactorial (int);                     /*  Returns the factorial of an integer.           */
float fTakePower (float, int);            /*  Returns the value of a float taken to an       *
                                           *      integer exponent.                          */
int iFibonacci (int);                     /*  Given the integer value n, returns the nth     *
                                           *      number in the Fibonacci sequence.          */

main()
{
    /*  Program begins.  
     *
     *  The calculator simulation restarts after every operation until the user chooses 
     *  'Exit', represented by the condition (cOperationChoice == '0').  The simulation
     *  will always run at least once because it is governed by a do-while loop.
     */
    char cOperationChoice;    
	do {
        /*  Numerical variables fOperand1, fOperand2, iOperand1, and iOperand2 will be 
         *  used to store user-entered float and integer values.  The float fResult and
         *  integer iResult are used to store the results of calculations.  The choice
         *  of a float variable or its integer counterpart depends on the chosen calculator
         *  function.  For example, if the user chooses "Modulus", only the three integer 
         *  variables (iOperand1, iOperand2, and iResult) will be used.  These six variables 
         *  are defined here so that they are local to the do-while loop that iterates once 
         *  per user operation.
         */
        float fOperand1 = 0.0, fOperand2 = 0.0, fResult = 0.0;
        int iOperand1 = 0, iOperand2 = 0, iResult = 0;
        	
        //  The calculator menu is printed and the user's choice is obtained.
        printMenu ();
        getChoice (&cOperationChoice);  //  cOperationChoice is passed 'by reference'.
        
        //  This switch statement directs program flow according to the user's menu choice.  
        switch (cOperationChoice) {
            case '1':                                   //  Addition
                //  Two float values are obtained from the user as fOperand1 and fOperand2.
                getFloat (1, &fOperand1); getFloat (2, &fOperand2);
                //  The sum is obtained using the function fAddTwoFloats and stored as fResult.
                fResult = fAddTwoFloats(fOperand1, fOperand2);
                //  The operands and their sum are printed according to their significant digits.
                printf ("%.*f + %.*f = %.*f\n", iHowManySigDigs(fOperand1), fOperand1, 
                                                iHowManySigDigs(fOperand2), fOperand2, 
                                                iHowManySigDigs(fResult)  , fResult);
                break;
            case '2':                                   //  Subtraction
                getFloat (1, &fOperand1); getFloat (2, &fOperand2);
                fResult = fSubtractTwoFloats(fOperand1, fOperand2);
                printf ("%.*f - %.*f = %.*f\n", iHowManySigDigs(fOperand1), fOperand1, 
                                                iHowManySigDigs(fOperand2), fOperand2, 
                                                iHowManySigDigs(fResult)  , fResult);
                break;
            case '3':                                   //  Multiplication
                getFloat (1, &fOperand1); getFloat (2, &fOperand2);
                fResult = fMultiplyTwoFloats(fOperand1, fOperand2);
                printf ("%.*f x %.*f = %.*f\n", iHowManySigDigs(fOperand1), fOperand1, 
                                                iHowManySigDigs(fOperand2), fOperand2, 
                                                iHowManySigDigs(fResult)  , fResult);
                break;
            case '4':                                   //  Division
                getFloat (1, &fOperand1); getFloat (2, &fOperand2);
                //  The following conditional statement ensures that division by zero is not attempted.
                if (fOperand2 != 0) {
                    fResult = fDivideTwoFloats(fOperand1, fOperand2);
                    printf ("%.*f / %.*f = %.*f\n", iHowManySigDigs(fOperand1), fOperand1, 
                                                    iHowManySigDigs(fOperand2), fOperand2, 
                                                    iHowManySigDigs(fResult)  , fResult);
                }
                else
                    printf ("Division by zero is not allowed.\n");
                break;
            case '5':                                   //  Modulus
                //  Two integer values are obtained from the user and stored as iOperand1 and iOperand2.
                getInteger (1, &iOperand1); getInteger (2, &iOperand2);
                //  As in the previous case, a conditional statement ensures that modulus by zero is not attempted.
                if (iOperand2 != 0) {
                    iResult = iTakeMod(iOperand1, iOperand2);
                    printf ("%d mod %d = %d\n", iOperand1, iOperand2, iResult);
                }
                else
                    printf ("Modulus by zero is not allowed.\n");
                break;
            case '6':                                   //  Test if prime
                //  A single integer value is obtained from the user.
                getInteger (0, &iOperand1);
                //  The entered value will be tested only if it is greater than 1.
                if (iOperand1 > 1) {
                    /*  The function iSmallestNonTrivalFactor returns 0 if its argument 
                     *  is a prime number.  If its argument is composite, it returns the 
                     *  smallest non-trivial factor.  The variable iResult takes on the
                     *  value of iSmallestNonTrivialFactor(iOperand1) so that the 
                     *  function will not have to be called repeatedly during condition 
                     *  testing and output.
                     */
                    iResult = iSmallestNonTrivialFactor(iOperand1);
                    /*  The value of iResult will be 0 if (and only if) iOperand1 is a 
                     *  prime number.  In that case, the condition (!iResult) will be true 
                     *  (non-zero).  Otherwise, if iOperand1 is not prime, then iResult 
                     *  will be given the value of iOperand1's smallest non-trivial factor.
                     *  The condition (!iResult) will consequently be false, and the value 
                     *  of iResult will be printed to justify the claim that iOperand1 is 
                     *  indeed not prime.
                     */
                if (!iResult)
                    printf ("%d is prime.\n", iOperand1);
                else
                    printf ("Not prime: %d x %d = %d\n", iResult, iOperand1 / iResult, iOperand1);
                }  
                /*  If, on the other hand, the entered integer is not greater than 1, an 
                 *  error is returned and the program continues.
                 */
                else
                    printf ("Only integers greater than 1 can be prime.\n");
                break;
            case '7':                                   //  Factorial 
                getInteger (0, &iOperand1);
                /*  Factorials grow very quickly, so that they are soon out of the range
                 *  of type int.  If the user attempts to take the factorial of a number
                 *  larger than 16, they will be asked to try a smaller number.  Additionally,
                 *  the user is not allowed to take the factorial of a negative number.
                 */
                if ((iOperand1 >= 0) && (iOperand1 <= 16)) {
                    iResult = iFactorial(iOperand1);
                    printf ("%d! = %d\n", iOperand1, iResult);
                }
                else if (iOperand1 > 16)
                    printf ("Try a smaller number.\n");
                else
                    printf ("Factorials are defined for non-negative integers.\n");
                break;
            case '8':                                   //  Power
                /*  The power calculation requires a float value for the base and an 
                 *  integer value for the exponent.
                 */
                getFloat (1, &fOperand1); getInteger (2, &iOperand2);
                /*  An error message is returned if the user attempts to take the base
                 *  value 0 to a exponent less than or equal to 0.  Otherwise the power
                 *  is calculated using the fTakePower function.
                 */
                if ((fOperand1 != 0) || (iOperand2 > 0)) {
                    fResult = fTakePower(fOperand1, iOperand2);
                    printf ("%.*f ^ %d = %.*f\n", iHowManySigDigs(fOperand1), fOperand1, 
                                                                              iOperand2, 
                                                  iHowManySigDigs(fResult)  , fResult);
                }
                else                     
                    printf ("%.0f ^ %d is not defined.\n", fOperand1, iOperand2);
                break;
            case '9':                                   //  Fibonacci            
                //  A sequence index is obtained from the user and stored as iOperand1.
                getInteger (0, &iOperand1);
                /*  The corresponding Fibonacci number will be delivered if the specified
                 *  sequence index is greater than or equal to 1.
                 */
                if (iOperand1 >= 1) {
                    iResult = iFibonacci(iOperand1);
                    printf ("The %d", iOperand1);
                    /*  The following switch statement accomodates the English language's 
                     *  peculiar cardinal numbering protocol: '1st', '2nd', '3rd' and 
                     *  thereafter '4th', '5th', '6th', '7th', etc.
                     */
                    switch (iOperand1) {
                        case 1:
                            printf ("st"); 
                            break;
                        case 2:
                            printf ("nd");
                            break;
                        case 3:
                            printf ("rd");
                            break;
                        default:
                            printf ("th");
                            break;
                    }
                    printf (" Fibonacci number is %d.\n", iResult);
                }
                //  If the entered sequence index is less than 1, an error message is printed.
                else
                    printf ("The Fibonacci sequence begins with n = 1.\n");
                break;
            case '0':                                   //  Exit
                printf ("Good Bye!\n");
                break;
        }  //  End of switch protocol.
    //  The loop will not terminate until the user-entered cOperationChoice has the value '0'.
    } while (cOperationChoice != '0');  
}  //  End of main() function.

//  The printMenu () function simply displays the calculator menu.
void printMenu () {
    printf("\nCalculator Menu:");
    printf("\n(1)\tAddition");
    printf("\n(2)\tSubtraction");
    printf("\n(3)\tMultiplication"); 
    printf("\n(4)\tDivision");
    printf("\n(5)\tModulus (integers only)");
    printf("\n(6)\tTest if prime (integers only)");
    printf("\n(7)\tFactorial (integers only)");
    printf("\n(8)\tPower");
    printf("\n(9)\tFibonacci");
    printf("\n(0)\tExit\n\n");
}

//  The function getChoice (char *) obtains a single digit, 0-9, from the user.
void getChoice (char *cChoice) {
    /*  The character array cInputString will store the user's input.  The const 
     *  int parameter iMaxLength denotes the number of characters in the user's 
     *  longest allowed input string.
     */
    const int iMaxLength = 50;
    char cInputString[iMaxLength + 1];

    /*  The array is initialized.  Every element is initialized to the null character.
     *  The value *cChoice is also set to the null character.
     */
    int i;
    for (i = 0; i < iMaxLength; i++)
        cInputString[i] = '\0';
    *cChoice = '\0';

    //  This loop executes while *cChoice is not a digit, 0-9.
    while (!isdigit(*cChoice)) {
        //  The user is prompted to enter cInputString.
        printf ("\rPlease choose an operation (0-9): ");
        scanf ("%s", cInputString);
        /*  If cInputString represents a single character, the value of that character
         *  is bestowed on *cChoice.  Otherwise, *cChoice is not changed.
         */
        if (strlen(cInputString) == 1)
            *cChoice = cInputString[0];
        //  If *cChoice does not yet represent a digit, then the loop will execute again.
    }
}

//  getFloat obtains a user-entered value for a float variable.
void getFloat (int iNumbering, float *fNumber) {
    //  Declaration and initialization of input string.
    const int iMaxLength = 20;
    char cInputString[iMaxLength + 1];
    int i;
    for (i = 0; i < iMaxLength; i++)
    cInputString[i] = '\0';

    //  The user is prompted according to the parameter iNumbering.
    printf ("Enter the ");
    switch (iNumbering) {
        case 1: 
            printf ("first ");
            break;
        case 2:
            printf ("second ");
            break;
    }
    printf ("number: ");
    /*  The user enters a string of data.  That string is converted to a float value using
     *  the function atof.  The float value is assigned to *fNumber.
     */
    scanf ("%s", cInputString);
    *fNumber = atof(cInputString);
}

//  getInteger obtains a user-entered value for an integer variable.
void getInteger (int iNumbering, int *iNumber) {
    //  Declaration and initialization of input string.
    const int iMaxLength = 20;
    char cInputString[iMaxLength + 1];
    int i;
    for (i = 0; i < iMaxLength; i++)
        cInputString[i] = '\0';

    //  The user is prompted according to the parameter iNumbering.
    printf ("Enter the ");
    switch (iNumbering) {
        case 1: 
            printf ("first ");
            break;
        case 2:
            printf ("second ");
            break;
    }
    printf ("number: ");
    /*  The user enters a string of data.  That string is converted to a float value using
     *  the function atof.  The float value is assigned to *fNumber.
     */
    scanf ("%s", cInputString);
    *iNumber = atoi(cInputString);
}

/*  The function iHowManySigDigs returns a non-negative integer value that represents the 
 *  number of decimal places to display a float.  That is, iHowManySigDigs(4.23) returns 
 *  the value 2, iHowManySigDigs(5.7) returns the value 1, and iHowManySigDigs(9) returns 
 *  the value 0. The maximum value returned by iHowManySigDigs is 4, even for arguments 
 *  with more than four decimal places.  
 */
int iHowManySigDigs (float fNumber) {
    /*  The integer variable iEquiv is assigned the integer value (the floor) of the float
     *  fNumber.  In the following loop, fNumber is repeatedly increased by a factor of 10
     *  and iEquiv is again assigned the floor of fNumber.  Meanwhile, the counter i is
     *  incremented.  When the difference of fNumber and iEquiv is zero, the loop will
     *  cease to execute.  The loop is further controlled by the value of i, which is not
     *  allowed to exceed 4.  
     *  
     *  Known problems: Sometimes the difference of fNumber and iEquiv "should" be zero but 
     *  is not precisely zero, so that the loop does not terminate until i receives the value 
     *  4.  In this case, an error occurs in which iHowManySigDigs returns a value of 4 for 
     *  a float with apparently fewer than 4 decimal places.  This may be because float type 
     *  variables store extra digits that are not part of their values.  A possible solution 
     *  might involve allowing a set tolerance level for the comparison of fNumber and iEquiv, 
     *  so that their difference only need be close to zero, not exact, to terminate the loop.
     */
    int iEquiv = (int) fNumber;
    int i = 0;
    while ((fNumber - iEquiv) && (i < 4)) {
        fNumber *= 10;
        iEquiv = (int) (fNumber);
        i++;
    }
    //  The value i now represents the number of decimal places associated with fNumber.
    return i;
}

//  fAddTwoFloats receives two float values and returns their sum.
float fAddTwoFloats (float fAddend1, float fAddend2) {
    return fAddend1 + fAddend2;
}

//  fSubtractTwoFloats receives two ordered float values and returns their difference.
float fSubtractTwoFloats (float fMinuend, float fSubtrahend) {
    //  The fAddTwoFloats function is used with a modification of parameters.
    return fAddTwoFloats(fMinuend, 0 - fSubtrahend);	
}

//  fMultiplTwoFloats receives two float values and returns their product.
float fMultiplyTwoFloats (float fFactor1, float fFactor2) {
    return fFactor1 * fFactor2;
}

//  fDivideTwoFloats receives two ordered float values and returns their product.
float fDivideTwoFloats (float fDividend, float fDivisor) {
    //  The fMultiplyTwoFloats function is used with a modification of parameters.
    return fMultiplyTwoFloats(fDividend, 1 / fDivisor);
}

//  iTakeMod receives two ordered integer values and returns their remainder under integer division.
int iTakeMod (int iDividend, int iDivisor) {
    return iDividend % iDivisor;
}

//  The iFactorial function returns n! for a given natural number n.
int iFactorial (int iNatural) {
    int iProduct = 1; 
    int i;
    //  The loop simulates the commonsense method of computing factorials (e.g.,  5! = 5 x 4 x 3 x 2 x 1).
    for (i = iNatural; i > 0; i--)
        iProduct *= i;
    return iProduct;
}

/*  iSmallestNonTrivialFactor returns the smallest non-trivial factor for an integer > 1.  
 *  (A non-trivial factor is a factor other than 1 and the integer itself.) If the integer 
 *  is prime, then it has no non-trivial factors, and the function returns the value 0 
 *  instead.  Therefore, a zero value of the function indicates a prime argument and a 
 *  non-zero value indicates a composite argument. 
 */
int iSmallestNonTrivialFactor (int iTestNumber) {
    //  The number 2, which is prime, must be accommodated separately as an "edge case".
    if (iTestNumber == 2)
        return 0;
    else {
        /*  The following loop simulates the search for a non-trivial factor of iTestNumber,   
    	 *  by testing the remainder of iTestNumber / iPossibleFactor under integer division.  
         *  Possible factors are considered from 2 all the way up to just over half of iTestNumber.
         *  The loop terminates either because a factor was found or because all possible
         *  factors have been considered.  
    	 */
        int iPossibleFactor = 1;
        do
            iPossibleFactor++;	
        while ((iPossibleFactor < iTestNumber / 2 + 1) && (iTakeMod(iTestNumber, iPossibleFactor) != 0));
        //  If a factor was found, it is returned as the value of iSmallestNonTrivialFactor.
        if ((iTakeMod(iTestNumber, iPossibleFactor) == 0))
            return iPossibleFactor;
        //  If no factor was found, the value 0 is returned.
        else
            return 0;
    }
}

//  fTakePower receives a float x and an integer n and returns the value of x ^ n.
float fTakePower (float fBase, int iExponent) {
    float fProduct = 1.0;
    /*  iPower is given the absolute value of iExponent.  The value of fBase ^ iPower
     *  is computed using a for loop which keeps a running product of fBase multiplied
     *  by itself, iPower times.
     */
    int iPower = abs(iExponent);
    int i;
    for (i = 1; i <= iPower; i++)
        fProduct = fMultiplyTwoFloats(fProduct, fBase);
    //  For a negative exponent, the reciprocal of the running product is returned.
    if (iExponent < 0)
        return 1 / fProduct;
    //  For a non-negative exponent, the running product itself is returned.
    else
        return fProduct;
}

/*  iFibonacci computes the Fibonacci sequence up to a particular index, and then returns
 *  the Fibonacci number associated with that sequence index.  The previous Fibonacci numbers
 *  are stored in an array while the function runs.
 */
int iFibonacci (int iIndex) {
    /*  The array iFibonacciList is declared.  The value of iIndex is decremented by 1
     *  to accommodate the numbering of array indices, which begin with 0, so that the 
     *  index n -1 holds the nth value. 
     */
    int iFibonacciList[--iIndex];
    int i;
    //  All array elements are initialized to 1.
    for (i = 0; i <= iIndex; i++)
        iFibonacciList[i] = 1;
    /*  The Fibonacci sequence is computed, beginning with the third element, according to
     *  the rule F(n) = F(n - 1) + F(n - 2).
     */
    for (i = 2; i <= iIndex; i++) 
        iFibonacciList[i] = iFibonacciList[i - 1] + iFibonacciList[i - 2];
    //  The final value in the iFibonacciList array is returned.
    return iFibonacciList[iIndex];
}
