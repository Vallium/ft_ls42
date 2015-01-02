/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 15:37:32 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/02 15:37:36 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_sub(char *str, int start, int l)
{
	if (!str)
		return ;
	str += start;
	while (l-- && *str)
	{
		ft_putchar(*str++);
	}
}
