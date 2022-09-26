/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 05:29:33 by schoukou          #+#    #+#             */
/*   Updated: 2021/11/21 05:31:55 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	get_ln(const char *s, const char *set, int offset)
{
	int	i;

	i = 0;
	if (offset == 0)
	{
		while (s[i] && is_in_set(s[i], set))
			i++;
	}
	else
	{
		offset--;
		while (s[offset - i] && is_in_set(s[offset - i], set))
			i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		ln1;
	int		ln2;
	int		len;
	char	*p;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	ln1 = get_ln(s1, set, 0);
	if (ln1 >= len)
		return (ft_strdup("\0"));
	ln2 = get_ln(s1, set, len);
	p = ft_substr(s1, ln1, len - (ln1 + ln2));
	return (p);
}
/*int main()
{
	printf("%s", ft_strtrim("\0hhh\0", "\0"));
}*/