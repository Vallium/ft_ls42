/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 19:13:04 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/07 19:13:42 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_intlen(int i)
{
	int ret;

	ret = 1;
	while (i /= 10)
		ret++;
	return (ret);
}

int			ft_llilen(long long int i)
{
	int ret;

	ret = 1;
	while (i /= 10)
		ret++;
	return (ret);
}
