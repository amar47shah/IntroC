/* Amar Shah
 * 
 * Introduction to Programming Languages CECS130-50
 * Lab Assignment #1
 * 9 May 2012
 * 
 * A C program that generates an ASCII portrait of course instructor Dr. Roman Yampolskiy.
 * 
 * Detail: The ASCII portrait is based on a photograph which shows Dr. Roman Yampolskiy's face,
 * close-up, in three-quarter right-profile. Dr. Yampolskiy is smiling and resting his chin in
 * his right hand.  The original photograph is available in this course's listing on Blackboard,
 * under 'Faculty Information'.
 */

#include <stdio.h>   //  This program makes use of the standard input/output library header stdio.h.

main()
{
	/* The following 23 printf() statements instruct the computer to output the ASCII portrait.  
	 * Each printf() command corresponds to a line of ASCII art; thus, each printed string ends 
	 * with the newline escape sequence \n.  The escape sequences \t and \\ are also used.
	 *
	 */
	
	// The following 7 printf() statements instruct the computer to draw Dr. Yampolskiy's forehead and hair.
	printf("\t__________________________\n");
	printf("    ___/~~~~~~~~~~~~~~~~~~~~~~~~~~\\\n");
	printf("   /~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\n");
    printf("  /~~~~~~~~~~~~~~~~~~~~    ~~~    ~~\\\n");
	printf(" /~~~~~~~~\t  ~~~~\t\t    ~\\\n");
	printf("|~~~~~~\t\t    ~\n");
	printf("|~~~~~~\n");
	
	// The following 10 printf() statements instruct the computer to draw Dr. Yampolskiy's ear, eyes, nose, and mouth.
	printf("|~~~~~~~~\t\t\t~~~~~~~\n");
	printf("|~~~~~~~~~\t~~~~~~~\t       ~~ (*8*\n");
	printf("\\~~~~~~~      ~   *8*  > \\      ~\n");
	printf("  |    ~~~\t\t  \\    \\\n");
	printf("  \\     ~~\t\t   \\    \\\n");
	printf("   \\    ~~\t\t    \\    \\\n");
	printf("    \\__|\t\t      ____)   :\n");
	printf("      | \\\t    :\t\t       :\n");
	printf("      |  \\\t  :     ____________    __\n");
	printf("\t  \\_\t\t  --_____---   /  \\\n");
	
	// The final 6 printf() statements instruct the computer to draw Dr. Yampolskiy's chin and hand.
	printf("\t    \\_\t\t\t      /    ____---__ \n");
	printf("\t      \\___\t\t     /\t\t    |\n");
	printf("\t\t  \\__\t\t    /\n");
	printf("\t\t     \\_____________|\n");
	printf("\t\t\t\t\\  |\n");
	printf("\t\t\t\t \\ |\n");
	
	// After all 23 printf() statements have been executed, the program terminates.
}

