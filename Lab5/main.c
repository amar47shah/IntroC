/* Amar Shah
 * 
 * Introduction to Programming Languages, CECS 130-50
 * Lab Assignment #4
 * 9 June 2012
 * 
 * A C program that generates a short story.  The user is asked to 
 * enter personal information, which is inserted into a story.  The 
 * exact details of the story vary according to the user information
 * and according to the values of random variables.  Each new set
 * of information is stored as a separate record in a list, so that, 
 * on repeated trials, a new story can be generated which features
 * a previously used "main character".
 *
 * The generated story is closely based on the very short story 
 * "Give It Up!", by Franz Kafka.  The original full text of Kafka's 
 * story can be found online here: 
 *
 * http://www.flashfictiononline.com/fpublic0034-give-it-up-franz-kafka.html
 *
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

/* StoryCharacter defines a structure whose members are strings
 * (character arrays) representing a story character's name, 
 * birthplace, workplace, brand/model of cellphone, and favorite 
 * presidential candidate.  In addition, the structure includes 
 * three members that indicate the story character's appropriate 
 * personal pronouns.
 *
 * Instances of this structure are declared with the label 
 * 'StoryCharacterType'.
 */
typedef struct StoryCharacter {
    char Name[15];
    char Birthplace[30];
    char Workplace[30];
    char Cellphone[30];
    char CandidateChoice[30];
    char HeShe[10];
    char HimHer[10];
    char HisHer[10];
} StoryCharacterType;

/* The List structure includes an array of StoryCharacterType,
 * an integer variable iLength that refers to the number of 
 * records currently stored in the array, and an integer iStar 
 * whose value represents the array index of the story character
 * record that will be used to generate the story.
 * 
 * Instances of the List structure are declared with the label
 * 'ListType'.  
 */
typedef struct List {
	StoryCharacterType MainCharacter[5];
	int iLength;
	int iStar;
} ListType;

/* Function prototypes: iSayYes obtains the user's answer to
 * a yes/no question, and casts it as a boolean binary integer
 * (0/'false' for 'no', 1/'true' for 'yes').  GetNewCharacter 
 * manages the inputting of a new record, and PrintStory 
 * generates and prints the story.
 */
int iSayYes();
void GetNewCharacter(ListType *);
void PrintStory(StoryCharacterType *);

main()
{
    /* The List UsualSuspects is declared.  All strings are
     * initialized to "" and integers to 0.  pList is declared
     * as a pointer of ListType and initialized to the address
     * of UsualSuspects.  Throughout the program, the pointer
     * pList will be used to reference the List UsualSuspects.
     */
    ListType UsualSuspects = {{""}, 0, 0};
    ListType *pList = &UsualSuspects;

    /* iNewPerson and iPlayAgain are integer variables that
     * represent boolean values, for use in the control flow
     * of the main program.  They are initialized to 'true'.
     */
    int iNewPerson = 1, iPlayAgain = 1;

    while (iPlayAgain) {
        printf ("\nStory Generator: A story about you!\n");

        /* If no records are currently stored in the List
         * (i.e., the program has just started) then the
         * user must enter a new record before continuing.
         * If there are at least 1, and less than 5, records
         * in the List so far, then the user may choose
         * whether to enter a new record or generate the 
         * story using an existing record.  If there are
         * already 5 records stored, then the List is filled
         * to maximum capacity, and the user must choose
         * to generate the story using an existing record.
         */
        if (pList->iLength == 0)
            iNewPerson = 1;
        else if (pList->iLength > 0 && pList->iLength < 5) {
            printf ("\nNew Person? (Y/N) ");
            iNewPerson = iSayYes();
        }
        else
            iNewPerson = 0;

        if (iNewPerson) {

            /* To add a new record, the program calls the function
             * GetNewCharacter with the pointer pList as argument.
             * pList points to the List data structure UsualSuspects.
             * (UsualSuspects is passed by reference.)
             */
            GetNewCharacter(pList);

            /* Using pointer syntax, UsualSuspects.iStar is
             * assigned the value of the index of the latest 
             * new record. This record indexed by iStar will 
             * be used to generate the story.
             */
            pList->iStar = pList->iLength - 1;
        }
        else {
            /* If the user wishes to (or is required to) reuse a
             * previously entered character record, a list of all
             * the stored character names is printed, and the user
             * is prompted to choose one.
             */ 
            printf ("\nHere are all the characters.\n");
            int i;
            for (i = 0; i < pList->iLength; i++)
                printf ("%s\n", pList->MainCharacter[i].Name);
            
            /* The user is prompted again until her choice matches
             * one of the names in the list.  UsualSuspects.iStar
             * is assigned the index of the StoryCharacter array 
             * MainCharacter[], whose member Name matches the user
             * input.
             */
            pList->iStar = pList->iLength;
            do {
                char cCharacterChoice[15];
                printf ("\rChoose a character from the list. ");
                scanf ("%s", cCharacterChoice);
                
                // Searching for a match.
                i = 0;
                while (i < pList->iLength && strcmp(cCharacterChoice, pList->MainCharacter[i].Name))
                    i++;
                
                /* iStar is assigned the value of i.  If there was
                 * no match, then the value assigned to iStar is 
                 * too big to stop the loop.
                 */
                pList->iStar = i;
            } while (pList->iStar > pList->iLength - 1);
        }  // End of conditional statement block: (!iNewPerson)

        /* A pointer, pHero, is declared as StoryCharacterType
         * and initialized to point to the element indexed by iStar
         * in the array MainCharacter.  pHero now points to the
         * structure (of type StoryCharacter) that contains all 
         * the information necessary to generate the story.  
         */
        StoryCharacterType *pHero = &pList->MainCharacter[pList->iStar];

        /* pHero is passed to PrintStory, and thus the appropriate
         * StoryCharacter element of the array MainCharacter is
         * passed by reference.
         */
        PrintStory(pHero);

        // The user decides whether to play again.
        printf ("Do you want to play again? (Y/N) ");
        iPlayAgain = iSayYes();
    }  // End of while loop: (iPlayAgain)
    printf ("\nGoodbye!\n");
}

int iSayYes() {
    /* The user's response to a Y/N question is inputted
     * as a (possibly) much longer string.
     */
    char cInputString[15] = {'\0'};
    scanf ("%s", cInputString);

    /* The answer is counted as 'yes' only if the first character
     * of the entered string is either 'y' or 'Y'.  The integer 
     * values 1 and 0 are returned, representing 'true' (the 
     * user chose 'yes') and 'false' (the user did not choose 
     * 'yes'), respectively.
     */
    if (*cInputString == 'y' || *cInputString == 'Y')
        return 1;
    else
        return 0;
}  // End of function definition iSayYes()

void GetNewCharacter(ListType *p) {
    /* The value of iLength corresponds to the number of elements
     * currently stored in a List.  Therefore the last element is
     * indexed by iLength - 1.  A new item in the List will
     * therefore take the index iLength, BEFORE it is incremented
     * to represent the new number of items in the list. iItem 
     * refers to the index of the new character record in
     * UsualSuspects.MainCharacter[].
     */
    int iItem = p->iLength++;
    
    /* Every character record must be given a distinct name, so
     * that a reused character record can be unambiguously chosen.
     * The name is entered in a special input string and then
     * compared to names stored in existing records.
     */
    char cInputString[15] = {'\0'};
    printf ("\nWhat is your name? ");
    scanf ("%s", cInputString);
    
    // Searching for a match.
    int i = 0;
    while (i < iItem && strcmp(cInputString, p->MainCharacter[i].Name))
        i++;

    /* If, after the previous process, the counter i is too small,
     * then a match has been found.  The user is prompted to enter a
     * new name.  The loop executes until the user has entered a 
     * previously unused StoryCharacter Name.
     */
    while (i < iItem) {
        printf ("\rPlease choose a new name. ");
        scanf ("%s", cInputString);
        i = 0;
        while (i < iItem && strcmp(cInputString, p->MainCharacter[i].Name))
            i++;
    }
    
    /* The name of the new character is copied into the Name field
     * of the new StoryCharacter in the List, the element of array
     * UsualSuspects.MainCharacter[], indexed by iItem.
     */
    strcpy (p->MainCharacter[iItem].Name, cInputString);

    /* The process of reading in the values of MainCharacter[iItem]
     * .Birthplace, .Workplace, .Cellphone, and .CandidateChoice
     * is comparatively simpler.  These do not have to be distinct
     * from corresponding values in records already stored.
     */
    printf ("In what town or city were you born? ");
    scanf ("%s", p->MainCharacter[iItem].Birthplace);
    printf ("Where do you work? ");
    scanf ("%s", p->MainCharacter[iItem].Workplace);
    printf ("What kind of cellphone handset do you use? ");
    scanf ("%s", p->MainCharacter[iItem].Cellphone);
    printf ("Who will you vote for President in 2012? ");
    scanf ("%s", p->MainCharacter[iItem].CandidateChoice);

    /* Rather than ask the user to assign a gender to the
     * the new character, the program asks the user to define
     * the set of pronouns used to refer to the character.
     * The user may easily choose standard masculine or 
     * feminine options or instead may choose to define the
     * pronouns explicity.
     */
    for (i = 0; i < 15; i++)
        cInputString[i] = '\0';
    printf ("\nEnter 'F' to use feminine pronouns (she/her/her)");
    printf ("\n   or 'M' to use masculine pronouns (he/him/his)");
    printf ("\n   or any other key to define your own pronouns. ");
    scanf ("%s", cInputString);
    switch (*cInputString) {
        case 'f': case 'F':
            strcpy (p->MainCharacter[iItem].HeShe, "she");
            strcpy (p->MainCharacter[iItem].HimHer, "her");
            strcpy (p->MainCharacter[iItem].HisHer, "her");
            break;
        case 'm': case 'M':
            strcpy (p->MainCharacter[iItem].HeShe, "he");
            strcpy (p->MainCharacter[iItem].HimHer, "him");
            strcpy (p->MainCharacter[iItem].HisHer, "his");
            break;
        default:
            printf ("\nYou chose to define your own pronouns.");
            printf ("\nInstead of 'she' or 'he', I wish to be called: ");
            scanf ("%s", p->MainCharacter[iItem].HeShe);
            printf ("Instead of 'her' or 'him', I wish to be called: ");
            scanf ("%s", p->MainCharacter[iItem].HimHer);
            printf ("Instead of 'her' or 'his', I wish to use: ");
            scanf ("%s", p->MainCharacter[iItem].HisHer);
            break;
    }  // End of switch (*cInputString)
}  // End of function definition GetNewRecord()

void PrintStory (StoryCharacterType *p) {
    /* The function PrintStory receives a pointer reference to the
     * StoryCharacter structure that contains all of the user-
     * defined information for the main character of the story to
     * be generated.  An array containing random integers (0-3)
     * accounts for the remainder of the story's changing text.
     *
     * iStoryBoard, an integer array of 9 elements, is defined
     * and subsequently filled with random integer values, 0 to 3.
     */
    int i, iStoryBoard[9] = {0};
    srand(time(NULL));
    for (i = 0; i < 9; i++)
        iStoryBoard[i] = (rand() % 4);

    // The text of the story is now outputted.
    printf ("\nIt was ");
    /* Where multiple fixed options exist for story text, the 
     * program chooses between them by consulting the value of 
     * the corresponding element of iStoryBoard.
     */
    switch (iStoryBoard[0]) {
        case 0:
            printf ("very early in the morning");
            break;
        case 1:
            printf ("late at night");
            break;
        case 2:
            printf ("the longest day of summer");
            break;
        case 3:
            printf ("the middle of NPR pledge week");
            break;
    }
    printf (", the streets\n");
    switch (iStoryBoard[1]) {
        case 0:
            printf ("clean and deserted");
            break;
        case 1:
            printf ("filthy with 100-dollar bills");
            break;
        case 2:
            printf ("riddled with potholes");
            break;
        case 3:
            printf ("blanketed in snow");
            break;
    }
    /* User-defined information is retrieved from the StoryCharacter
     * structure using the passed pointer (or its alias, rather) and
     * pointer syntax.  The information is simply inserted into the 
     * position in the text where it should appear.
     */
    printf (".  %s was walking to %s.", p->Name, p->Workplace);
    printf ("\nAs %s compared ", p->Name);
    switch (iStoryBoard[2]) {
        case 0:
            printf ("the tower clock");
            break;
        case 1:
            printf ("the flashing bank marquee");
            break;
        case 2:
            printf ("the sun");
            break;
        case 3:
            printf ("%s car radio clock", p->HisHer);
            break;
    }
    printf (" with %s %s", p->HisHer, p->Cellphone);
    printf ("\n%s realized that it was already much later than", p->HeShe);
    printf ("\n%s had thought.  %s had to hurry, the shock", p->HeShe, p->Name);
    printf ("\nof this discovery made %s unsure of the way,", p->HimHer);
    printf ("\n%s ", p->HeShe);
    switch (iStoryBoard[3]) {
        case 0:
            printf ("did not yet know %s way very well in", p->HisHer);
            break;
        case 1:
            printf ("had not bothered to learn how to get around in");
            break;
        case 2:
            printf ("was a stranger in");
            break;
        case 3:
            printf ("had lost %s map of", p->HisHer);
    }
    printf (" %s;\nluckily, %s was ", p->Birthplace, p->CandidateChoice);
    switch (iStoryBoard[4]) {
        case 0:
            printf ("nearby");
            break;
        case 1:
            printf ("in the park");
            break;
        case 2:
            printf ("directing traffic");
            break;
        case 3:
            printf ("walking the family dog");
            break;
    }
    printf (", %s ran up to %s", p->Name, p->CandidateChoice);
    printf ("\nand ");
    switch (iStoryBoard[5]) {
        case 0:
            printf ("breathlessly");
            break;
        case 1:
            printf ("desperately");
            break;
        case 2:
            printf ("languorously");
            break;
        case 3:
            printf ("meekly");
            break;
    }
    printf (" asked the way.  %s smiled", p->CandidateChoice);
    printf ("\nand said: \"From me you want to know the way?\"");
    printf ("\n\"Yes,\" %s said, \"since ", p->Name);
    switch (iStoryBoard[6]) {
        case 0:
            printf ("I cannot find it myself");
            break;
        case 1:
            printf ("I am late for my hair appointment");
            break;
        case 2:
            printf ("I must get to work on time");
            break;
        case 3: 
            printf ("I voted for you");
            break;
    }
    printf (".\"\n\"");
    switch (iStoryBoard[7]) {
        case 0:
            printf ("Give it up! Give it up");
            break;
        case 1:
            printf ("Give me a dollar and I will take you there");
            break;
        case 2:
            printf ("Trust in the Lord. He will answer your prayers");
            break;
	case 3:
            printf ("Sure. Take a left on Clark Road and a right on Powers Lane,\nand it will be just over the bridge, can't miss it");
            break;
    }
    printf (",\" %s said, and\n", p->CandidateChoice);
    switch (iStoryBoard[8]) {
        case 0:
            printf ("turned away with a sudden jerk, like people who want\nto be alone with their laughter");	    
            break;
        case 1:
            printf ("took %s by the hand, squeezing %s fingers urgently", p->Name, p->HisHer);
            break;
        case 2:
            printf ("pointed encouragingly down the road");
            break;
        case 3:
            printf ("shrugged mightily on the pavement");
            break;
    }
    printf (".\n\n");
}  // End of function definition PrintStory()
