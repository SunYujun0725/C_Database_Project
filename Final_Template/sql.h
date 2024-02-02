
#ifndef SQL_H_INCLUDED
#define SQL_H_INCLUDED

struct condition
{
    char column[20];    // column
    char optr[5];    // optr
    char value[100];    // value
};

struct COLUMN_LIST
{
    int length_of_cols;
    char cols[100][15];
};

struct WHERE_CLAUSE
{
    int num_of_conditions;
    struct condition conditions[1000];
    int type_of_connector;  // 0 for AND;  1 for OR
};

#define SQL_TYPE_SELECT 0
#define SQL_TYPE_DELETE 1

struct SQL
{
    int type;   // 0 for SELECT;  1 for DELETE;

    // column list
    struct COLUMN_LIST col_list;

    // where clause
    struct WHERE_CLAUSE where_clause;

    // order by
    int flag_order_by;
    char order_by_col[15];
    int flag_inc;   // 1 for ASC;  0 for DES
};

#endif // SQL_H_INCLUDED
