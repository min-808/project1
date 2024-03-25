/*****************************************************************
//
//  NAME:        Min
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  
//
//  DATE:        March 21, 2024
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file includes the main function and getAddress function.
//   The main function makes up most of the user interface, prompting
//   the user with options, and asking for inputs like account number,
//   name, and house address. The getAddress function is a helper
//   method that's used to get the house address. A debug mode is
//   also provided to give further information to the tester.
//
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"

void getAddress(char[], int);

int debugMode = 0; /* Global variable */

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main function primarily serves to provide
//                 the various options of the bank database:
//                 add, printall, find, delete, and quit. These
//                 options all call various functions declared
//                 in the header files, which communicate with the
//                 actual database. 
//
//  Parameters:    argc (int) : The number of arguments in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : Success
//
*******************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;

    char input[20];
    int inputLength;

    int quit = 0;
    int invalid = 0;
    int showIntroMessage = 1;
    char temp[50];
    int numCheck;
    int nameLength;
    int addRetVal;
    int findRetVal;
    int deleteRetVal;

    int accountNumber;
    char name[25];
    char address[45];

    if (argc == 2)
    {
        if (strcmp(argv[1], "debug") == 0)
        {
            debugMode = 1;
        }
        else
        {
            printf("Invalid command line argument(s)\n");
            showIntroMessage = 0;
            quit = 1;
        }
    }
    else if (argc >= 2)
    {
        printf("Invalid command line argument(s)\n");
        showIntroMessage = 0;
        quit = 1;
    }

    readfile(&start, "storage.txt");

    if (debugMode == 1)
    {
        printf("---------------------------\n");
        printf("**CURRENTLY IN DEBUG MODE**\n");
        printf("---------------------------\n\n");
    }

    if (showIntroMessage == 1)
    {
        printf("Welcome to the Banking System!\n");
    }

    while (quit == 0)
    {
        if (invalid == 1)
        {
            printf("\nInvalid option\n\n");
            invalid = 0;
        }

        printf("Please choose an option\n\n");
        printf("add: Add a new record in the database\n");
        printf("printall: Print all the records in the database\n");
        printf("find: Find record(s) with a specified account number\n");
        printf("delete: Delete existing record(s) from the database ");
        printf("using the account number as a key\n");
        printf("quit: Quit the program\n\n");

        fgets(input, 20, stdin);
        inputLength = strlen(input) - 1; /* This is the length without the newline */
        input[inputLength] = '\0'; /* Sets the newline at the end to a null character */

        if (inputLength == 0)
        {
            invalid = 1;
        }
        else if (strncmp(input, "add", inputLength) == 0)
        {
            printf("\nPlease enter an account number\n");
            numCheck = scanf("%d", &accountNumber);

            while ((accountNumber <= 0) || (numCheck == 0))
            {
                printf("\nYour input was invalid. Try again\n");
                fgets(temp, 50, stdin);
                numCheck = scanf("%d", &accountNumber);
            }

            fgets(temp, 50, stdin); /* Clear the buffer before asking for the name */

            printf("\nNext, enter your name\n");
            fgets(name, 25, stdin);

            nameLength = strlen(name) - 1; /* Length of name without newline */
            name[nameLength] = '\0';

            printf("\nFinally, enter your address. ");
            printf("Type the asterisk character '*' and press enter when done\n");

            getAddress(address, 45);

            fgets(temp, 50, stdin); /* Clear the buffer again */

            addRetVal = addRecord(&start, accountNumber, name, address); /* Call the function */
            if (addRetVal == -1)
            {
                printf("\nCould not add record, account number already exists\n\n");
            }
            else
            {
                printf("\nSuccessfully added record\n\n");
            }
        }
        else if (strncmp(input, "printall", inputLength) == 0)
        {
            printAllRecords(start); /* Call the function */
        }
        else if (strncmp(input, "find", inputLength) == 0)
        {
            printf("\nPlease enter an account number to search for\n");
            numCheck = scanf("%d", &accountNumber);
            printf("\n");

            while ((accountNumber <= 0) || (numCheck == 0))
            {
                printf("\nYour input was invalid. Try again\n");
                fgets(temp, 50, stdin);
                numCheck = scanf("%d", &accountNumber);
            }

            fgets(temp, 50, stdin); /* Clear the buffer */

            printf("Searching for account number %d...\n", accountNumber);
            findRetVal = findRecord(start, accountNumber); /* Call the function */

            if (findRetVal == -1)
            {
                printf("\nCould not find record with that account number\n\n");
            }
        }
        else if (strncmp(input, "delete", inputLength) == 0)
        {
            printf("\nPlease enter an account number to delete\n");
            numCheck = scanf("%d", &accountNumber);

            while ((accountNumber <= 0) || (numCheck == 0))
            {
                printf("\nYour input was invalid. Try again\n");
                fgets(temp, 50, stdin);
                numCheck = scanf("%d", &accountNumber);
            }

            fgets(temp, 50, stdin); /* Clear the buffer */

            printf("\n");
            printf("Searching for account number %d...\n", accountNumber);
            deleteRetVal = deleteRecord(&start, accountNumber); /* Call the function */

            if (deleteRetVal == -1)
            {
                printf("Could not find record with that account number\n");
            }
            else
            {
                printf("Found account, deleting...\n");
            }
            printf("\n");
        }
        else if (strncmp(input, "quit", inputLength) == 0)
        {
            writefile(start, "storage.txt");
            cleanup(&start);
            printf("\nQuitting program\n");
            quit = 1;
        }
        else
        {
            invalid = 1;
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   The getAddress function behaves by using the
//                 fgetc method in a while loop, grabbing the
//                 characters typed from the user up until they
//                 type '*' followed by a new line. This way,
//                 the array preserves the user's exact inputs.
//
//  Parameters:    toInsert (char[]) : The address of the house
//                                     address char array
//                 length (int) : The length of the array
//
//  Return values:  None
//
*******************************************************************/

void getAddress(char toInsert[], int length)
{
    char c;
    int incrementer = 0;

    if (debugMode == 1)
    {
        printf("\nCalling the getAddress function with:\n");
        printf("toInsert: %s (nothing in it yet, so garbage data)\n", toInsert);
        printf("length: %d\n\n", length);
    }

    while (((c = fgetc(stdin)) != '*') && (incrementer < length - 1))
    {
        toInsert[incrementer] = c;
        incrementer++;
    }

    toInsert[incrementer] = '\0'; /* To make it a string */
}
