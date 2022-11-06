/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 08:44:28 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/06 20:26:14 by schoukou         ###   ########.fr       */
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
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	bigger(int a, int c)
{
	if (a > c)
		return (a);
	return (c);
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

void	init_minishell(t_lexer *lexer, char *str,
						t_parse *parse, t_token *token)
{
	t_token	*tmp;

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

int	main(int ac, char **av, char **env)
{
	t_lexer	*lexer;
	t_token	*token;
	t_parse	*parse;
	t_env	*env_list;
	char	*str;

	(void) av;
	token = NULL;
	parse = NULL;
	env_list = setup_env(env);
	str = NULL;
	lexer = malloc(sizeof(t_lexer));
	lexer->_env = &env_list;
	if (ac == 1)
	{
		while (1)
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
