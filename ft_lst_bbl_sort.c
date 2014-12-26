/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_bbl_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 23:17:46 by adoussau          #+#    #+#             */
/*   Updated: 2014/12/16 23:17:50 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>


void	ft_lst_bbl_sort(t_list *lst, int (*f)(t_file *f1, t_file *f2))
{
	t_list		*tmp;
	int		    end;
	t_file		*f1;
	t_file		*f2;

	end = 0;

	while (!end)
	{
		//printf("Alive\n");
		end = 1;
		tmp = lst;
		while (tmp->next)
		{
			f1 = (t_file*)tmp->content;
			f2 = (t_file*)tmp->next->content;

			if (f(f1, f2))
			{
				//printf("%s > %s\t\t\n", f1->entree->d_name, f2->entree->d_name);
				ft_swap(&tmp->content, &tmp->next->content);
				//printf("%llu < %llu\n", f1->stat.st_size, f2->stat.st_size);
				end = 0;
			}
			tmp = tmp->next;
		}
	}
}
