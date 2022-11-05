/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:25:12 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/04 22:19:08 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *char_join(char *str, char a)
{
	char *new;
	int	i = 0;
	new = malloc(ft_strlen(str) + 2);
	while(str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = a;
	new[++i] = '\0';
	free(str);
	return (new);
}

char    *check_h(char *str, t_lexer *lexer)
{
	int     i;
	int     x;
	char    *tmp;
	char    *tmp1;

    tmp = ft_strdup("");
	i = 0;
	while (str[i])
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
			tmp = char_join(tmp, str[i++]);
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
void    herdoc_handler(t_parse *parse, t_lexer *lexer)
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
