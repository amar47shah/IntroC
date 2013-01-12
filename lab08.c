/* Amar Shah
 * 
 * Introduction to Programming Languages, CECS 130-50
 * Lab Assignment #8
 * 30 June 2012
 * 
 * An application for managing a list of phone numbers, written in C.
 *
 * The user can add entries to a phone book, display all the entries
 * and choose entries to be deleted.  There is no limit to the number
 * of entries that may be stored, beyond the system's own memory limit.
 * 
 * The user may also load phone book entries from a file or save all
 * entries in memory to a file.  The user may choose to specify a file
 * path or may accept the default path: "(current directory)/contacts.dat"
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* The structure ListContact carries all the data of a phone book entry:
 * strings for first name, last name, and phone number. The structure
 * is defined as the blueprint for the type ContactType.
 */
typedef struct ListContact {
    char cFirstName[21];
    char cLastName[21];
    char cPhoneNumber[16];
} ContactType;

/* Function prototypes: printMenu displays the main menu; getChoice
 * obtains the user's menu choice from a specified range of choices; 
 * and the remaining subroutines each direct a particular function 
 * of the application.
 */
void printMainMenu ();
void getChoice (char *, const char);
void showAllContacts (ContactType *, int *);
void addContact (ContactType **, int *, int *);
void findContact (ContactType *, int *);
void getRandomContact (ContactType *, int *);
void deleteContact (ContactType *, int *);
void deleteAllContacts (int *, int *);
void saveContactsToFile (ContactType *, int *);
void loadContactsFromFile (ContactType **, int *, int *);

// Main function: Program execution begins.
main()
{
    
    /* Phonebook points to (the first element) of an array of structures
     * of ContactType.  Each element of the array contains all the 
     * information for one record: first name, last name, and phone 
     * number. Integer variables iLength and iCapacity each contain 
     * information about the array.  iCapacity indicates the number of
     * entries which can be stored according to current memory allocation;
     * when iCapacity = 5, then no more than 5 records can be stored.
     * iLength indicates the number of records that are currently stored.
     * (Therefore, the last element in the array is indexed by iLength - 1.)
     */
    ContactType *PhoneBook;
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
    PhoneBook = (ContactType *) calloc(iCapacity, sizeof(ContactType));
    
    /* cUserChoice will take on the value of the user's main menu choice.
     * The following loop will continue to execute until the user chooses
     * to exit.  The constant identifier cLastChoice contains the character
     * representing the last available choice ('Exit').  If the program
     * is modified to accommodate a larger or smaller menu, this constant
     * can be changed conveniently.
     */
    char cUserChoice = '\0';
    const char cLastChoice = '9';

    do {
        
        // The menu is displayed and the user enters her choice.
        printMainMenu ();
        getChoice (&cUserChoice, cLastChoice);
        
        // The appropriate function is called.
        switch (cUserChoice) {
            case '1':
                showAllContacts (PhoneBook, &iLength);
                break;
            case '2':
                addContact (&PhoneBook, &iLength, &iCapacity);
                break;
            case '3':
                findContact (PhoneBook, &iLength);
                break;
            case '4':
                getRandomContact (PhoneBook, &iLength);
                break;
            case '5':
                deleteContact (PhoneBook, &iLength);
                break;
            case '6':
                deleteAllContacts (&iLength, &iCapacity);
                break;
            case '7':
                saveContactsToFile (PhoneBook, &iLength);
                break;
            case '8':
                loadContactsFromFile (&PhoneBook, &iLength, &iCapacity);
                break;
        }
        // The application continues until the user chooses to exit.
    } while (cUserChoice != cLastChoice);
    
    // Freeing allocated memory.
    free (PhoneBook);

    printf ("\nGoodbye!\n\n");
}

// printMenu displays the menu.
void printMainMenu () {
    printf("\nPhone Book Application:");
    printf("\n\t(1) Show Phone Book");
    printf("\n\t(2) Add Contact");
    printf("\n\t(3) Find Contact");
    printf("\n\t(4) Get Random Contact");
    printf("\n\t(5) Delete Contact");
    printf("\n\t(6) Delete All Contacts");
    printf("\n\t(7) Save Contacts to File");
    printf("\n\t(8) Load Contacts from File"); 
    printf("\n\t(9) Exit\n\n");
}

/* getChoice obtains the user's menu choice. The char variable representing
 * the user's choice must be passed to getChoice by reference.  The constant
 * char cLChoice contains the literal value of the final choice in the menu.
 */
void getChoice (char *cChoice, const char cLChoice) {
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
     * we may proceed.  Otherwise, an error message is printed and the program
     * terminates.
     */
    if (cInputString != NULL) {
        
        /* The user must reenter her choice until her input exactly matches
         * one of the single characters '1' through cLChoice, which we assume
         * to have an ASCII value greater than '1', with all intermediate
         * characters representing legitimate choices.
         */
        *cChoice = '\0';
        while (*cChoice < '1' || *cChoice > cLChoice) {
            printf ("\rEnter your choice (1-%c): ", cLChoice);
            scanf ("%s", cInputString);
            if (strlen(cInputString) == 1)
                *cChoice = *cInputString;
        }
    }
    else {
        /* If calloc() was unsuccessful, an error message is printed and the
         * program terminates.
         */
        perror("Out of memory");
        exit(EXIT_FAILURE); 
    }
    
    // Allocated memory is freed.
    free(cInputString);
}

/* showAllContacts allows the user to sort the contacts by first or last name
 * (or choose not to sort the contacts) and then displays them all in a list.
 */
void showAllContacts (ContactType *pList, int *iLen) {
    int i;
       
    /* If the contact list has fewer than two entries, then sorting is trivial.
     * Therefore the sorting menu is presented only if the length of the list
     * is larger than 1.
     */
    if (*iLen > 1) {

        // cSortChoice will store the user's choice from the sorting menu.
        char cSortChoice = '\0';

        /* lContactsSwapped and TempHolder are needed for the sorting algorithm
         * (bubble-sort).  lContactsSwapped is a logical variable that indicates 
         * whether two entries in the list have been exchanged in the previous 
         * pass through the list. TempHolder holds an entry temporarily so that
         * it does not get unintendedly overwritten while it is being swapped.
         */
        int lContactsSwapped;
        ContactType TempHolder = {""};

        // The sorting menu is displayed and the user's choice obtained.
        printf ("\nWould you like to sort the entries?");
        printf ("\n\t(1) by Last Name");
        printf ("\n\t(2) by First Name");
        printf ("\n\t(3) Do Not Sort\n");
        getChoice (&cSortChoice, '3');
        
        /* The bubble-sort algorithm. On each pass through the array of ContactType
         * adjacent entries are compared, and swapped if they are out of order.
         * The process repeats if any two entries had to be swapped in the previous
         * iteration.  Once the array has been passed through without a swap, the
         * list is known to be sorted.
         */
        do {
            lContactsSwapped = 0;
            i = 0;
            while (i < *iLen - 1) {

                /* lSwapNeeded indicates whether the entry indexed by i should be 
                 * exchanged with the entry in the following position. lSwapNeeded 
                 * is a logical integer variable determined according to the user's 
                 * choice of sorting criteria.  If the user chose not to sort the 
                 * list, lSwapNeeded retains its initialized value, 0/false.
                 */
                int lSwapNeeded = 0;
                switch (cSortChoice) {
                    case '1':
                        lSwapNeeded = strcmp((pList + i)->cLastName, (pList + i + 1)->cLastName) > 0;
                        break;
                    case '2':
                        lSwapNeeded = strcmp((pList + i)->cFirstName, (pList + i + 1)->cFirstName) > 0;
                        break;
                }
 
                // If an exchange is necessary, this simple procedure accomplishes it.
                if (lSwapNeeded) {
                     TempHolder = *(pList + i);
                     *(pList + i) = *(pList + i + 1);
                     *(pList + i + 1) = TempHolder;
                     lContactsSwapped = 1;
                }
                i++;    
            } 
        } while (lContactsSwapped);  
    }

    //  Once sorting is complete, or if sorting was not necessary, the list is printed.
    printf ("\nPhone Book Contacts (%d):", *iLen);
    for (i = 0; i < *iLen; i++)
        printf ("\n%s\t%s\t%s", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
	printf ("\n");
}

/* addContact obtains a new record from the user and adds it to the stored 
 * phonebook.  The phonebook array of structures, its length, and its 
 * capacity are all passed by reference t333o the function.
 */
void addContact(ContactType **pList, int *iLen, int *iCap) {
    printf ("You chose to add a contact.\n");

    /* If the array's length is equal to its capacity, then the phone book's
     * allocated memory is completely filled and new memory must be obtained.
     */
    if (*iLen == *iCap) {

        /* A new pointer of ContactType is declared, and realloc() searches for
         * enough memory to retain all records stored in pList and add one more.
         */
        ContactType *pNewList = NULL;
        pNewList = (ContactType *) realloc(*pList, (*iCap + 1) * sizeof(ContactType));
        
        /* If realloc() was successful, then pList takes on the new memory 
         * location, which may or may not be different from the old one.
         * Meanwhile, the capacity counter iCap is incremented by one to
         * reflect that there is more room now available for the PhoneBook.
         */
        if (pNewList != NULL) { 
            *pList = pNewList;
            (*iCap)++;
        }
            /* If realloc() was not successful, a memory error message is printed
             * and the logical variable lMemoryError is set to 1 (true).
             */
        else {
            perror("Out of memory");
            exit(EXIT_FAILURE); 
        }
    }

    /* If a memory error was not encountered, then we can proceed.
     * cInputString is prepared just as above in function getChoice.
     */
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
         * the array of ContactType. This process ensures that the user's 
         * input will not be allowed to overload the ContactType fields.
         * The index ot the new record is iLen, because the previously
         * stored entries are indexed from 0 to iLen - 1, where iLen 
         * stands for the length of the array so far.
         */
        printf ("First Name: ");
        scanf ("%s", cInputString);
        strncpy ((*pList + *iLen)->cFirstName, cInputString, 20);
        printf ("Last Name: ");
        scanf ("%s", cInputString);
        strncpy ((*pList + *iLen)->cLastName, cInputString, 20);
            /* The user is reminded to leave spaces out of the phone number,
             * because scanf() recognizes each space as a string terminator.
             */
        printf ("Phone Number (without spaces): ");
        scanf ("%s", cInputString);
        strncpy ((*pList + *iLen)->cPhoneNumber, cInputString, 15);

        /* The array length counter iLen (iLength in main()) is incremented
         * to indicate that one more entry has been added to the phone book.
         */
        (*iLen)++;
        printf ("Contact added to the phone book.\n");
    }
    else {
        // If cInputString was not allocated memory, terminate the program.
        perror("Out of memory");
        exit(EXIT_FAILURE); 
    }

    // Allocated memory is freed from cInputString. 
    free(cInputString);
}

void findContact (ContactType *pList, int *iLen) {
    /* The user is allowed to search for a contact only if there is at least
     * one contact stored.
     */
    if (*iLen > 0) {

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
            char cSearchChoice = '\0';
            int i = 0;
            int lMatchFound = 0;
		  
            // The user can choose which field to use as a basis for the search.
            printf ("\nHow would you like to search?");
     	    printf ("\n\t(1) by Last Name");
            printf ("\n\t(2) by First Name");
    	    printf ("\n\t(3) by Phone Number\n");
            getChoice (&cSearchChoice, '3');
                    
            /* The user enters a field value to search for.  If the value
             * is the same as the corresponding field in a list entry, the
             * whole entry is printed.  Because this procedure uses strcmp()
             * to compare, the user's search value must match exactly,
             * including case.
             *
             * Depending on the user's choice, she may search for a particular
             * last name, first name, or phone number.  All entries with the
             * same value for the target field will be displayed. 
             */
            switch (cSearchChoice) {
     	        case '1':
                    printf ("\nLast Name: ");
                    scanf ("%s", cInputString);
                    while (i < *iLen) {
                        if (!strcmp((pList + i)->cLastName, cInputString)) {
                            printf ("%s\t%s\t%s\n", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
                            lMatchFound = 1;
                        }
                        i++;
                    } 
                    break;
                case '2':
                    printf ("\nFirst Name: ");
                    scanf ("%s", cInputString);
                    while (i < *iLen) {
                        if (!strcmp((pList + i)->cFirstName, cInputString)) {
                            printf ("%s\t%s\t%s\n", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
                            lMatchFound = 1;
                        }
                        i++;
                    }
                    break;
                case '3':
                    printf ("\nPhone Number: ");
                    scanf ("%s", cInputString);
                    while (i < *iLen)  {
                        if (!strcmp((pList + i)->cPhoneNumber, cInputString)) {
                            printf ("%s\t%s\t%s\n", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
                            lMatchFound = 1;
                        }
                        i++;
                    }
                    break;
            }
            /* If the logical variable lMatchFound was never set to 1, then no
             * match was found, and the user is notified.
             */
            if (!lMatchFound)
                printf ("No matches were found.\n");
        }
        else {
            // If cInputString was not allocated memory, terminate the program.
            perror("Out of memory");
            exit(EXIT_FAILURE); 
        }

        // Free allocated memory.
        free(cInputString);
    }
    else
        // If (*iLen == 0),
        printf ("There are no contacts to choose from.\n");
}

void getRandomContact (ContactType *pList, int *iLen) {
    /* If there are no contacts currently stored, then the user is notified
     * that the request could not be fulfilled.  Otherwise, a random index
     * is chosen of the PhoneBook array of ContactType. The entry corresponding
     * to this index is displayed.
     */
    if (*iLen > 0) {
        srand(time(NULL));
        int i = rand() % *iLen;
        printf ("\nRandom Contact:");
        printf ("\n%s\t%s\t%s\n", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
    }
    else
        printf ("There are no contacts to choose from.\n");
}

/* deleteContact allows the user to enter the first and last name belonging to a 
 * particular entry and deletes that entry from the array of phone records.
 */
void deleteContact (ContactType *pList, int *iLen) {

    /* If the list contains no entries, the user is informed that the task could
     * not be fulfilled.
     */
    if (*iLen > 0) {
        printf ("You chose to delete a contact.\n");

        /* Memory for cInputFirstName and cInputLastName is allocated similarly
         * to cInputString in previous functions. This function requires two 
         * input variables because both first and last name have to be matched
         * to locate the record that will be deleted.
         */
        char *cInputFirstName = NULL;
        char *cInputLastName = NULL;
        int iMaxLength = 1000;
        while ((cInputFirstName == NULL || cInputLastName == NULL) && iMaxLength > 0) {
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
                printf ("Contact deleted from the phone book.\n");
        	}
            // If a match wasn't found, the user is notified.
            else 
                printf ("Contact not found.\n");
        }
        else {
            
            /* If cInputFirstName and cInputLastName were not both allocated memory, 
             * terminate the program.
             */
            perror("Out of memory");
            exit(EXIT_FAILURE); 
        }

        // Allocated memory is freed from cInputFirstName and cInputLastName.
        free(cInputFirstName);
        free(cInputLastName); 
    }
    else
        printf ("There are no contacts to delete.\n");
}

void deleteAllContacts (int *iLen, int *iCap) {
    // If no entries are stored, the request is declined and the user is informed.
    if (*iLen > 0) {
        
        // The user chooses whether to confirm the decision to delete all contacts.
        char cConfirmChoice = '\0';
        printf ("\nDo you wish to delete all contacts?");
        printf ("\n\t(1) Yes");
        printf ("\n\t(2) No\n");
        getChoice (&cConfirmChoice, '2');

        /* If the user chooses to continue deleting all contacts, the following
         * procedure is executed: the length and capacity counters of the PhoneBook
         * are both set to zero.
         */
        if (cConfirmChoice == '1') {
            *iLen = 0;
            *iCap = 0;
            printf ("All contacts have been deleted.\n");
    	}
    	else
            printf ("All contacts have been retained.\n");
    }
    else
        printf ("There are no contacts to delete.\n");
}

void saveContactsToFile (ContactType *pList, int *iLen)
{
    // The function will not attempt to save contacts if none are in memory.
    if (*iLen > 0) {

        /* The constant string pointer cDefaultName stores the default file location.
         * cFileChoice stores the user's choice: whether 1) to enter a file location
         * or 2) accept the default file location. The FILE pointer pWrite will hold
         * the address of the filestream where the data will be saved.
         */
        const char *cDefaultFileName = "contacts.dat";
        char cFileChoice = '\0';
        char cFileName[51] = "";
        FILE *pWrite = NULL;
        
        // The user chooses whether to specify a path or accept the default.
        printf ("\nWhere do you want to save the contacts?");
        printf ("\n\t(1) Specify file-name path.");
        printf ("\n\t(2) Use default file-name path.\n");
        getChoice (&cFileChoice, '2');
		
        /* If the user chose to enter a file location, then she is prompted
         * for one and the input is saved as cInputString and copied to
         * cFileName.  If she chose to accept the default, then cDefaultFileName
         * is copied to cFileName.
         */
        if (cFileChoice == '1') {
            char *cInputString = NULL;	
            int iMaxLength = 1000;
            while (cInputString == NULL && iMaxLength > 0) {
                cInputString = (char *) calloc(iMaxLength + 1, sizeof(char)); 
                iMaxLength -= 10;
            }

            if (cInputString != NULL) {
                printf ("File-name (and location): ");
                scanf ("%s", cInputString);
                strncpy (cFileName, cInputString, 50);
            }
            else {
                // If cInputString was not allocated memory, terminate the program.
                perror("Out of memory");
                exit(EXIT_FAILURE); 
            }
            // Allocated memory is freed from cInputString. 
            free(cInputString);
        }
        else 
            strncpy (cFileName, cDefaultFileName, 50);

        // The file is opened for writing, and the filestream is saved as pWrite.
        pWrite = fopen(cFileName, "w");

        // If the file was opened successfully, we continue. Otherwise, an error is printed.
        if (pWrite != NULL) {

            // The first field of data written to the file is the number of entries. 
            fprintf (pWrite, "%d\n", *iLen);

            // Now, the entries are written to the file using a for-loop.
            int i;
            for (i = 0; i < *iLen; i++) 
                fprintf (pWrite, "%s\t%s\t%s\n", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
		
            // Finally, the file is closed, and a message is printed to the user.
            fclose (pWrite);
            printf ("Contacts saved to %s.\n", cFileName);
        }
        else 
            printf ("Invalid file-name or location.\n");
    }
    // If no contacts are in memory, then an error is printed to the user and the program continues.
    else
        printf ("There are no contacts to save.\n");
}

void loadContactsFromFile (ContactType **pList, int *iLen, int *iCap)
{
    char cConfirmChoice = '1';

    /* If there are contacts in memory, the user is asked whether to proceed
     * with loading from the file, which will overwrite the stored contacts.
     */
    if (*iLen > 0) {
        printf ("\nCurrently stored contacts will be lost. Continue?");
        printf ("\n\t(1) Yes");
        printf ("\n\t(2) No\n");
        getChoice (&cConfirmChoice, '2');
    }

    /* If there were no contacts stored in memory, or if the user decided
     * to overwrite them, then the procedure continues.  Otherwise, loading
     * the contacts is aborted and the contacts stored in memory are retained.
     */
    if (cConfirmChoice == '1') {
        const char *cDefaultFileName = "contacts.dat";
        char cFileChoice = '\0';
        char cFileName[51] = "";
        FILE *pRead = NULL; 

        // The user chooses whether to specify a path or accept the default.
        printf ("\nWhere are the contacts saved?");
        printf ("\n\t(1) Specify file-name path.");
        printf ("\n\t(2) Use default file-name path.\n");
        getChoice (&cFileChoice, '2');

        // If the user chose to specify a path:		
        if (cFileChoice == '1') {
            char *cInputString = NULL;	
            int iMaxLength = 1000;
            while (cInputString == NULL && iMaxLength > 0) {
                cInputString = (char *) calloc(iMaxLength + 1, sizeof(char)); 
                iMaxLength -= 10;
            }

            if (cInputString != NULL) {
                    // Get the user's path choice and copy it to cFileName.
                    printf ("File-name (and location): ");
                    scanf ("%s", cInputString);
                    strncpy (cFileName, cInputString, 50);
                }
            else {
                // If cInputString was not allocated memory, terminate the program.
                perror("Out of memory");
                exit(EXIT_FAILURE); 
            }
            // Allocated memory is freed from cInputString. 
            free(cInputString);
        }
        else
            // If the user chose to accept the default path: 
            strncpy (cFileName, cDefaultFileName, 50);

        // Open the file for reading.
        pRead = fopen(cFileName, "r");

        /* If the file was opened successfully, begin loading data.  Otherwise
         * issue an error.
         */
        if (pRead != NULL) {
            /* Read the first field in the data file as an integer.  This will be
             * the number of records which will be stored.  Since struct array
             * may not hold enough space for this many records, this value must
             * be used to allocate space.
             */
            int iNewCap = 0;
            fscanf (pRead, "%d", &iNewCap);

            ContactType *pNewList = NULL;
            pNewList = (ContactType *) realloc(*pList, iNewCap * sizeof(ContactType));

            /* If the allocation was successful, then the struct array is moved to the
             * the new pointer, and the new capacity is recorded.
             */
            if (pNewList != NULL) {
                *pList = pNewList;
                *iCap = iNewCap;
            }
            else {
                // If the allocation was unsuccesful, the program ends.
                perror ("Out of memory");
                exit(EXIT_FAILURE);
            }
            
            /* Now, the data can be read into the array of ContactType.  The integer
             * value at the beginning of the file determined how many entries will be
             * read.
             */
            int i;
            for (i = 0; i < *iCap; i++) 
                fscanf (pRead, "%s%s%s", (*pList + i)->cFirstName, (*pList + i)->cLastName, (*pList + i)->cPhoneNumber);
            
            /* The length of the list of entries is recorded as *iCap, the number of 
             * entries saved.
             */
            *iLen = *iCap;
            // Close the file and notify the user that the contacts have been loaded.
            fclose (pRead);
            printf ("Contacts loaded from %s.\n", cFileName);
        }
        else {
            // If the file could not be opened, notify the user.
            printf ("Invalid file-name or location.\n");
            printf ("Currently stored contacts are retained.\n");
        }
    }
    else
        // If the user chose not to overwrite stored contacts, notify her and continue execution.
        printf ("Currently stored contacts are retained.\n");
}
