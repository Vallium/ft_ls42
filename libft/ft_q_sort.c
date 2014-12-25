/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_q_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 12:17:19 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 20:45:20 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void			sort(void **tab, int bg, int ed, int (*f)(void *, void *))
{
	const void	*pvt = tab[bg];
	int			lft;
	int			rgt;

	lft = bg - 1;
	rgt = ed + 1;
	if (bg >= ed)
		return ;
	while (1)
	{
		while (f(tab[--rgt], pvt))
			;
		while (!f(tab[++lft], pvt))
			;
		if (lft < rgt)
			ft_swap(&tab[lft], &tab[rgt]);
		else
			break ;
	}
	sort(tab, bg, rgt, f);
	sort(tab, rgt + 1, ed, f);
}

void	ft_q_sort(void **tab, size_t size, int (*f)(void *, void *))
{
	sort(tab, 0, size - 1, f);
}
