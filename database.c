/*****************************************************************
//
//  NAME:        Min
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Name
//
//  DATE:        March 22, 2024
//
//  FILE:        database.c
//  
//   DESCRIPTION:
//    This file includes the functions called by the user interface:
//    addRecord, printAllRecords, findRecord, and deleteRecord. Additionally,
//    it includes writefile, readfile, and cleanup, which are functions
//    used to save, read, and restore the heap. These aren't included
//    in the list of available commands. 
//
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

extern int debugMode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   The addRecord function adds a record to the database.
//
//  Parameters:    storagePointer (struct record**) : A pointer of a pointer that points
//                                                    to the start of the linked list
//                 accountNum (int) : The account number to associate
//                                    the record with
//                 c1 (char[]) : The character array storing the name
//                 c2 (char[]) : The character array storing the house address
//  
//  Return values:  0 : Success
//                 -1 : Fail
//
*******************************************************************/

int addRecord(struct record ** storagePointer, int accountNum, char c1[], char c2[])
{
    struct record* temp;
    struct record* current = *storagePointer;
    struct record* start = *storagePointer;
    struct record* prev = NULL;
    int retval = -1;

    if (debugMode == 1)
    {
        printf("\nCalling the addRecord function with:\n");
        printf("accountNum: %d\n", accountNum);
        printf("name: %s\n", c1);
        printf("address: %s\n", c2);
    }

    if (start == NULL)
    {
        start = (struct record*) malloc(sizeof(struct record));
        start -> accountno = accountNum;
        strcpy(start -> address, c2);
        strcpy(start -> name, c1);
        start -> next = NULL;
        *storagePointer = start; /* Set the start to the new record */
        retval = 0;
    }
    else if (accountNum < current -> accountno) /* Adding in the front */
    {
        temp = (struct record*) malloc(sizeof(struct record));
        temp -> next = current;
        temp -> accountno = accountNum;
        strcpy(temp -> address, c2);
        strcpy(temp -> name, c1);
        *storagePointer = temp;
        retval = 0;
    }
    else if ((current != NULL) && (current -> accountno < accountNum)) /* Adding to the end */
    {
        while ((current != NULL) && (current -> accountno < accountNum)) /* Find where to insert */
        {
            prev = current;
            current = current -> next;
        }
        if (current == NULL) /* Check if the end is a duplicate before adding */
        {
            if (prev -> accountno == accountNum)
            {
                retval = -1;
            }
            else /* You're good the end isn't a duplicate, add as normal */
            {
                temp = (struct record*) malloc(sizeof(struct record));
                temp -> next = current;
                prev -> next = temp;
                temp -> accountno = accountNum;
                strcpy(temp -> address, c2);
                strcpy(temp -> name, c1);
                retval = 0;
            }
        }
        else if (current != NULL) /* Means we're in the middle */
        {
            if (current -> accountno == accountNum)
            {
                retval = -1;
            }
            else
            {
                temp = (struct record*) malloc(sizeof(struct record));
                temp -> next = current;
                prev -> next = temp;
                temp -> accountno = accountNum;
                strcpy(temp -> address, c2);
                strcpy(temp -> name, c1);
                retval = 0;
            }
        }
    }
    else if ((current != NULL) && (current -> accountno == accountNum))
    {
        retval = -1;
    }
    return retval;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   The printAllRecords function prints all the records
//                 currently present in the database.
//
//  Parameters:    storage (struct record*) : A pointer to the start of
//                                            the linked list
//  
//  Return values:  None
//
*******************************************************************/

void printAllRecords(struct record * storage)
{
    struct record* current = storage;

    if (debugMode == 1)
    {
        printf("\nCalling the printAllRecords function\n");
    }

    if (storage == NULL)
    {
        printf("\nNo records found\n\n");
    }
    else
    {
        printf("\nRecords:\n\n");
    }

    while (current != NULL)
    {
        printf("Account Number: %d\n", current -> accountno);
        printf("Name: %s\n", current -> name);
        printf("Address: %s\n\n", current -> address);
        current = current -> next;
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   The findRecord function looks for a record
//                 in the database given an account number.
//
//  Parameters:    storage (struct record*) : A pointer to the start of
//                                            the linked list
//                 accountNum (int) : The account number to look for
//  
//  Return values:  0 : Success
//                 -1 : Not found
//
*******************************************************************/

int findRecord(struct record * storage, int accountNum)
{
    struct record* current = storage;
    int retval = -1;

    if (debugMode == 1)
    {
        printf("Calling the findRecord function with:\n\n");
        printf("accountNum: %d\n", accountNum);
    }

    while (current != NULL)
    {
        if (current -> accountno == accountNum)
        {
            retval = 0;
            printf("\nAccount found:\n\n");
            printf("Account Number: %d\n", current -> accountno);
            printf("Name: %s\n", current -> name);
            printf("Address: %s\n\n", current -> address);
            current = current -> next;
        }
        else
        {
            current = current -> next;
        }
    }

    return retval;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   The deleteRecord function deletes a record in the
//                 database given an account number.
//
//  Parameters:    storagePointer (struct record**) : A pointer of a pointer that points
//                                                    to the start of the linked list
//                 accountNum (int) : The account number to delete
//  
//  Return values:  0 : Success
//                 -1 : Not found
//
*******************************************************************/

int deleteRecord(struct record ** storagePointer, int accountNum)
{
    struct record* current = *storagePointer;
    struct record* start = *storagePointer;
    struct record* prev = NULL;
    struct record* next = NULL;
    int retval = -1;
    int check = 0;

    if (debugMode == 1)
    {
        printf("Calling the deleteRecord function with: \n\n");
        printf("accountNum: %d\n\n", accountNum);
    }

    if (start != NULL)
    {
        while ((current != NULL) && (check == 0))
        {
            if (current -> accountno == accountNum)
            {
                if (prev == NULL) /* Start of list */
                {
                    if (current -> next == NULL) /* Only item */
                    {
                        free(current);
                        retval = 0;
                        current = NULL;
                        *storagePointer = NULL;
                    }
                    else /* Deleting first item, multiple items */
                    {
                        start = current -> next;
                        *storagePointer = start;
                        free(current);
                        current = start;
                        retval = 0;
                    }
                }
                else if (next == NULL) /* End of list */
                {
                    prev -> next = NULL;
                    free(current);
                    retval = 0;
                    current = NULL;
                }
                else /* Middle of list */
                {
                    free(current);
                    prev -> next = next;
                    retval = 0;
                    current = start;
                }
            }
            else if ((current -> accountno < accountNum) && (current -> next != NULL)) /* Less */
            {
                prev = current;
                current = current -> next;
                next = current -> next;
            }
            else if ((current -> accountno < accountNum) && (current -> next == NULL)) /* End */
            {
                check = -1;
            }
            else if (current -> accountno > accountNum)
            {
                check = -1;
            }
        }
    }
    return retval;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   The writefile function takes the existing linked list
//                 and writes its contents to a text file.
//
//  Parameters:    start (struct record*) : A pointer to the start of
//                                          the linked list
//                 filename (char[]) : The name of the file you're
//                                     writing to
//  
//  Return values:  0 : Success
//                 -1 : Write failure
//
*******************************************************************/

int writefile(struct record * start, char filename[])
{
    FILE* outfile;
    int retval = 0;
    struct record* current = start;

    if (debugMode == 1)
    {
        printf("Calling the writefile function with: \n\n");
        printf("filename: %s\n\n", filename);
    }

    if ((outfile = fopen(filename, "w")) == NULL)
    {
        retval = -1;
    }
    else
    {
        while (current != NULL)
        {
            fprintf(outfile, "%d\n%s\n%s*\n", current -> accountno, current -> name, current -> address);
            current = current -> next;
        }

        fclose(outfile);
    }

    return retval;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   The readfile function takes a text file in the correct
//                 format and creates a linked list with all the fields populated.
//
//  Parameters:    start (struct record*) : A pointer to the start of
//                                          the linked list
//                 filename (char[]) : The name of the file you're
//                                     writing to
//  
//  Return values:  0 : Success
//                 -1 : Read failure
//
*******************************************************************/

int readfile(struct record ** start, char filename[])
{
    FILE* infile;
    int retval = 0;
    char temp[50];
    int tempNumber;
    char tempName[25];
    char tempAddress[45];

    char c;
    int incrementer = 0;

    struct record* prev = NULL;
    struct record* current = *start;

    if (debugMode == 1)
    {
        printf("Calling the readfile function with: \n\n");
        printf("filename: %s\n\n", filename);
    }

    if ((infile = fopen(filename, "r")) == NULL)
    {
        retval = -1;
    }
    else
    {
        while (fscanf(infile, "%d", &tempNumber) != EOF) /* While we're not at EOF */
        {
            current = (struct record*) malloc(sizeof(struct record));
            fgets(temp, 50, infile); /* Clear the buffer */
            fgets(tempName, 25, infile);
            tempName[strlen(tempName) - 1] = '\0'; /* To make it a string */

            while (((c = fgetc(infile)) != '*') && (incrementer < 45 - 1))
            {
                tempAddress[incrementer] = c;
                incrementer++;
            }
            tempAddress[incrementer] = '\0'; /* To make it a string */
            incrementer = 0;
            fgets(temp, 50, infile); /* Clear the buffer */

            current -> accountno = tempNumber;
            strcpy(current -> name, tempName);
            strcpy(current -> address, tempAddress);
            current -> next = NULL;

            if (*start == NULL)
            {
                *start = current;
                prev = current;
            }
            else
            {
                prev -> next = current;
                prev = current;
            }
        }

        fclose(infile);
    }

    return retval;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   The cleanup function releases all the heap space
//                 at the end of the function.
//
//  Parameters:    start (struct record*) : A pointer to the start of
//                                          the linked list
//  
//  Return values:  None
//
*******************************************************************/

void cleanup(struct record ** start)
{
    struct record* current;
    struct record* todelete = *start;

    if (debugMode == 1)
    {
        printf("\nCalling the cleanup function\n");
    }

    while (todelete != NULL)
    {
        current = todelete;
        todelete = todelete -> next;
        free(current);
    }

    *start = NULL;
}
