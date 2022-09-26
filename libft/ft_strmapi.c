/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:39:23 by schoukou          #+#    #+#             */
/*   Updated: 2021/11/20 17:42:48 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*p;
	int		len;

	i = 0;
	if (s == 0)
		return (NULL);
	len = ft_strlen(s);
	p = (char *)malloc(len + 1);
	if (p == NULL)
		return (NULL);
	while (s[i])
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
/*char	ftt(unsigned int i , char c)
{
	((void) i);
	
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}*/
/*int main()
{
	char *s = "sfhgfhf";

	printf("%s", ft_strmapi(s,ftt));
}*/