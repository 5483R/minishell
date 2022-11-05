#include "../execution.h"

void    free_2d_buff(char **buff)
{
    int i;

    i = 0;
    if (buff)
    {
        while (buff[i])
        {
            free(buff[i]);
            buff[i] = NULL;
            i++;
        }
        free(buff);
        buff = NULL;
    }
}

void    free_buff(char *buff)
{
    if (buff)
    {
        free(buff);
        buff= NULL;
    }
}

void    free_redirections(t_rdr *red)
{
    t_rdr *current;

    current = red;
    if (current)
    {
        while (current)
        {
           if (current->value)
               free(current->value);
           current = current->next;
        }
        free(red);
    }
}

void    free_cmds(t_parse *cmd)
{
    t_parse *current;
    t_parse *tmp;

    tmp = NULL;
    current = cmd;
    while (current)
    {
        free_buff(current->cmd);
        free_buff(current->path);
        free_2d_buff(current->env_2d);
        free_2d_buff(current->cmd_2d);
        free_redirections(current->rdr);
        free_2d_buff(current->arg);
        current = current->next;
    }
    current = cmd;
    while (current)
    {
        tmp = current;
        current = current->next;
        free(tmp);
    }
}

void    free_all(t_parse *data, t_exec *exe)
{
    int i;

    i = 0;
    free_cmds(data);
    if (exe)
    {
        if (exe->pipes)
        {
            while (exe->pipes[i])
            {
                free(exe->pipes[i]);
                i++;
            }
            free(exe->pipes);
        }
        free(exe);
    }
}
