/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 08:44:28 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/04 00:10:25 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "execution/execution.h"
#include <signal.h>

void	my_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	add_back(t_token **list, t_token *tmp)
{
    t_token *tmp1;
    
    tmp1 = *list;
    if (*list == NULL)
        (*list) = tmp;
    else
    {
        while (tmp1->next != NULL)
			tmp1 = tmp1->next;
        tmp1->next = tmp;
    }
}

int	bigger(int a, int c)
{
	if (a > c)
        return (a);
    return (c);
}

int check_space(char *str)
{
	int i = 0;
	while(str[i] && str[i] != ' ')
		i++;
	return (i);
}
char *env_search_h(char *str, t_lexer *lexer)
{
	t_env *tmp = (*lexer->_env);
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, str))
		{
			free (str);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	free(str);
	return (ft_strdup("\0"));
}

char *check_h(char *str, t_lexer *lexer)
{
	int i = 0;
	char *tmp = ft_strdup("");
	char *tmp1;
	int x;
	while(str[i])
	{
		if (str[i] == '$')
		{
			x = check_space(&str[i]);
			tmp1 = ft_substr(str, i + 1, x);
			tmp1 = env_search_h(tmp1, lexer);
			tmp = ft_strjoin(tmp, tmp1);
			free(tmp1);
			i += x + 1;
		}
		else
		{
			tmp[i] = str[i];
			i++;
		}
	}
	free(str);
	return (tmp);
}

void    ft_herdoc(t_rdr   *tmp1, t_lexer *lexer)
{
    char *a;
    int fd[2];
	int	id;
	int status;

    if (tmp1->type == 3 && tmp1->herdoc)
    {
		signal(SIGINT, SIG_IGN);
		pipe(fd);
		id = fork();
		if (id == 0)
		{
			signal(SIGINT, SIG_DFL);
        	a = readline("> ");
			if (a)
			{
				close(fd[0]);
				while (ft_strncmp(a, tmp1->value,
					bigger(ft_strlen(a),ft_strlen(tmp1->value))))
				{
					if (!lexer->flg_quote)
						a = check_h(a, lexer);
					ft_putstr_fd(a, fd[1]);
					ft_putstr_fd("\n", fd[1]);
					free(a);
					a = readline("> ");
					if (!a)
						break ;
				}
        		free(a);
			}
        	close(fd[1]);
			exit(0);
		}
		close(fd[1]);
		waitpid(-1, &status, 0);
		tmp1->fd = fd[0];
    }
}
void	herdoc_handler(t_parse *parse, t_lexer *lexer)
{
	t_parse *tmp;
	t_rdr   *tmp1;

    tmp = parse;
	while (tmp)
	{
		if (tmp->rdr != NULL)
		{
			tmp1 = tmp->rdr;
            while(tmp1)
            {
                ft_herdoc(tmp1, lexer);
                tmp1 = tmp1->next;
            }
		}
		tmp = tmp->next;
	}
}

void	rdr_create_files(t_parse **parse, t_lexer *lexer)
{
	t_parse *tmp = (*parse);
    t_rdr *tmpr;
	while(tmp)
	{
        tmpr = tmp->rdr;
        while(tmpr)
        {
		    if (tmpr->type == 4 && !lexer->flg_error)
			{
				tmpr->fd = open(tmpr->value, O_RDWR, 0777);
				if (tmpr->fd == -1 || !tmpr->value[0])
				{
					raise_error(NULL, tmpr->value, EXIT_FAILURE, FALSE);
					lexer->flg_error = 1;
					tmpr->fd = ERROR_FILE;
				}
			}
		    if (tmpr->type == 5 && !lexer->flg_error)
			{
			    tmpr->fd = open(tmpr->value, O_CREAT | O_WRONLY | O_TRUNC, 0777);
				if (tmpr->fd == -1 || !tmpr->value)
				{
					raise_error(NULL, tmpr->value, EXIT_FAILURE, FALSE);
					lexer->flg_error = 1;
					tmpr->fd = ERROR_FILE;
				}
			}
		    if (tmpr->type == 6 && !lexer->flg_error)
			{
			    tmpr->fd = open(tmpr->value, O_CREAT | O_RDWR | O_APPEND, 0777);
				if (tmpr->fd == -1 || !tmpr->value)
				{
					raise_error(NULL, tmpr->value, EXIT_FAILURE, FALSE);
					lexer->flg_error = 1;
					tmpr->fd = ERROR_FILE;
				}
			}
			tmpr = tmpr->next;
        }
        tmp = tmp->next;
	}
}

void ft_free_list(t_token *token)
{
	t_token *tmp1;

	tmp1 = token;
	if (token)
	{
		while (tmp1)
		{
			token = token->next;
			free(tmp1->value);
			free(tmp1);
			tmp1 = token;
		}
	}
}

void	after_parse(t_parse *parse, t_token *token, t_lexer *lexer)
{
	if (lexer->flg_error == 1)
	{
		write(2, "syntax_error\n", 14);
		g_exitm = 258;
	}
	if (parse != NULL)
		herdoc_handler(parse, lexer);
	if (!lexer->flg_error && parse != NULL)
		rdr_create_files(&parse, lexer);
	if (parse != NULL)
		execution(parse, lexer->_env);
	ft_free_list(token);
}

void	init_minishell(t_lexer *lexer, char *str, t_parse *parse, t_token *token)
{
	t_token *tmp;

	if (!str)
	{
		printf("exit\n");
		exit(g_exitm);
	}
	if (str[0] != '\0')
	{
		add_history(str);
		lexer = init_lexer(str, lexer);
		token = NULL;
		while ((tmp = get_next_token(lexer)) != NULL && !lexer->flg_error)
		{
			add_back(&token, tmp);
			tmp = NULL;
		}
		if ((token) != NULL)
			parse = init_parsing(&token, lexer);
		after_parse(parse, token, lexer);
		parse = NULL;
	}
}


int main(int ac, char **av, char **env)
{
    t_lexer  *lexer;
    t_token *token;
    t_parse *parse;
	t_env 	*env_list;
    char    *str;
    (void) av;

    token = NULL;
    parse = NULL;
    env_list = setup_env(env);
    str = NULL;
    lexer = malloc(sizeof(t_lexer));
    lexer->_env = &env_list;
    if (ac == 1)
    {
        while(1)
        {
			lexer->flg_quote = 0;
        	signal(SIGINT, my_handler);
         	signal(SIGQUIT, SIG_IGN);
         	str = readline("minishell >$ ");
         	init_minishell(lexer, str, parse, token);
			free(str);
        }
    }
    return (0);
}
