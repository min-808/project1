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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file defines a struct called record, which includes the
//   account number, name, address, and next variables.
//
*******************************************************************/

struct record
{
    int                accountno;
    char               name[25];
    char               address[45];
    struct record*     next;
};
