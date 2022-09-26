#include "header.h"
t_token *init_token(int type, char *value)
{
	t_token *token = (t_token *)malloc(sizeof(t_token));
	token->value = malloc(sizeof(char) * (ft_strlen(value) + 1));
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}