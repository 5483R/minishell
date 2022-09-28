#ifndef TOKEN_H
#define TOKEN_H

typedef struct s_token
{
    enum
    {
        TOKEN_CMD,
        TOKEN_ARG,
        TOKEN_PIPE,
        TOKEN_HERDOC,
        TOKEN_SLRD,
        TOKEN_SRRD,
        TOKEN_DRRD,
        TOKEN_ERROR,
        TOKEN_ENV,
    } type;
    int flag_cmg;
    struct s_token *next;
    char *value;
}   t_token;

#endif