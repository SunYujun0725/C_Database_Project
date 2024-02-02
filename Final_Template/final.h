#include "sql.h"

#ifndef FINAL_H_INCLUDED
#define FINAL_H_INCLUDED

struct student {
    int ID;
    char Name[21];
    int StudentID;
    char Class;
    char Email[41];
    int Phone;
};

extern struct student tableA[300];
extern int num_students;

#endif // FINAL_H_INCLUDED
