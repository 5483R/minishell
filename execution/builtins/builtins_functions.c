#include "builtins.h"

int run_echo(t_parse *data)
{
    int i;
    int n_flag_found;

    i = 0;
    n_flag_found = FALSE;
    if (!is_identical(data->cmd, ECHO))
        return (FALSE);
    while (data->arg && valid_echo_flag(data->arg[i]))
    {
        n_flag_found = TRUE;
        i++;
    }
    while(data->arg && data->arg[i])
    {
        printf("%s", data->arg[i]);
        i++;
        if (data->arg && data->arg[i])
            printf(" ");
    }
    if (!n_flag_found)
        printf("\n");
    return (TRUE);
}

int run_cd(t_parse *data, t_env **env)
{
    if (!is_identical(data->cmd, CD))
        return (FALSE);
    if (data->arg && double_ptr_len(data->arg) > 1)
        raise_error("too many arguments", "cd", EXIT_FAILURE, FALSE);
    else if (data->arg)
    {
        if (cd_back_valid_arg(*data->arg))
            if (ft_strlen(*data->arg) == 2)
                cd_home(env);
            else
                cd_back(env);
        else
            cd_path(data, env);
    }
    else if (!data->arg)
        cd_home(env);
    return (TRUE);
}

int run_pwd(t_parse *data)
{
    char *pwd;

    pwd = NULL;
    if (!is_identical(data->cmd, PWD))
        return (FALSE);
    pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free (pwd);
    return (TRUE);
}

int run_unset(t_parse *data, t_env **env)
{
    int i;

    i = 0;
    if (!is_identical(data->cmd, UNSET))
        return (FALSE);
    while (data->arg && data->arg[i])
    {
        if (env_key_valid(data->arg[i]))
            remove_env_item(data->arg[i], env);
        else
            raise_error("not a valid identifier", data->arg[i], EXIT_FAILURE, FALSE);
        i++;
    }
    return (TRUE);
}

int run_export(t_parse *data, t_env **env)
{
    int     i;

    i = 0;
    if (!is_identical(data->cmd, EXPORT))
        return (FALSE);
    if (!data->arg)
        print_sorted_env_items(*env);
    else
    {
        while (data->arg[i])
        {
            create_or_update_env_item(env, data->arg[i]);
            i++;
        }
    }
    return (TRUE);
}