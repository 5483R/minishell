/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:45:24 by schoukou          #+#    #+#             */
/*   Updated: 2022/08/01 22:44:20 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	y;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	y = 0;
	while (src[y] != '\0')
	{
		dest[i] = src[y];
		i++;
		y++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	p;

	p = 0;
	while (src[p] != '\0')
	{
		dest[p] = src[p];
		p++;
	}
	dest[p] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;

	if ((s1) == 0 || (s2) == 0)
		return (NULL);
	result = malloc(ft_strlen(((char *)s1)) + ft_strlen(((char *)s2)) + 1);
	if (result == NULL)
		return (NULL);
	if (result)
	{
		ft_strcpy(result, ((char *)s1));
		ft_strcat(result, ((char *)s2));
	}
	free(s1);
	return (result);
}
/*int main()
{
    char a[] = {"ahlan"};
    char b[] = " hh";
    printf("%s", ft_strjoin(a,b));
}*/
