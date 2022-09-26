/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:01:54 by schoukou          #+#    #+#             */
/*   Updated: 2021/11/20 19:03:37 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*void	ftt(unsigned int i , char *c)
{
	((void) i);
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}*/
/*int main()
{
	char s[] = "sfhgfhf";
	ft_striteri(s,ftt);
	printf("%s", s);
}*/