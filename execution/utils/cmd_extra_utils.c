#include "../execution.h"

int get_cmd_type(char *cmd_name)
{
    if (is_identical(cmd_name, ECHO)
        || is_identical(cmd_name, CD)
        || is_identical(cmd_name, PWD)
        || is_identical(cmd_name, EXPORT)
        || is_identical(cmd_name, UNSET)
        || is_identical(cmd_name, ENV)
        || is_identical(cmd_name, EXIT))
        return (BUILTIN_CMD);
    return (NORMAL_CMD);
}

void    wait_cmds(t_parse *cmds)
{
    t_parse *current;
    
    current = cmds;
    while (current && current->cmd)
    {
        if (current->pid != NONE)
        {
            waitpid(current->pid, &g_exitm, WUNTRACED);
            if (WIFEXITED(g_exitm))
                g_exitm = WEXITSTATUS(g_exitm);
        }
        current = current->next;
    }
}

void    cmds_initialization(t_parse *cmds)
{
    t_parse *current;

    current = cmds;
    while (current)
    {
        current->cmd_2d = NULL;
        current->env_2d = NULL;
        current->path = NULL;
        current->read_src = get_input_redirection(current);
        current->write_dst = get_output_redirection(current);
        current = current->next;
    }
}

void    check_cmd_path(char *path)
{
    struct stat file_data;

    if (path)
    {
        stat(path, &file_data);
        if (S_ISDIR(file_data.st_mode))
            raise_error("Is a directory", path, 126, TRUE);
        if (path[0] == '.' || path[0] == '/')
        {
            if (access(path, X_OK) == ERROR_RETURNED)
                raise_error(NULL, path, 126, TRUE);
        }
    }
}
