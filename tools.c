#include "header.h"

int count_2d(char **str)
{
    int i = 0;
    while(str[i])
        i++;
    return (i);
}
char** copy_env(char **env)
{
    int i;
    i = 0;
    char **copy;
    int x = count_2d(env);
    copy = malloc(sizeof(char*) * (x + 1));
    while(env[i])
    {
        copy[i] = ft_strdup(env[i]);
        i++;
    }
    copy[i] = 0;
    return (copy);
}

char *search_in_env(char *c, t_lexer *lexer)
{
    int i = 0;
    while(lexer->env[i])
    {
        if (!ft_strncmp(lexer->env[i], c, ft_strlen(c)))
        {
            free(c);
            return (ft_substr(lexer->env[i], ft_strlen(c), ft_strlen(lexer->env[i]) - ft_strlen(c)));
        }
        i++;
    }
    return (NULL);
}

char    *dollar_handler(t_lexer *lexer)
{
    char *s = ft_strdup("");
    char *c = ft_strdup("");
    if (lexer->c == '$')
        lexer_advance(lexer);
    if (lexer->c != '_' && !ft_isalnum(lexer->c))
    {
        s = ft_strjoin(s, "$");
        free(c);
        return (s);
    }
    while(lexer->c)
    {
        if (lexer->c != '_' && !ft_isalnum(lexer->c))
            break ;
        else
            {
                c = get_current_char_as_string(lexer);
                s = ft_strjoin(s, c);
                free(c);
                lexer_advance(lexer);
            }
    }
    s = ft_strjoin(s, "=");
    s = search_in_env(s, lexer);
    if (s == NULL)
        s = ft_strdup("");
    return(s);
}