/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:51:17 by schoukou          #+#    #+#             */
/*   Updated: 2021/11/20 19:42:40 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_intlen(int value)
{
	int	counter;

	counter = 0;
	if (value < 0)
	{
		counter++;
		value = -value;
	}
	else if (value == 0)
		return (1);
	while (value > 0)
	{
		value /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int x)
{
	char		*s;
	size_t		len;
	long int	n;

	n = x;
	if (x == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n) + 1;
	s = malloc(sizeof(char) * len);
	if (s == NULL)
		return (NULL);
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	s[len - 1] = '\0';
	while (n && len--)
	{
		s[len - 1] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
/*int main()
{
 int a = -50;
 char *x = ft_itoa(a);
 printf("%s", x);
}*/