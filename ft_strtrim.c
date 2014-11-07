/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:35:32 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 17:10:00 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char			*ft_strtrim(char const *s)
{
	size_t		start;
	size_t		end;
	char		*str;
	char		*data;
	char		*ret;

	if (!s)
		return (NULL);
	str = (char *)s;
	start = 0;
	while (space(*str++))
		start++;
	str--;
	end = ft_strlen(s) - 1;
	if (start != (end + 1))
		while (space(s[end]))
			end--;
	data = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!data)
		return (NULL);
	ret = data;
	while (start++ <= end)
		*data++ = *str++;
	*data = 0;
	return (ret);
}
