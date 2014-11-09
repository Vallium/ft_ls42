/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 08:20:02 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/09 12:38:25 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *us1;
	unsigned char *us2;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 || *us2)
	{
		if (*us1 != *us2)
			return (*us1 - *us2);
		us1++;
		us2++;
	}
	return (0);
}
