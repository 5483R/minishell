#include "../builtins.h"

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

void update_env_value(t_env *env, char *new_value)
{
    if (env)
    {
        if (env->value)
            free(env->value);
        env->value = new_value;
    }
}

void    cd_home(t_env *env)
{
    t_env *home;
    t_env *old_pwd;
    char *old;

    home = get_env_item_or_none("HOME", env);
    old_pwd = get_env_item_or_none("OLDPWD", env);
    old = NULL;
    if (!home)
        raise_error("HOME not set", "cd", EXIT_FAILURE, FALSE);
    else
    {
        if (old_pwd)
            old = getcwd(NULL, 0);
        if (chdir(home->value) == ERROR_RETURNED)
        {
            raise_error(NULL, "cd", EXIT_FAILURE, FALSE);
            if (old)
                free(old);
            return ;
        }
        update_env_value(old_pwd, old);
        update_env_value(get_env_item_or_none("PWD", env), getcwd(NULL, 0));
    }
}

void    cd_path(t_parse *data, t_env *env)
{
    t_env *old_pwd;
    t_env *pwd;
    char *old;

    old = NULL;
    old_pwd = get_env_item_or_none("OLDPWD", env);
    pwd = get_env_item_or_none("PWD", env);
    if (old_pwd)
        old = getcwd(NULL, 0);
    if (chdir(*data->arg) == ERROR_RETURNED)
    {
        raise_error(NULL, "cd", EXIT_FAILURE, FALSE);
        if (old)
            free(old);
        return ;
    }
    update_env_value(old_pwd, old);
    update_env_value(pwd, getcwd(NULL, 0));
}

int run_cd(t_parse *data, t_env *env)
{
    if (!is_identical(data->cmd, CD))
        return (FALSE);
    if (data->arg && data->arg[1])
        raise_error("too many arguments", "cd", EXIT_FAILURE, FALSE);
    else if (data->arg)
        cd_path(data, env);
    else if (!data->arg)
        cd_home(env);
    return (TRUE);
}

int run_pwd(t_parse *data)
{
    if (!is_identical(data->cmd, PWD))
        return (FALSE);
    printf("%s\n", getcwd(NULL, 0));
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
        i++;
    }
    return (TRUE);
}

int run_export(t_parse *data, t_env **env)
{
    t_env   *found;
    char    *key;
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
            key = extract_env_key(data->arg[i]);
            if (key)
            {
                found = get_env_item_or_none(key, data->env);
                if (!found)
                    add_env_item(env, data->arg[i]);
                else
                    update_env_item(found, data->arg[i]);
            }
            i++;
        }
    }
    return (TRUE);
}