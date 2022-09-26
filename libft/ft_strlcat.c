/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:39:41 by schoukou          #+#    #+#             */
/*   Updated: 2021/11/26 21:59:14 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dlen;
	unsigned int	slen;

	i = 0;
	j = 0;
	slen = ft_strlen(src);
	if (size == 0 && !dest)
		return (slen);
	dlen = ft_strlen(dest);
	i = dlen;
	if (size == 0 || size <= dlen)
		return (slen + size);
	while (src[j] != '\0' && size > dlen + 1)
	{
		dest[i] = src[j];
		i++;
		j++;
		size--;
	}
	dest[i] = '\0';
	return (dlen + slen);
}
