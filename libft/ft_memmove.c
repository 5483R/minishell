/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:05:00 by schoukou          #+#    #+#             */
/*   Updated: 2021/11/28 15:47:39 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	char		*lastd;
	const char	*s;
	const char	*lasts;

	d = dst;
	s = src;
	if ((d == 0 && s == 0))
	{
		return (NULL);
	}
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{	
		lasts = s + (len - 1);
		lastd = d + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
