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

void    free_cmd(t_parse *cmd)
{
    if (cmd)
    {
        if (cmd->path)
        {
            printf("cmd->path\n");
            free(cmd->path);
            cmd->path = NULL;
        }
        if (cmd->env_2d)
        {
            printf("cmd->env_2d\n");
            free_2d_buff(cmd->env_2d);
        }
            
        if (cmd->cmd_2d)
        {
            printf("cmd->cmd_2d\n");
            free_2d_buff(cmd->cmd_2d);
        }
    }
}

void    free_all(t_exec *exe)
{
    int i;

    i = 0;
    if (exe)
    {
        if (exe->pipes)
        {
            while (exe->pipes[i])
            {
                free(exe->pipes[i]);
                exe->pipes[i] = NULL;
                i++;
            }
            free(exe->pipes);
            exe->pipes = NULL;
        }
        free(exe);
        exe = NULL;
    }
}