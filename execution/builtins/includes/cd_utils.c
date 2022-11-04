#include "../builtins.h"

void update_env_value(t_env *env, char *new_value)
{
    if (env)
    {
        if (env->value)
        {
            if (new_value)
                free(env->value);
        }
        if (new_value)
            env->value = new_value;
    }
}

void    cd_path(t_parse *data, t_env **env)
{
    t_env *old_pwd;
    t_env *pwd;
    char *old;
    int i;

    i = 0;
    old = NULL;
    old_pwd = get_env_item_or_none("OLDPWD", *env);
    pwd = get_env_item_or_none("PWD", *env);
    old = getcwd(NULL, 0);
    if (chdir(&data->arg[0][i]) == ERROR_RETURNED)
    {
        raise_error(NULL, "cd", EXIT_FAILURE, FALSE);
        if (old)
            free(old);
        return ;
    }
    if (!old_pwd)
        add_env_item(env, "OLDPWD=NONE");
    old_pwd = get_env_item_or_none("OLDPWD", *env);
    update_env_value(old_pwd, old);
    update_env_value(pwd, getcwd(NULL, 0));
}

void    cd_back(t_env **env)
{
    t_env *old_pwd;
    char *old;

    old_pwd = get_env_item_or_none("OLDPWD", *env);
    old = NULL;
    if (!old_pwd)
        raise_error("OLDPWD not set", "cd", EXIT_FAILURE, FALSE);
    else
    {
        old = getcwd(NULL, 0);
        if (chdir(old_pwd->value) == ERROR_RETURNED)
        {
            raise_error(NULL, "cd", EXIT_FAILURE, FALSE);
            if (old)
                free(old);
            return ;
        }
        update_env_value(old_pwd, old);
        update_env_value(get_env_item_or_none("PWD", *env), getcwd(NULL, 0));
    }
}

int cd_back_valid_arg(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] != '-')
            return (FALSE);
        i++;
    }
    if (i > 2)
        return (FALSE);
    return (TRUE);
}

void    cd_home(t_env **env)
{
    t_env *home;
    t_env *old_pwd;
    char *old;

    home = get_env_item_or_none("HOME", *env);
    old_pwd = get_env_item_or_none("OLDPWD", *env);
    old = NULL;
    if (!home)
        raise_error("HOME not set", "cd", EXIT_FAILURE, FALSE);
    else
    {
        old = getcwd(NULL, 0);
        if (chdir(home->value) == ERROR_RETURNED)
        {
            raise_error(NULL, "cd", EXIT_FAILURE, FALSE);
            if (old)
                free(old);
            return ;
        }
        if (!old_pwd)
            add_env_item(env, "OLDPWD=NONE");
        old_pwd = get_env_item_or_none("OLDPWD", *env);
        update_env_value(old_pwd, old);
        update_env_value(get_env_item_or_none("PWD", *env), getcwd(NULL, 0));
    }
}