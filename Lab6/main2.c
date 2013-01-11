/* Amar Shah
 * 
 * Introduction to Programming Languages, CECS 130-50
 * Lab Assignment #6
 * 16 June 2012
 * 
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct ListEntry {
    char cFirstName[21];
    char cLastName[21];
    char cPhoneNumber[16];
} ListEntryType;

void printMenu ();
void getChoice (char *);
void addEntry (ListEntryType *, int *, int *);
void deleteEntry (ListEntryType *, int *);
void showAllEntries (ListEntryType *, int *);

main()
{
    ListEntryType *PhoneBook;
	PhoneBook = (ListEntryType *) calloc(iCapacity, sizeof(ListEntryType));
	int iLength = 0;
	int iCapacity = 0;
	char cUserChoice = '\0';
	
	do {
	    printMenu ();
	    getChoice (&cUserChoice);
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
	free (PhoneBook);
}

void printMenu () {
    printf("\nPhone Book Application:");
    printf("\n\t(1) Add Friend");
    printf("\n\t(2) Delete Friend");
    printf("\n\t(3) Show Phone Book"); 
    printf("\n\t(4) Exit\n\n");
}

void getChoice (char *cChoice) {
	char *cInputString = NULL;	
	int iMaxLength = 1000;
	
    //printf ("Before memory is allocated, cInputString is %p.\n", cInputString);
	while (cInputString == NULL && iMaxLength > 0) {
		cInputString = (char *) calloc(iMaxLength + 1, sizeof(char)); 
		iMaxLength -= 10;
	}
	//printf ("Memory storage will begin at %p.\nDo not enter more than %d characters.\n", cInputString, iMaxLength);
    
	if (cInputString != NULL) {
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
	free(cInputString);
}

void addEntry(ListEntryType *pList, int *iLen, int *iCap) {
    printf ("You chose to add a friend.\n");

    int lMemoryError = 0; // Logical Integer lMemoryError
	//if (p->iLength > p->iCapacity) {}
	//else 
	if (*iLen == *iCap) {
		//if the length of the list is at capacity, then we need to allocate more memory.
		//find a pointer with enough memory available
	    ListEntryType *pNewList = NULL;
    	pNewList = (ListEntryType *) realloc(pList, (*iCap + 1) * sizeof(ListEntryType));
		if (pNewList != NULL) { 
		    // Take on new pointer (or keep old one).
			pList = pNewList;
			// Increase recorded capacity:
			(*iCap)++;
		}
		else {
			printf ("\nOut of memory.\n");
			lMemoryError = 1;
		}
	}
	//printf ("New max items %d.\n", *iCap);
    
	if (!lMemoryError) {
	    int iMaxLength = 1000;
	    char *cInputString = NULL;	
        //printf ("Before memory is allocated, cInputString is %p.\n", cInputString);
	    while (cInputString == NULL && iMaxLength > 0) {
		    cInputString = (char *) calloc(iMaxLength + 1, sizeof(char)); 
			iMaxLength -= 10;
	    }
		if (cInputString != NULL) {
	        
			printf ("First Name: ");
		    scanf ("%s", cInputString);
		    strncpy ((pList + *iLen)->cFirstName, cInputString, 20);
		    
			printf ("Last Name: ");
		    scanf ("%s", cInputString);
		    strncpy ((pList + *iLen)->cLastName, cInputString, 20);
		    
			printf ("Phone Number (without spaces): ");
		    scanf ("%s", cInputString);
			strncpy ((pList + *iLen)->cPhoneNumber, cInputString, 15);
	
			(*iLen)++;
			printf ("Record added to the phone book.\n");
        }
		else {
			printf ("\nOut of memory.\n");
			lMemoryError = 1;
		}
		free(cInputString);
	}
}

void deleteEntry (ListEntryType *pList, int *iLen) {
	printf ("You chose to delete a friend.\n");
	int lMemoryError = 0;
	int iMaxLength = 1000;
	char *cInputFirstName = NULL;
	char *cInputLastName = NULL;
	while ((cInputFirstName == NULL || cInputLastName == NULL) && iMaxLength > 0){
	    cInputFirstName = (char *) calloc(iMaxLength + 1, sizeof(char));
		cInputLastName = (char *) calloc(iMaxLength + 1, sizeof(char));
		iMaxLength -= 10; 
	}
	if (cInputFirstName != NULL && cInputLastName != NULL) {
		printf ("First Name: ");
		scanf ("%s", cInputFirstName);
		printf ("Last Name: ");
		scanf ("%s", cInputLastName);
		int i = 0;
		while ((strcmp((pList + i)->cFirstName, cInputFirstName) || strcmp((pList + i)->cLastName, cInputLastName)) && i < *iLen) 
		    i++;
		if (i < *iLen) {
			int j;
			for (j = i; j < *iLen - 1; j++) {
				strcpy ((pList + j)->cFirstName, (pList + j + 1)->cFirstName);
			    strcpy ((pList + j)->cLastName, (pList + j + 1)->cLastName);
				strcpy ((pList + j)->cPhoneNumber, (pList + j + 1)->cPhoneNumber);
			}
			(*iLen)--;
			printf ("Record deleted from the phone book.\n");
		}
		else {
			printf ("Record not found.\n");
		}
			
	}
	else {
		printf("\nOut of memory.\n");
		lMemoryError = 1;
	}
	free(cInputFirstName);
	free(cInputLastName); 
}

void showAllEntries (ListEntryType *pList, int *iLen) {
    printf ("\nPhone Book Entries (%d):", *iLen);
	int i;
	for (i = 0; i < *iLen; i++)
		printf ("\n%s\t%s\t%s", (pList + i)->cFirstName, (pList + i)->cLastName, (pList + i)->cPhoneNumber);
	printf ("\n");
}