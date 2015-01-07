/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_wedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 19:16:49 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/07 19:16:52 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		to_wedge(const char *str, int n)
{
	int		i;
	int		l;

	if (!str)
		return ;
	l = 0;
	i = n - ft_strlen(str);
	while (i-- > 0)
	{
		ft_putchar(' ');
		l++;
	}
	while (l++ < n)
		ft_putchar(*str++);
}

void		to_wedge2(const char *str, int n)
{
	int		l;

	if (!str)
		return ;
	l = 0;
	while (l++ < n && *str)
		ft_putchar(*str++);
	while (l++ <= n)
		ft_putchar(' ');
}

void		to_wedge_lli2(long long int nb, int n)
{
	int		l;

	l = ft_llilen(nb);
	ft_putnbrll(nb);
	while (l++ < n)
		ft_putchar(' ');
}

void		to_wedge_lli(long long int nb, int n)
{
	int		i;
	int		l;

	l = 0;
	i = n - ft_llilen(nb);
	while (i-- > 0)
	{
		ft_putchar(' ');
		l++;
	}
	ft_putnbrll(nb);
}
