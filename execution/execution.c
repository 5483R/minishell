#include "execution.h"

int     exit_status;

void    run_cmd(t_parse *cmd)
{
    if (run_as_builtin(cmd))
        return ;
}

t_exec  *setup_exec(t_parse *cmds)
{
    t_exec  *exe;
    t_parse *current;

    exe = malloc(sizeof(t_exec));
    if (!exe)
        raise_error("Memory allocation failed!", "malloc");
    exe->cmds = cmds;
    exe->ncmds = 0;
    current = cmds;
    while (current)
    {
        exe->ncmds++;
        current = current->next;
    }
    exe->pipes = malloc(sizeof(int *) * (exe->ncmds - 1));
    if (!exe->pipes)
        raise_error("Memory allocation failed!", "malloc");
    return (exe);
}

void    execution(t_parse *data)
{
    //int      pid;
    t_exec  *exe;
    t_parse *current;

    exe = setup_exec(data);
    current = exe->cmds;
    while (current)
    {
        run_cmd(current);
        current = current->next;
    }
}