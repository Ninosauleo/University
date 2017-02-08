/*

 File name: exerc_3_4.c (or cpp)

 Date: 2017-02-07

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <0000>] PENDING

a) Write a function that given an integer n, an array of integers and the size of the array determines
if n is in the array. If so the function should return the index for the first position of the number (in
case of several) otherwise returns -1.
For testing the function, write a main program that tests the function with help of an array initiated
in the main program as below and with a function declaration:


int search_number( int number, int tab[], int size);
int test [] = { 1,2,34,5,67,3,23,12,13,10};


b) There are a lot of ways to sort a field. For example, bubble sort which not is the fastest but easy to
understand and implement. Write a sorting routine that uses the following algorithm to sort an array
of integers.
• Find the minimum value in the list.
• Swap the minimum with the first in list.
• Repeat this but exclude the previous minimum on top of the list and search only in the rest of the
list.
Implement the sorting function using the function declaration:
void sort (int number, int tab []);
Test the function by use of a main program and an initiated array as above. For checking purpose
print out the sorted array.

 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>

#define MAX 20

#define filename "person_database.bin"
#define backupfilename "person_database.bak"


typedef struct {
    char firstname[20];
    char famnamne[20];
    char pers_number[13]; // yyyymmddnnnc
}PERSON;

/*
 *
 */
typedef char Str50[50];

PERSON *person_Collection;
PERSON temp;


/*
 *
 */

enum CHOICE {
    ONE = 1 , TWO = 2, THREE = 3, FOUR = 4, FIVE = 5
};

char readInput(char *pointer){
    fgets(pointer, MAX, stdin);
    char *pos;
    if ((pos=strchr(pointer, '\n')) != NULL) {
        *pos = '\0';
    }

    fseek(stdin,0,SEEK_END); //we need to flush the input of before.
    fflush(stdin);
}

int readln(char s[]) {
    char ch;
    int i;
    int chars_remain;
    i = 0;
    chars_remain = 1;
    while (chars_remain) {
        ch = getchar();
        if ((ch == '\n') || (ch == EOF) ) {
            chars_remain = 0;
        } else if (i < MAX - 1) {
            s[i] = ch;
            i++;
        }
    }
    s[i] = '\0';
    return i;
}

// returns index (0-based) of first char of searchstring in sourcestring
// or -1 if searchstring is not found
int searchstring(char searchstr[], char sourcestr[]) {
    char *ptrtostr;
    int foundat;
    foundat = -1;
    ptrtostr = strstr( sourcestr, searchstr );
    if ( ptrtostr != NULL ) {
        foundat = (int)((ptrtostr - sourcestr));
    }
    return foundat;
}


/*
PERSON person_Collection[10];
 */

void create_cdcollection() {
    person_Collection = (PERSON*)malloc(sizeof(PERSON) * 1);
    person_arraylen = 1;
    strcpy(person_Collection[0].firstname, "GROUP");
    strcpy(person_Collection[0].famnamne, "FOUR");
    strcpy(person_Collection[0].pers_number, "199508300499");
}

// return number of records in cd db file

int number_of_records_in_db() {
    FILE *f;
    int endpos;
    int numrecs = 0;

    f = fopen(filename, "rb");
    if (f == 0) {
        printf( "Cannot open file: %s\n", filename);
    } else {
        fseek(f , 0 , SEEK_END);					// seek to end of file
        endpos = ftell(f);							// get the current position (now at the end of the file)
        numrecs = endpos / sizeof(PERSON);				// calculate number of records in file
        fclose(f);
    }
    return numrecs;
}


// set all fields of global cd record to "" or 0
static void init_tempPerson() {
    strcpy(temp.firstname, "");
    strcpy(temp.famnamne, "");
    strcpy(temp.pers_number, "");
}

//change it to PERSON input_record( void);

static void read_data() {
    char pname[20];
    char fname[20];
    char personN[13];
    int slen = 0;

    init_tempPerson();
    // keep prompting until some data is entered (don't allow just a carriage-return)
    // EXERCISE: 	Try rewriting using do..while loops. Think if you need to init slen to 0
    //				before each loop (as I have done below) if you use do..while?
    while( slen == 0 ) {
        printf("ENTER FIRST NAME \n");
        slen = readln(pname);
        printf("FIRST NAME is %s \n", pname);

    };
    slen = 0;
    while( slen == 0 ) {
        printf("ENTER FAMILY NAME \n");
        slen = readln(fname);
        printf("FAMILY NAME is %s \n", fname);
    };
    slen = 0;
    while( slen == 0 ) {
        printf("ENTER PERSONAL NUMBER (yyyyxxddpppp): \n");
        slen = readln(personN);
        printf("PERSONAL NUMBER is %s \n", personN);

    };

    // finally init temp
    strcpy(temp.firstname, pname);
    strcpy(temp.famnamne, fname);
    strcpy(temp.pers_number, personN);
}


void add_person() {
    FILE *f;
    read_data();
    f = fopen(filename, "ab");								// open file in append mode
    if (f == 0) {
        printf( "Cannot write to file: %s\n", filename);
    } else {
        fwrite(&temp, sizeof(PERSON), 1, f);					// write data saved in temp at end of file
        fclose(f);
    }
}


// load cd db into cd_collection array in memory
static int load_collection() {
    FILE *f;
    int numrecs;
    int numrecsread = 0;

    numrecs = number_of_records_in_db(filename);
    f = fopen(filename, "rb");
    if (f == 0) {
        printf( "Cannot read file: %s\n", filename);
    } else {
        person_Collection = realloc(person_Collection, sizeof(PERSON) * numrecs);		// alloc some memory
        numrecsread = fread(person_Collection, sizeof(PERSON), numrecs, f);			// read all recs into memory
        if (numrecsread != numrecs) {
            printf("Error: %d records in file but %d were read into memory", numrecs, numrecsread);
        }
        fclose(f);
    }
    person_arraylen = numrecsread; // used when saving: I need to know the number of records to be saved
    return numrecsread;
}

// load and show CD collection on screen

void display_collection() {
    int i;
    int numrecs;
    PERSON thisperson;

    numrecs = load_collection(filename);
    for (i = 0; i < numrecs; i++) {
        thisperson = person_Collection[i];
        printf("%d PERSON #%d: Name: '%s' Last Name: %s personal number %s\n", sizeof(PERSON), i, thisperson.firstname, thisperson.famnamne, thisperson.pers_number);
    }
}


void deleteFile(){
    int status;
    status = remove(filename);

    if( status == 0 )
        printf("%s file deleted successfully.\n",filename);
    else
    {
        printf("Unable to delete the file\n");
        perror("Error");
    }
}


void searchPersonName(char *name){
    int i =0;
    int numrecs;
    char *ptrtostr;

    PERSON thisperson;

    numrecs = load_collection(filename);

    for (i = 0; i < numrecs; i++) {
        thisperson = person_Collection[i];
        ptrtostr = strstr(person_Collection[i].firstname, name);
        if(ptrtostr != NULL) {
            printf("Name: '%s' Collection at %d \n", thisperson.firstname, i);
        }
    }
}


void searchPersonLastName(char *name){
    int i =0;
    int numrecs;
    char *ptrtostr;

    PERSON thisperson;

    numrecs = load_collection(filename);

    for (i = 0; i < numrecs; i++) {
        thisperson = person_Collection[i];
        ptrtostr = strstr(person_Collection[i].famnamne, name);
        if(ptrtostr != NULL) {
            printf("Name: '%s' Collection at %d \n", thisperson.famnamne, i);
        }
    }
}

void choose_SEARCH(enum CHOICE command) {
    switch (command) {
        case ONE:
            printf("Search Name \n");
            //create method delete binary/clear
            char userInput[MAX];
            char *userPointer = userInput;
            readInput(userPointer);
            //printf("%s\n", userPointer);
            searchPersonName(userInput);
            break;
        case TWO:
            printf("TWO \n");
            char userInputLast[MAX];
            char *userPointer2 = userInputLast;
            readInput(userPointer2);
            searchPersonLastName(userInputLast);
            break;
        default:
            printf("INPUT ERROR \n");
            break;
    }
}


void choose_Command(enum CHOICE command){
    switch( command ) {
        case ONE:
            printf("ONE \n");
            //create method delete binary/clear
            deleteFile(filename);
            add_person(filename);
            break;
        case TWO:
            printf("TWO \n");
            // create object here??
            add_person(filename); //missing creating the index collection
            break;
        case THREE:
            printf("THREE \n");
            printf("Press one to search Name \n");
            printf("Press two to search Family Name \n");
            enum CHOICE userchoice;
            char userInput[MAX];
            char *userPointer = userInput;
            readInput(userPointer);
            userchoice = atoi(userInput);
            choose_SEARCH(userchoice);

            break;
        case FOUR:
            printf("FOUR \n");
            display_collection(filename);
            break;
        case FIVE:
            printf("FIVE \n");
            exit(0);
            break;

        default:
            printf("INPUT ERROR \n");
            exit(0);
            break;
    }
}

int main(int argc, char **argv) {
    enum CHOICE userchoice;
    char userInput[MAX];
    char *userPointer = userInput;

    create_cdcollection();
    while (userchoice != '<') {
        printf("1 Create a new and delete the old file. \n");
        printf("2 Add a new person to the file. \n");
        printf("3 Search for a person in the file . \n");
        printf("4 Print out all in the file. \n");
        printf("5 Exit the program. \n");

        readInput(userPointer);
        userchoice = atoi(userInput);

        choose_Command(userchoice);

    }

    return(0);
}