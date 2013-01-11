/* Amar Shah
 * 
 * Introduction to Programming Languages, CECS 130-50
 * Lab Assignment #6
 * 16 June 2012
 * 
 * An application for managing a list of phone numbers, written in C.
 *
 * The user can add entries to a phone book, display all the entries
 * and choose entries to be deleted.  There is no limit to the number
 * of entries that may be stored, beyond the system's own memory limit.
 *
 * Future utility improvements: 1) Writing all records to a file so
 * that they are stored after program termination. 2) An internal
 * sorting function to keep the records in alphabetical order.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* The structure ListEntry carries all the data of a phone book entry:
 * strings for first name, last name, and phone number. The structure
 * is defined as the blueprint for the type ListEntryType.
 */
typedef struct ListEntry {
    char cFirstName[21];
    char cLastName[21];
    char cPhoneNumber[16];
} ListEntryType;

/* Function prototypes: printMenu displays the main menu; getChoice
 * obtains the user's choice from the main menu; and the remaining
 * subroutines each direct a particular function of the application.
 */
void printMenu ();
void getChoice (char *);
void addEntry (ListEntryType *, int *, int *);
void deleteEntry (ListEntryType *, int *);
void showAllEntries (ListEntryType *, int *);

// Main function: Program execution begins.
main()
{
    /* Phonebook points to (the first element) of an array of structures
     * of ListEntryType.  Each element of the array contains all the 
     * information for one record: first name, last name, and phone 
     * number. Integer variables iLength and iCapacity each contain 
     * information about the array.  iCapacity indicates the number of
     * entries which can be stored according to current memory allocation;
     * when iCapacity = 5, then no more than 5 records can be stored.
     * iLength indicates the number of records that are currently stored.
     * (Therefore, the last element in the array is indexed by iLength - 1.)
     */
    ListEntryType *PhoneBook;
    int iLength = 0;
    int iCapacity = 0;
    
    /* PhoneBook is allocated enough memory to match its current listed
     * capacity.  Of course, here, the listed capacity is 0, so PhoneBook
     * is not assigned any memory according to the calloc function. This
     * assignment is included for form's sake, to match the free(PhoneBook)
     * statement at the end of the main() function.  Adhering to the form
     * of matching memory allocation and memory freeing will ensure careful
     * programming.
     */
    PhoneBook = (ListEntryType *) calloc(iCapacity, sizeof(ListEntryType));
    
    /* cUserChoice will take on the value of the user's main menu choice.
     * The following loop will continue to execute until the user chooses
     * to exit.
     */
    char cUserChoice = '\0';
    do {
        // The menu is displayed and the user enters her choice.
        printMenu ();
        getChoice (&cUserChoice);
        
        // The appropriate function is called.
        switch (cUserChoice) {
            case '1':
                addEntry (PhoneBook, &iLength, &iCapacity);
                break;
            case '2':
                deleteEntry (PhoneBook, &iLength);
                break;
            case '3':
                showAllEntries (PhoneBook, &iLength);
                break;
        }
    } while (cUserChoice != '4');
    printf ("Goodbye!\n\n");
    
    // Freeing allocated memory.
    free (PhoneBook);
}

// printMenu displays the menu.
void printMenu () {
    printf("\nPhone Book Application:");
    printf("\n\t(1) Add Friend");
    printf("\n\t(2) Delete Friend");
    printf("\n\t(3) Show Phone Book"); 
    printf("\n\t(4) Exit\n\n");
}

/* getChoice obtains the user's menu choice. The char variable representing
 * the user's choice must be passed to getChoice by reference.
 */
void getChoice (char *cChoice) {
    /* The user's input will be collected in cInputString and then validated.
     * iMaxLength represents the maximum characters that cInputString can store.
     */
    char *cInputString = NULL;	
    int iMaxLength = 1000;

    /* If there is not enough memory for cInputString to store iMaxLength
     * characters, then iMaxLength is decremented by 10, and memory allocation
     * is again attempted.  This continues until either cInputString has been
     * allocated memory or iMaxLength is no longer a positive integer.
     */
    while (cInputString == NULL && iMaxLength > 0) {
        cInputString = (char *) calloc(iMaxLength + 1, sizeof(char)); 
        iMaxLength -= 10;
    }

    /* If calloc() was successful in allocating memory to cInputString, then
     * we may proceed.  Otherwise, an error message, "Out of memory." is printed
     * and the user's choice is recorded as '4' (choice "Exit") so that the
     * program will terminate.
     */
    if (cInputString != NULL) {
        
        /* The user must reenter her choice until her input exactly matches
         * one of the single characters '1', '2', '3', or '4'.
         */
        *cChoice = '\0';
        while (*cChoice < 49 || *cChoice > 52) {
            printf ("\rEnter your choice (1-4): ");
            scanf ("%s", cInputString);
            if (strlen(cInputString) == 1)
                *cChoice = *cInputString;
        }
    }
    else {
        printf("\nOut of memory.\n");
        *cChoice = '4';
    }
    
    // Allocated memory is freed.
    free(cInputString);
}

/* addEntry obtains a new record from the user and adds it to the stored 
 * phone book.  The phone book array of structures, its length, and its 
 * capacity are all passed by reference to the function.
 */
void addEntry(ListEntryType *pList, int *iLen, int *iCap) {
    printf ("You chose to add a friend.\n");

    /* The integer variable lMemoryError stores a logical value (0, false;
     * 1, true) indicating whether a memory reallocation routine has been 
     * completely unsuccessful. lMemoryError starts out as 0 (false).
     */
    int lMemoryError = 0;

    /* If the arrays length is equal to its capacity, then the phone book's
     * allocated memory is completely filled and new memory must be obtained.
     */
    if (*iLen == *iCap) {

        /* A new pointer of ListEntryType is declared, and realloc() searches for
         * enough memory to retain all records stored in pList and add one more.
         */
        ListEntryType *pNewList = NULL;
        pNewList = (ListEntryType *) realloc(pList, (*iCap + 1) * sizeof(ListEntryType));
        
        /* If realloc() was successful, then pList takes on the new memory 
         * location, which may or may not be different from the old one.
         * Meanwhile, the capacity counter iCap is incremented by one to
         * reflect that there is more room now available for the PhoneBook.
         */
        if (pNewList != NULL) { 
            pList = pNewList;
            (*iCap)++;
        }
            /* If realloc() was not successful, a memory error message i printed
             * and the logical variable lMemoryError is set to 1 (true).
             */
        else {
            printf ("\nOut of memory.\n");
            lMemoryError = 1;
        }
    }

    // If a memory error was not encountered, then we can proceed.    
    if (!lMemoryError) {

        // cInputString is prepared just as above in function getChoice.
        char *cInputString = NULL;	
        int iMaxLength = 1000;
        while (cInputString == NULL && iMaxLength > 0) {
            cInputString = (char *) calloc(iMaxLength + 1, sizeof(char)); 
            iMaxLength -= 10;
        }

        /* If cInputString was allocated memory, then the user can proceed
         * to input field data into cInputString.  
         */
        if (cInputString != NULL) {

            /* The maximum allowed characters for each field are copied into 
             * the array of ListEntryType. This process ensures that the user's 
             * input will not be allowed to overload the ListEntryType fields.
             * The index ot the new record is iLen, because the previously
             * stored entries are indexed from 0 to iLen - 1, where iLen 
             * stands for the length of the array so far.
             */
            printf ("First Name: ");
            scanf ("%s", cInputString);
            strncpy ((pList + *iLen)->cFirstName, cInputString, 20);
            printf ("Last Name: ");
            scanf ("%s", cInputString);
            strncpy ((pList + *iLen)->cLastName, cInputString, 20);
                /* The user is reminded to leave spaces out of the phone number,
                 * because scanf() recognizes each space as a string terminator.
                 */
            printf ("Phone Number (without spaces): ");
            scanf ("%s", cInputString);
            strncpy ((pList + *iLen)->cPhoneNumber, cInputString, 15);
   
            /* The array length counter iLen (iLength in main()) is incremented
             * to indicate that one more entry has been added to the phone book.
             */
            (*iLen)++;
            printf ("Record added to the phone book.\n");
        }
            /* If cInputString was not allocated memory, then an error is printed
             * and the logical variable lMemoryError is set to 1 (true).
             */
        else {
            printf ("\nOut of memory.\n");
            lMemoryError = 1;
        }

    /* Allocated memory is freed from cInputString. If no memory was allocated
     * free() does nothing.
     */
    free(cInputString);
    }
}

/* deleteEntry allows the user to enter the first and last name belonging to a 
 * particular entry and deletes that entry from the array of phone records.
 */
void deleteEntry (ListEntryType *pList, int *iLen) {
    printf ("You chose to delete a friend.\n");
    int lMemoryError = 0;

    /* Memory for cInputFirstName and cInputLastName is allocated similarly
     * to cInputString in previous functions. This function requires two 
     * input variables because both first and last name have to be matched
     * to locate the record that will be deleted.
     */
    char *cInputFirstName = NULL;
    char *cInputLastName = NULL;
    int iMaxLength = 1000;
    while ((cInputFirstName == NULL || cInputLastName == NULL) && iMaxLength > 0){
        cInputFirstName = (char *) calloc(iMaxLength + 1, sizeof(char));
        cInputLastName = (char *) calloc(iMaxLength + 1, sizeof(char));
        iMaxLength -= 10; 
    }

    /* If memory was allocated for both cInputFirstName and cInputLastName,
     * then we can proceed. Otherwise, an error is printed and the error
     * is recorded in the value of lMemoryError.
     */
    if (cInputFirstName != NULL && cInputLastName != NULL) {
        // The user enters the first and last name of the unwanted record.
        printf ("First Name: ");
        scanf ("%s", cInputFirstName);
        printf ("Last Name: ");
        scanf ("%s", cInputLastName);

        /* The following loop counts through the elements of the array of
         * phone records and terminates if either 1) an entry is found with
         * first name and last name matching the user's input or 2) all
         * entries have been considered and no match has been found.
         */
        int i = 0;
        while ((strcmp((pList + i)->cFirstName, cInputFirstName) || strcmp((pList + i)->cLastName, cInputLastName)) && i < *iLen) 
            i++;
       
        /* The value of i is now less than the length of the array only if
         * a match was found. Otherwise, the two will be equal.
         */
        if (i < *iLen) {
            /* The following code "deletes" an array element by shifting
             * all of the following elements by one index. The length counter
             * is also decremented.  The unwanted entry is either overwritten
             * or, if it was at the end of the array, just ignored because
             * it is not counted in the length tally.
             */
            int j;
            for (j = i; j < *iLen - 1; j++) {
                strcpy ((pList + j)->cFirstName, (pList + j + 1)->cFirstName);
	        strcpy ((pList + j)->cLastName, (pList + j + 1)->cLastName);
                strcpy ((pList + j)->cPhoneNumber, (pList + j + 1)->cPhoneNumber);
            }
                (*iLen)--;
	        printf ("Record deleted from the phone book.\n");
    	}
            // If a match wasn't found, the user is notified.
        else {
            printf ("Record not found.\n");
        }
    }
       // If cInputFirstName and cInputLastName were not allocated memory:
    else {
        printf("\nOut of memory.\n");
        lMemoryError = 1;
    }

    // Allocated memory is freed from cInputFirstName and cInputLastName.
    free(cInputFirstName);
    free(cInputLastName); 
}

/* showAllEntries simply displays all the currently stored entries in the 
 * list of phone records. No data is changed, but both the Phone Book and
 * the length counter are passed by reference, to save memory and maintain
 * consistency with the other functions.
 */
void showAllEntries (ListEntryType *pList, int *iLen) {
    printf ("\nPhone Book Entries (%d):", *iLen);
    int i;
    for (i = 0; i < *iLen; i++)
        printf ("\n%s\t%s\t%s", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
    printf ("\n");
}
