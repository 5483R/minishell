#include "builtins.h"

int run_env(t_parse *data, t_env **env)
{
    t_env *current;

    current = *env;
    if (!is_identical(data->cmd, ENV))
        return (FALSE);
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return (TRUE);
}

int is_valid_arg(char *arg)
{
    int i;

    i = 0;
    if (arg[0] == '-')
        i++;
    while (arg && arg[i])
    {
        if (!ft_isdigit(arg[i]))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int run_exit(t_parse *data)
{
    int args_len;

    args_len = double_ptr_len(data->arg);
    if (!is_identical(data->cmd, EXIT))
        return (FALSE);
    printf("exit\n");
    if (args_len <= 1)
    {
        if (args_len == 1 && is_valid_arg(*data->arg))
            g_exitm = ft_atoi(*data->arg) % 256;    
        else if (args_len == 1)
            raise_error("numeric argument required", *data->arg, 255, FALSE);
        exit(g_exitm);
    }
    else
    {
        if (is_valid_arg(data->arg[0]))
            raise_error("too many arguments", "exit", EXIT_FAILURE, FALSE);
        else
            raise_error("numeric argument required", *data->arg, 255, TRUE);
    }
    return (TRUE);
}