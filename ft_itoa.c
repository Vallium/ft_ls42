/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:50:44 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 15:58:33 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		count(int i)
{
	int		j;

	j = 0;
	while (i /= 10)
		j++;
	printf("\n%i\n",i);
	return (j + 1);
}

char		*ft_itoa(int i)
{
	printf("\nitoa(%i)\n",i);
	size_t	size;
	char	*ret;
	char	*str;

	size = count(i);
	ret = (char *)malloc(sizeof(char) * (size + (i < 0 ? 1 : 0) + 1));
	if (!ret)
		return (NULL);
	str = ret;
	if (i < 0)
	{
		*str++ = '-';
		i = -i;
	}
	str += size - 1;
	*(str + 1) = 0;
	while (size--)
	{
		printf("%i\n",i%10);
		*str-- = (char)(i % 10 + '0');
		i /= 10;
	}
	return (ret);

}
