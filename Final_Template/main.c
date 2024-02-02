
#include <stdio.h>
#include "final.h"

struct student tableA[300];
int num_students;

int main()
{
    int i,j,k;
    int m;

    // read input
    scanf("%d%d", &num_students, &m);
    for(int i=0;i<num_students;i++)
        scanf("%d%s %c %s%d", &tableA[i].ID,
                              &tableA[i].Name,
                              &tableA[i].StudentID,
                              &tableA[i].Class,
                              &tableA[i].Email,
                              &tableA[i].Phone);

    // read & process SQL
    while(m--)
    {
        ReadNProcessSQL();
    }

    return 0;
}
