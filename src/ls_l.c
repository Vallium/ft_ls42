/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 19:15:42 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/07 19:15:46 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_l(char *arg)
{
	t_file			file;
	t_file			**tab;
	t_llu			llu;

	llu.total = 0;
	if (!(fill_tab(&tab, arg, &llu)))
		return ;
	sort_tab(&tab, &llu);
	print_total(&llu);
	printfilelist(tab, llu.size, arg);
	llu.i = 0;
	while (llu.i < llu.size)
	{
		file = *((t_file *)tab[llu.i]);
		if (g_re && S_ISDIR(file.stats.st_mode) && ft_strcmp(file.name, ".")
				&& ft_strcmp(file.name, ".."))
			llu.total = 0,
			ft_putchar('\n'),
			ft_putstr(ft_burger(arg, '/', file.name)),
			ft_putendl(":"),
			ls_l(ft_burger(arg, '/', file.name));
		llu.i++;
	}
	free_ls(tab, &llu);
}

void		ls_mult_arg(char *argv, int i)
{
	if (i)
	{
		ft_putstr(argv);
		ft_putstr(":\n");
	}
	ls_l(argv);
}

void		free_ls(t_file **tab, t_llu *llu)
{
	llu->i = 0;
	while (llu->i < llu->size)
		free(tab[llu->i++]);
	free(tab);
}

t_file		**lst2tab(t_list **lst, int *size)
{
	t_list *tmp;
	t_file **tab;

	*size = 0;
	tmp = *lst;
	while (tmp)
	{
		(*size)++;
		tmp = tmp->next;
	}
	tmp = *lst;
	tab = (t_file **)malloc(sizeof(t_file *) * (*size));
	*size = 0;
	while (tmp)
	{
		tab[(*size)++] = (t_file *)tmp->content;
		tmp = tmp->next;
	}
	ft_lstsimpledel(lst);
	return (tab);
}
