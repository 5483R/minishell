#include "../execution.h"

int **create_pipes(int npipes)
{
    int **pipes;
    int i;

    i = 0;
    pipes = malloc(sizeof(int *) * (npipes + 1));
    while (i < npipes)
    {
        pipes[i] = malloc(sizeof(int ) * 2);
        pipe(pipes[i]);
        i++;
    }
    pipes[i] = NULL;
    return (pipes);
}

void    reset_standard_fds(t_exec *exe)
{
    dup2(exe->stdout_dup, 1);
    dup2(exe->stdin_dup, 0);
}

void    hold_standard_fds(t_exec *exe)
{
    exe->stdin_dup = dup(STDIN_FILENO);
    exe->stdout_dup = dup(STDOUT_FILENO);
}

void    dup_close_fds(t_parse *cmd, t_exec *exe)
{
    if (cmd->read_src > 0)
        dup2(cmd->read_src, 0);
    if (cmd->write_dst > 0)
        dup2(cmd->write_dst, 1);
    close_fds(exe, cmd);
}

void    close_fds(t_exec *exe, t_parse *cmd)
{
    int i;

    i = 0;
    while (exe->pipes && i < (exe->ncmds - 1))
    {
        close(exe->pipes[i][WRITE_END]);
        close(exe->pipes[i][READ_END]);
        i++;
    }
    if (cmd)
    {
        if (cmd->read_src > 0)
            close(cmd->read_src);
        if (cmd->write_dst > 0)
            close(cmd->write_dst);
    }
}