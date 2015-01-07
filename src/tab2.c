/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 19:16:38 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/07 19:16:42 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		tab_fill(t_argtab *tab, int argc, char *argv[])
{
	int		i;
	int		get;

	i = 0;
	while (i < argc)
	{
		get = get_types(argv[i]);
		tab_distrib(tab, get, argv[i]);
		if (get == 3)
			tab->error.data[tab->error.size++] = argv[i];
		i++;
	}
	i = 0;
	while (i++ < tab->file.size)
		tab->file.ptr[i - 1] = &tab->file.data[i - 1];
	i = 0;
	while (i++ < tab->dir.size)
		tab->dir.ptr[i - 1] = &tab->dir.data[i - 1];
}

void		tab_sort(t_argtab *tab)
{
	if (!g_r)
		ft_sort_qck((void**)tab->dir.ptr, tab->dir.size, file_name_cmp),
		ft_sort_qck((void**)tab->file.ptr, tab->file.size, file_name_cmp);
	else
		ft_sort_qck((void**)tab->dir.ptr, tab->dir.size, file_r_name_cmp),
		ft_sort_qck((void**)tab->file.ptr, tab->file.size, file_r_name_cmp);
	if (g_t)
	{
		if (!g_r)
			ft_sort_qck((void**)tab->dir.ptr, tab->dir.size, file_time_cmp),
			ft_sort_qck((void**)tab->file.ptr, tab->file.size, file_time_cmp);
		else
			ft_sort_qck((void**)tab->dir.ptr, tab->dir.size, file_r_time_cmp),
			ft_sort_qck((void**)tab->file.ptr, tab->file.size, file_r_time_cmp);
	}
}

void		tab_free(t_argtab *tab)
{
	free(tab->file.data);
	free(tab->file.ptr);
	free(tab->dir.data);
	free(tab->dir.ptr);
}

void		arg_to_tab(int argc, char *argv[])
{
	t_argtab		tab;
	int				i;

	tab_init(&tab, argc);
	tab_fill(&tab, argc, argv);
	tab_sort(&tab);
	print_error(tab);
	printfilelist(tab.file.ptr, tab.file.size, "");
	if (!tab.dir.size)
		return ;
	if (tab.error.size || tab.file.size)
		ft_putchar('\n');
	if (tab.dir.size != 1)
		ft_putstr(tab.dir.ptr[0]->name),
		ft_putendl(":");
	i = 0;
	while (i < (tab.dir.size))
	{
		ls_mult_arg(tab.dir.ptr[i]->name, i);
		if (i != (tab.dir.size - 1))
			ft_putchar('\n');
		i++;
	}
	tab_free(&tab);
	exit(0);
}
