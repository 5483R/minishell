/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:26:34 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/06 20:26:36 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_free_list(t_token *token)
{
	t_token	*tmp1;

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

void	add_back(t_token **list, t_token *tmp)
{
	t_token	*tmp1;

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
