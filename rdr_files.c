/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:26:43 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/06 20:40:58 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "execution/execution.h"
// void	rd_files_2(t_parse **parse, t_lexer *lexer)
// {
// 	t_parse	*tmp;
// 	t_rdr	*tmpr;
	
// 	if (tmpr->type == 4 && !lexer->flg_error)
// 		{
// 			tmpr->fd = open(tmpr->value, O_RDWR, 0777);
// 			if (tmpr->fd == -1 || !tmpr->value[0])
// 			{
// 				raise_error(NULL, tmpr->value, EXIT_FAILURE, FALSE);
// 				lexer->flg_error = 1;
// 				tmpr->fd = ERROR_FILE;
// 			}
// 		}
// 		if (tmpr->type == 5 && !lexer->flg_error)
// 		{
// 			tmpr->fd = open(tmpr->value, O_CREAT
// 					| O_WRONLY | O_TRUNC, 0777);
// 			if (tmpr->fd == -1 || !tmpr->value)
// 			{
// 				raise_error(NULL, tmpr->value, EXIT_FAILURE, FALSE);
// 				lexer->flg_error = 1;
// 				tmpr->fd = ERROR_FILE;
// 			}
// 		}
// }
void	rdr_create_files(t_parse **parse, t_lexer *lexer)
{
	t_parse	*tmp;
	t_rdr	*tmpr;

	tmp = (*parse);
	while (tmp)
	{
		tmpr = tmp->rdr;
		lexer->flg_error = 0;
		while (tmpr)
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
				tmpr->fd = open(tmpr->value, O_CREAT
						| O_WRONLY | O_TRUNC, 0777);
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
