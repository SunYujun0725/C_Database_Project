#include "final.h"
#include "my-buffered-gettoken.h"

int isStudentValid( struct student*, struct WHERE_CLAUSE*);
void printStudent( struct student*, struct COLUMN_LIST*);

struct SQL sql;

void ReadNProcessSQL()
{
    char tmp[1000];

    // read and store the current SQL command

    while(1)
    {
        getNextToken(tmp);

        if( !strcmp(tmp, ";") )
            break;

        else if( !strcmp(tmp, "SELECT") )
        {
            sql.type = SQL_TYPE_SELECT;

            // read column list
        }

        else if( !strcmp(tmp, "DELETE") )
        {
            sql.type = SQL_TYPE_DELETE;
        }

        else if( !strcmp(tmp, "FROM") )
        {
            getNextToken(tmp);
        }

        else if( !strcmp(tmp, "WHERE") )
        {
            // read where clause

        }

        else if( !strcmp(tmp, "ORDER") )
        {
            getNextToken(tmp); // get "BY"

            // read the content of order by
        }
    }

    // process the SQL command

    if( sql.type == SQL_TYPE_SELECT )
    {
        for(int i=0;i<num_students;i++)
            if( isStudentValid(&tableA[i], &sql.where_clause) )
                printStudent(&tableA[i], &sql.col_list);
    }
    else
    {
        // execute DELETE command
    }
}

//

int isStudentValid( struct student *data,
                    struct WHERE_CLAUSE *where)
{
}

void printStudent( struct student *data,
                   struct COLUMN_LIST *col_list )
{
}
