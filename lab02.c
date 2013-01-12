/* Amar Shah
 * 
 * Introduction to Programming Languages CECS130-50
 * Lab Assignment #2
 * 16 May 2012
 * 
 * A C program that converts a user-determined amount of an unspecified currency 
 * into amounts of various global currencies, and displays the results in a table.
 */
 
// This program makes use of the standard input/output library header stdio.h.
#include <stdio.h>  

main()
{
    /* The following constants, of type 'float', express currency conversion factors using the
     * American Dollar as a base currency. That is, multiplying a number of British Pounds by
     * the constant fDollars2Pounds will give the number of American Dollars of equivalent worth.
     * Multiplying an amount of Euro by the constant fDollars2Euro will give the number of American
	 * Dollars of equivalent worth, and so on.  Dividing a number of American Dollars by any of
	 * these constants will give an equivalent amount of the appropriate foreign currency.
	 * 
	 * Instead of using a constant fDollars2Dollars, this conversion factor is understood to have
	 * an unchanging value of exactly 1.0.
     */
    const float fDollars2Pounds = 1.5924;
    const float fDollars2Euro = 1.2735;
    const float fDollars2AusDollars = 0.9934;
    const float fDollars2SwissFrancs = 1.060;
    const float fDollars2CanDollars = 0.9885;

    // The variable fAmount2Exchange, of type 'float', is defined and a new value is entered by the user.
    float fAmount2Exchange = 0.0;
    printf ("Please enter the amount of foreign currency to exchange.  ");
    scanf  ("%f", &fAmount2Exchange);
    
	// The following statements calculate and print the table.
	  
	/* The first statement prints the column headers, which are 3-letter official abbreviations for
	 * the American Dollar, British Pound, Euro, Australian Dollar, Swiss Franc, and Candadian Dollar,
	 * in that order.
	 */
    printf ("\n\t   USD\t   GBP\t   EUR\t   AUD\t   CHF\t   CAD");
    
	/* In the first row of table data, various currencies are compared to the American Dollar.  To
	 * calculate equivalent amounts of American Dollars for each currency, the value of fAmount2Exchange
	 * is simply multiplied by the conversion factors stored as constants above.
	 */  
	printf ("\nUSD\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f", fAmount2Exchange, 
                                                         fAmount2Exchange * fDollars2Pounds,
                                                         fAmount2Exchange * fDollars2Euro,
                                                         fAmount2Exchange * fDollars2AusDollars,
                                                         fAmount2Exchange * fDollars2SwissFrancs,
                                                         fAmount2Exchange * fDollars2CanDollars);
    
	/* The second row of the table displays equivalent amounts of British Pounds for the entered amount
	 * of other currencies.  The user-entered value fAmount2Exchange is therefore multiplied by the appropriate
	 * conversion constant in order to be expressed as a number of American Dollars, and then divided by
	 * fDollars2Pounds to be expressed as a number of equivalent British Pounds.  Where the conversion is trivial
	 * ("British Pounds into British Pounds"), the value of fAmount2Exchange is left unchanged.
	 */
	printf ("\nGBP\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f", fAmount2Exchange / fDollars2Pounds, 
                                                         fAmount2Exchange,
                                                         fAmount2Exchange / fDollars2Pounds * fDollars2Euro,
                                                         fAmount2Exchange / fDollars2Pounds * fDollars2AusDollars,
                                                         fAmount2Exchange / fDollars2Pounds * fDollars2SwissFrancs,
                                                         fAmount2Exchange / fDollars2Pounds * fDollars2CanDollars);
    /* The remaining four rows of data are calculated and displayed in similar fashion.  Note how the 
	 * "%.4f" conversion specifier is used throughout the table to display expressions of type 'float' 
	 * with four decimal places.
	 */
	printf ("\nEUR\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f", fAmount2Exchange / fDollars2Euro, 
                                                         fAmount2Exchange / fDollars2Euro * fDollars2Pounds,
                                                         fAmount2Exchange,
                                                         fAmount2Exchange / fDollars2Euro * fDollars2AusDollars,
                                                         fAmount2Exchange / fDollars2Euro * fDollars2SwissFrancs,
                                                         fAmount2Exchange / fDollars2Euro * fDollars2CanDollars);
    printf ("\nAUD\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f", fAmount2Exchange / fDollars2AusDollars, 
                                                         fAmount2Exchange / fDollars2AusDollars * fDollars2Pounds,
                                                         fAmount2Exchange / fDollars2AusDollars * fDollars2Euro,
                                                         fAmount2Exchange,
                                                         fAmount2Exchange / fDollars2AusDollars * fDollars2SwissFrancs,
                                                         fAmount2Exchange / fDollars2AusDollars * fDollars2CanDollars);
    printf ("\nCHF\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f", fAmount2Exchange / fDollars2SwissFrancs, 
                                                         fAmount2Exchange / fDollars2SwissFrancs * fDollars2Pounds,
                                                         fAmount2Exchange / fDollars2SwissFrancs * fDollars2Euro,
                                                         fAmount2Exchange / fDollars2SwissFrancs * fDollars2AusDollars,
                                                         fAmount2Exchange,
                                                         fAmount2Exchange / fDollars2SwissFrancs * fDollars2CanDollars);
    printf ("\nCAD\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f", fAmount2Exchange / fDollars2CanDollars, 
                                                         fAmount2Exchange / fDollars2CanDollars * fDollars2Pounds,
                                                         fAmount2Exchange / fDollars2CanDollars * fDollars2Euro,
                                                         fAmount2Exchange / fDollars2CanDollars * fDollars2AusDollars,
                                                         fAmount2Exchange / fDollars2CanDollars * fDollars2SwissFrancs,
                                                         fAmount2Exchange);
   
   // After printing the table, the program terminates.
   printf ("\n\n");
}                                                           
