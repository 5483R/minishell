/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:25:21 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/04 15:29:41 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_space(char *str)
{
	int i = 0;
	while(str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*env_search_h(char *str, t_lexer *lexer)
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
