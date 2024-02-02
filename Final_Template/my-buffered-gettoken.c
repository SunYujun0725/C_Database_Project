#include <string.h>
#include "my-buffered-gettoken.h"

char _token_buffer[1000];
int is_token_buffer_filled = 0;

// Read a token, store it in the buffer, and
// set the buffer flag
void getToken()
{
}

char *getNextToken( char *t )
{
    peekNextToken(t);
    is_token_buffer_filled = 0;
    return t;
}

char *peekNextToken( char *t )
{
    if( !is_token_buffer_filled )
        getToken();

    strcpy(t,_token_buffer);
    return t;
}
