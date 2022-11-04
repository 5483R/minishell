/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 22:10:53 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/03 23:50:40 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**copy_env(char **env)
{
	int		i;
	char	**copy;
	int		x;

	i = 0;
	x = count_2d(env);
	copy = malloc(sizeof(char *) * (x + 1));
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	*env_search(t_lexer *lexer, char *c)
{
	t_env *tmp = (*lexer->_env);
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, c))
		{
			free (c);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	free(c);
	return (NULL);
}

char	*dollar_handler2(t_lexer *lexer, char *s, char *c)
{
	int i = 0;

	while (lexer->c)
	{
		if (i == 0 && ft_isdigit(lexer->c))
		{
			lexer_advance(lexer);
			free(s);
			return (ft_strdup("\0"));
		}
		if (lexer->c != '_' && !ft_isalnum(lexer->c))
			break ;
		else
		{
			c = get_current_char_as_string(lexer);
			s = ft_strjoin(s, c);
			free(c);
			lexer_advance(lexer);
		}
	}
	s = env_search(lexer, s);
	if (s == NULL)
		s = ft_strdup("\0");
	return (s);
}

char	*dollar_handler(t_lexer *lexer)
{
	char	*s;
	char	*c;

	s = ft_strdup("");
	c = ft_strdup("");
	if (lexer->c == '?')
	{
		free(c);
		c = ft_itoa(g_exitm);
		s = ft_strjoin(s, c);
		free(c);
		lexer_advance(lexer);
		return (s);
	}
	if (lexer->c != '_' && !ft_isalnum(lexer->c))
	{
		s = ft_strjoin(s, "$");
		free(c);
		return (s);
	}
	s = dollar_handler2(lexer, s, c);
	free(c);
	return (s);
}
