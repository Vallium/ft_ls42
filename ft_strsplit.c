/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:23:10 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 13:51:35 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(const char *s, char c)
{
	int		i;

	i = 0;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1))
			i++;
		s++;
	}
	return (i);
}

char		**ft_strsplit(const	char *s, char c)
{
	char			**tab;
	char			*data;
	char			*datatmp;
	unsigned int	i;

	if (!s)
		return (NULL);
	data = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	tab = (char **)malloc(sizeof(char *) * countwords(s, c));
	datatmp = data;
	i = 0;
	while (*datatmp)
	{
		if (*datatmp == c && *(datatmp + 1) != c && *(datatmp + 1))
			tab[i] = datatmp + 1;
		if (*datatmp == c)
			*datatmp = 0;
		datatmp++;
		i++;
	}
	return (tab);
}
