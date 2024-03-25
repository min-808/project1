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
//  FILE:        database.h
//
//  DESCRIPTION:
//   This file declares the functions defined in database.c and used
//   in user_interface.c
//
*******************************************************************/

#include "record.h"

int addRecord(struct record **, int, char[], char[]);
void printAllRecords(struct record *);
int findRecord(struct record *, int);
int deleteRecord(struct record **, int);
int writefile(struct record *, char[]);
int readfile(struct record **, char[]);
void cleanup(struct record **);
