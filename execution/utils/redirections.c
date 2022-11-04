#include "../execution.h"

int get_input_redirection(t_parse *cmd)
{
    t_rdr *current;
    int fd;

    fd = NONE;
    current = cmd->rdr;
    while (current)
    {
        if (current->type == HEREDOC || current->type == SINGLE_LEFT_RED)
            fd = current->fd;
        current = current->next;
    }
    return (fd);
}

int get_output_redirection(t_parse *cmd)
{
    t_rdr *current;
    int fd;

    fd = NONE;
    current = cmd->rdr;
    while (current)
    {
        if (current->type == SINGLE_RIGHT_RED || current->type == DOUBLE_RIGHT_RED)
            fd = current->fd;
        current = current->next;
    }
    return (fd);
}

int get_read_src(t_parse *cmd, t_exec *exe)
{
    int fd;

    fd = cmd->read_src;
    if (fd == NONE && exe->pipes)
    {
        if (cmd->id != 0)
            fd = exe->pipes[cmd->id - 1][READ_END];
    }
    return (fd);
}

int get_write_dst(t_parse *cmd, t_exec *exe)
{
    int fd;

    fd = cmd->write_dst;
    if (fd == NONE && exe->pipes && cmd->next)
    {
        if (cmd->id == (exe->ncmds - 1))
            fd = NONE;
        else
            fd = exe->pipes[cmd->id][WRITE_END];
    }
    return (fd);
}