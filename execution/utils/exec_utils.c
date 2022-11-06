#include "../execution.h"

char **env_converter(t_env *env)
{
    int i;
    char **env_ptr;
    t_env *current;
    char *tmp;

    current = env;
    i = 0;
    tmp = NULL;
    env_ptr = malloc(sizeof(char *) * (env_size(env) + 1));
    if (!env_ptr)
        raise_error("Allocation Failed", "malloc", EXIT_FAILURE, TRUE);
    while (current)
    {
        tmp = ft_strjoinx(current->key, "=");
        env_ptr[i] = ft_strjoinx(tmp, current->value);
        free(tmp);
        current = current->next;
        i++;
    }
    env_ptr[i] = NULL;
    return (env_ptr);
}