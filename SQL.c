#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define COLUMN_ID           0
#define COLUMN_NAME         1
#define COLUMN_STUDENTID    2
#define COLUMN_CLASS        3
#define COLUMN_EMAIL        4
#define COLUMN_PHONE        5
#define COLUMN_MAX          6

const char *column_str[] =  {"ID", "Name", "StudentID", "Class", "Email", "Phone"};

typedef struct Record {
    int id;
    char name[20 + 1];
    int studentid;
    char classroom[1 + 1];
    char email[40 + 1];
    int phone;
    int metadata;
    int deleted;
} record;

int get_next_token(char *buffer, int index, char *token)
{
    int i = 0;
    int ret = 0;
    int start = index;
    int end = index;
    int length = strlen(buffer);

    for (; end<length; end++) {
        if (buffer[end] == ' ')
            break;
    }
    if (buffer[end] != ' ')
        ret = -1;
    for (i=0; i<(end-start); i++)
        token[i] = buffer[start+i];
    token[i] = 0;

    if (ret == 0)
        return end + 1;
    return ret;
}

int get_select_column(char *buffer, int index, int *column_number, int *column_order)
{
    int finish_column = 0;
    char token[1000 + 1];
    *column_number = 0;

    while (1) {
        index = get_next_token(buffer, index, token);

        if (strcmp(token, "FROM") == 0) {
            finish_column = 1;
            continue;
        }

        // table name
        if (finish_column == 1)
            break;

        if (finish_column == 0) {
            if (strcmp(token, "*") == 0) {
                for (int j=0; j<COLUMN_MAX; j++) {
                    column_order[(*column_number)] = j;
                    (*column_number) += 1;
                }
                continue;
            }
            if (token[strlen(token)-1] == ',')
                token[strlen(token)-1] = 0;
            for (int j=0; j<COLUMN_MAX; j++) {
                if (strcmp(token, column_str[j]) == 0) {
                    column_order[(*column_number)] = j;
                    (*column_number) += 1;
                }
            }
        }
    }

    return index;
}

void print_database(record *database, int num_record, int column_number, int *column_order, int metadata, int op_and)
{
    for (int i=0; i<num_record; i++) {
        int j=0;
        if (database[i].deleted > 0)
            continue;
        if (metadata >= 0) {
            if (op_and) {
                if (database[i].metadata != metadata)
                    continue;
            } else {
                if (database[i].metadata < 0)
                    continue;
            }
        }
        for (j=0; j<column_number; j++) {
            switch (column_order[j]) {
            case COLUMN_ID:
                printf("%d", database[i].id);
                break;
            case COLUMN_NAME:
                printf("%s", database[i].name);
                break;
            case COLUMN_STUDENTID:
                printf("%d", database[i].studentid);
                break;
            case COLUMN_CLASS:
                printf("%s", database[i].classroom);
                break;
            case COLUMN_EMAIL:
                printf("%s", database[i].email);
                break;
            case COLUMN_PHONE:
                printf("%d", database[i].phone);
                break;
            }

            if (j != (column_number-1))
                printf(" ");
        }
        printf("\n");
    }
}

int get_column_index(char *token)
{
    int index = -1;

    for (int j=0; j<COLUMN_MAX; j++) {
        if (strcmp(token, column_str[j]) == 0) {
            index = j;
            break;
        }
    }
    return index;
}

void update_metadata(record *database)
{
    if (database->metadata < 0)
        database->metadata = 1;
    else
        database->metadata += 1;
}

void reset_metadata(record *database, int num_record)
{
    for (int i=0; i<num_record; i++)
        database[i].metadata = -1;
}

void delete_database_all(record *database, int num_record)
{
    for (int i=0; i<num_record; i++)
        database[i].deleted = 1;
}

void delete_database_by_metadata(record *database, int num_record, int metadata, int op_and)
{
    for (int i=0; i<num_record; i++) {
        if (op_and) {
            if (database[i].metadata == metadata)
                database[i].deleted = 1;
        } else {
            if (database[i].metadata >= 0)
                database[i].deleted = 1;
        }
    }
}

int is_tail_string(char *buffer, char *tail)
{
    int is_tail = 0;
    int buffer_length = strlen(buffer);
    int tail_length = strlen(tail);
    int counter = 0;

    while ((counter < buffer_length) && (counter < tail_length)) {
        if (buffer[buffer_length - counter - 1] != tail[tail_length - counter - 1])
            break;
        counter++;
    }

    if (counter == tail_length)
        is_tail = 1;

    return is_tail;
}

int modify_database_by_like(record *database, int num_record, int target_column, char *element)
{
    char left[1000 + 1], right[1000 + 1];

    for (int i=0; i<num_record; i++) {
        if (database[i].deleted > 0)
            continue;
        switch (target_column) {
        case COLUMN_NAME:
            strcpy(left, database[i].name);
            break;
        case COLUMN_CLASS:
            strcpy(left, database[i].classroom);
            break;
        case COLUMN_EMAIL:
            strcpy(left, database[i].email);
            break;
        default:
            return -1;
        }

        // remove ""
        strcpy(right, element+1);
        right[strlen(right) - 1] = 0;
        if ((right[0] == '%') && (right[strlen(right) - 1] == '%')) {
            right[strlen(right) - 1] = 0;
            // single % without other characters
            if (strlen(right) == 0) {
                update_metadata(&database[i]);
                continue;
            }
            int length = strlen(right+1);
            // double % without other characters
            if (length == 0) {
                update_metadata(&database[i]);
                continue;
            }
            char *target = strstr(left, right+1);
            if (target)
                update_metadata(&database[i]);
        } else if (right[0] == '%') {
            if (is_tail_string(left, right+1))
                update_metadata(&database[i]);
        } else if (right[strlen(right) - 1] == '%') {
            right[strlen(right) - 1] = 0;
            char *target = strstr(left, right);
            if (target == left)
                update_metadata(&database[i]);
        } else {
            if (strcmp(left, right) == 0)
                update_metadata(&database[i]);
        }
    }

    return 0;
}

int get_value(record *database, int target_column, int *number, char **string)
{
    int is_number = 0;

    switch (target_column) {
    case COLUMN_ID:
        *number = database->id;
        is_number = 1;
        break;
    case COLUMN_NAME:
        *string = database->name;
        break;
    case COLUMN_STUDENTID:
        *number = database->studentid;
        is_number = 1;
        break;
    case COLUMN_CLASS:
        *string = database->classroom;
        break;
    case COLUMN_EMAIL:
        *string = database->email;
        break;
    case COLUMN_PHONE:
        *number = database->phone;
        is_number = 1;
        break;
    }

    return is_number;
}

int compare_number_value(int target_number, int compare_number, int order)
{
    int need_swap = 0;

    if (order) {
        if (compare_number < target_number)
            need_swap = 1;
    } else {
        if (compare_number > target_number)
            need_swap = 1;
    }

    return need_swap;
}

int compare_string_value(char *target_string, char *compare_string, int order)
{
    int need_swap = 0;

    if (order) {
        if (strcmp(compare_string, target_string) < 0)
            need_swap = 1;
    } else {
        if (strcmp(compare_string, target_string) > 0)
            need_swap = 1;
    }

    return need_swap;
}

void arrange_database(record *database, record *database_ori, int num_record, int target_column, int order)
{
    memcpy(database, database_ori, sizeof(record)*num_record);
    record *target = NULL;
    record *compare = NULL;
    record temp;
    int target_number = 0;
    int compare_number = 0;
    char *target_string = NULL;
    char *compare_string = NULL;
    int is_number = 0;

    for (int i=0; i<num_record; i++) {
        target = database + i;
        is_number = get_value(target, target_column, &target_number, &target_string);
        for (int j=i+1; j<num_record; j++) {
            compare = database + j;
            get_value(compare, target_column, &compare_number, &compare_string);
            if (is_number) {
                if (compare_number_value(target_number, compare_number, order)) {
                    memcpy(&temp, target, sizeof(record));
                    memcpy(target, compare, sizeof(record));
                    memcpy(compare, &temp, sizeof(record));
                    // update new target number
                    get_value(target, target_column, &target_number, &target_string);
                }
            } else {
                if (compare_string_value(target_string, compare_string, order)) {
                    memcpy(&temp, target, sizeof(record));
                    memcpy(target, compare, sizeof(record));
                    memcpy(compare, &temp, sizeof(record));
                    // update new target number
                    get_value(target, target_column, &target_number, &target_string);
                }
            }
        }
    }
}

int modify_database(record *database, int num_record, int target_column, char *compare, char *element)
{
    int left = 0, right = 0;
    char left_string[1000 + 1], right_string[1000 + 1];
    int is_number = 0;

    for (int i=0; i<num_record; i++) {
        if (database[i].deleted > 0)
            continue;
        switch (target_column) {
        case COLUMN_ID:
            left = database[i].id;
            is_number = 1;
            break;
        case COLUMN_STUDENTID:
            left = database[i].studentid;
            is_number = 1;
            break;
        case COLUMN_PHONE:
            left = database[i].phone;
            is_number = 1;
            break;
        case COLUMN_NAME:
            strcpy(left_string, database[i].name);
            is_number = 0;
            break;
        case COLUMN_CLASS:
            strcpy(left_string, database[i].classroom);
            is_number = 0;
            break;
        case COLUMN_EMAIL:
            strcpy(left_string, database[i].email);
            is_number = 0;
            break;
        default:
            return -1;
        }

        if (is_number) {
            right = strtol(element, NULL, 0);
            if (strcmp(compare, ">=") == 0) {
                if (left >= right)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, ">") == 0) {
                if (left > right)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "<=") == 0) {
                if (left <= right)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "<") == 0) {
                if (left < right)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "=") == 0) {
                if (left == right)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "!=") == 0) {
                if (left != right)
                    update_metadata(&database[i]);
            } else {
                return -1;
            }
        } else {
            // remove ""
            strcpy(right_string, element+1);
            right_string[strlen(right_string) - 1] = 0;
            if (strcmp(compare, ">=") == 0) {
                if (strcmp(left_string, right_string) >= 0)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, ">") == 0) {
                if (strcmp(left_string, right_string) > 0)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "<=") == 0) {
                if (strcmp(left_string, right_string) <= 0)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "<") == 0) {
                if (strcmp(left_string, right_string) < 0)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "=") == 0) {
                if (strcmp(left_string, right_string) == 0)
                    update_metadata(&database[i]);
            } else if (strcmp(compare, "!=") == 0) {
                if (strcmp(left_string, right_string) != 0)
                    update_metadata(&database[i]);
            } else {
                return -1;
            }
        }
    }

    return 0;
}

int main(void) {
    int num_record, num_instruction;
    scanf("%d %d\n", &num_record, &num_instruction);
    record database[num_record];
    record database_mod[num_record];
    record database_order[num_record];
    memset(&database[0], -1, sizeof(database));
    memset(&database_order[0], -1, sizeof(database_order));

    record input;
    for (int i=0; i<num_record; i++) {
        scanf("%d %s %d %s %s %d\n", &input.id, input.name, &input.studentid, input.classroom, input.email, &input.phone);
        database[i].id = input.id;
        strcpy(database[i].name, input.name);
        database[i].studentid = input.studentid;
        strcpy(database[i].classroom, input.classroom);
        strcpy(database[i].email, input.email);
        database[i].phone = input.phone;
    }

    char command[num_instruction][1000 + 1];
    char token[1000 + 1];
    memset(&command[0][0], 0, num_instruction*(1000 + 1));
    for (int i=0; i<num_instruction; i++) {
        fgets(command[i], 1000, stdin);
        command[i][strlen(command[i]) - 2] = 0;
    }

    memcpy(&database_mod[0], &database[0], sizeof(database));
    for (int i=0; i<num_instruction; i++) {
        int ret;
        int print_all = 0;
        int index = 0;
        int op_and = 0;
        int show_order = 0;
        int op_counter = 0;
        int target_column;
        int column_number = 0;
        int column_order[COLUMN_MAX];
        char compare[1000 + 1];
        char element[1000 + 1];

        reset_metadata(database_mod, num_record);
        index = get_next_token(command[i], index, token);

        if (strcmp(token, "SELECT") == 0) {
            index = get_select_column(command[i], index, &column_number, column_order);
            if (index < 0) {
                print_database(database_mod, num_record, column_number, column_order, -1, op_and);
                continue;
            }
            // Where
            index = get_next_token(command[i], index, token);
            // very ugly method, modify later...
            if (strcmp(token, "ORDER") == 0) {
                print_all = 1;
                goto parse_order;
            }

            do {
                op_counter++;
                // Column
                index = get_next_token(command[i], index, token);
                target_column = get_column_index(token);
                // Compare
                index = get_next_token(command[i], index, compare);
                // Element
                index = get_next_token(command[i], index, element);

                if (strcmp(compare, "LIKE") == 0)
                    ret = modify_database_by_like(database_mod, num_record, target_column, element);
                else
                    ret = modify_database(database_mod, num_record, target_column, compare, element);
                if (ret || (index < 0))
                    break;
                index = get_next_token(command[i], index, token);
                if (strcmp(token, "AND") == 0) {
                    op_and = 1;
                } else if (strcmp(token, "OR") == 0) {
                    op_and = 0;
                } else if (strcmp(token, "ORDER") == 0) {
                    int order;
parse_order:
                    // BY
                    index = get_next_token(command[i], index, token);
                    // Column
                    index = get_next_token(command[i], index, token);
                    target_column = get_column_index(token);
                    // DESC
                    index = get_next_token(command[i], index, token);
                    if (strcmp(token, "DESC") == 0)
                        order = 0;
                    else
                        order = 1;
                    arrange_database(database_order, database_mod, num_record, target_column, order);
                    show_order = 1;
                    ret = 0;
                    break;
                }
            } while (1);
            if (ret == 0) {
                if (print_all)
                    op_counter = -1;
                if (show_order)
                    print_database(database_order, num_record, column_number, column_order, op_counter, op_and);
                else
                    print_database(database_mod, num_record, column_number, column_order, op_counter, op_and);
            }
        } else if (strcmp(token, "DELETE") == 0) {
            // FROM table WHERE
            index = get_next_token(command[i], index, token);
            index = get_next_token(command[i], index, token);
            if (index < 0) {
                delete_database_all(database_mod, num_record);
                continue;
            }
            index = get_next_token(command[i], index, token);

            do {
                op_counter++;
                // Column
                index = get_next_token(command[i], index, token);
                target_column = get_column_index(token);
                // Compare
                index = get_next_token(command[i], index, compare);
                // Element
                index = get_next_token(command[i], index, element);

                if (strcmp(compare, "LIKE") == 0)
                    ret = modify_database_by_like(database_mod, num_record, target_column, element);
                else
                    ret = modify_database(database_mod, num_record, target_column, compare, element);
                if (ret || (index < 0))
                    break;
                index = get_next_token(command[i], index, token);
                if (strcmp(token, "AND") == 0) {
                    op_and = 1;
                } else if (strcmp(token, "OR") == 0) {
                    op_and = 0;
                }
            } while (1);
            delete_database_by_metadata(database_mod, num_record, op_counter, op_and);
        }
    }

    system("pause");

    return 0;
}
