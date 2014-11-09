/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:35:32 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/09 20:12:34 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	char		*tmp;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	i = ft_strlen(s) - 1;
	tmp = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i = i - 1;
	j = 0;
	while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
		j = j + 1;
	if (j == ft_strlen(s))
	{
		tmp[0] = '\0';
		return (tmp);
	}
	tmp = ft_strsub(s, j, i - j + 1);
	return (tmp);
}
