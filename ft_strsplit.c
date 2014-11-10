/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:23:10 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/10 14:40:10 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		countwords(const char *s, char c)
{
	int		i;

	i = 0;
	while (*s++)
		if (*s == c && *(s + 1) != c && *(s + 1))
			i++;
	return (i);
}

static size_t	len(const char *s, char c)
{
	size_t		i;

	i = 0;
	while (*s && *s != c)
		i++;
	return (i);
}

static void		cpy(char *s1, char *s2, char c)
{
	while (*s2 != c)
		*s1++ = *s2++;
	*s1 = 0;
}

static char*	new(const char *s, char c)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (len(s, c) + 1));
	cpy(ret, (char *)s, c);
	return (ret);
}

char		**ft_strsplit(const char *s, char c)
{
	char			**tab;
	char			**ret;
	unsigned int	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * countwords(s, c));
	if (!tab)
		return (NULL);
	ret = tab;
	while (*s)
		if (*s == c && *(s + 1) != c && *(s + 1))
			*tab++ = new(s, c);
	return (tab);
}
