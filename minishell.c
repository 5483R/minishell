#include "header.h"

void add_back(t_token **list, t_token *tmp)
{
    if (*list == NULL)
        (*list) = tmp;
    else
    {
        t_token *tmp1 = *list;
        while(tmp1->next != NULL)
            tmp1 = tmp1->next;
        tmp1->next = tmp;
    } 
}

int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;
    t_lexer  *lexer;
    t_token *token = NULL;
    t_token *tmp;
    t_parse *parse; 
    char *str;
    lexer = malloc(sizeof(t_lexer));
    lexer->env = copy_env(env);
    while(1)
    {
        str = readline("minishell >$ ");
        lexer = init_lexer(str, lexer);
        while ((tmp = get_next_token(lexer)) != NULL)
            add_back(&token, tmp);
        if ((token) != NULL)
        {
            parse = init_parsing(&token, lexer);
        }
        t_parse *tmp1 = parse;
        if (lexer->flg_error == 0)
        {
            while(tmp1)
            {
                if (tmp1->cmd != NULL)
                    printf("cmd = %s\n", tmp1->cmd);
                if (tmp1->arg != NULL)
                {
                    int i = 0;
                    while(tmp1->arg[i])
                    {
                        printf("arg = %s\n", tmp1->arg[i]);
                        i++;
                    }
                }
                if (tmp1->rdr != NULL)
                {
                    t_rdr *r = tmp1->rdr;
                    while(r)
                    {
                        printf("rdr->type = %d, rdr->value = %s\n", r->type, r->value);
                        r = r->next;
                    }
                }
                printf("-----------------------\n");
                tmp1 = tmp1->next;
            }
        }
        else
            printf("syntax_error\n");
        if (ft_strlen(str) > 0)
            add_history(str);
        tmp = token;
        while(tmp)
        {
            token = token->next;
            free(tmp);
            tmp = token;
        }
    }
return 0;
}