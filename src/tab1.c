/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 19:16:30 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/07 19:16:34 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			fill_tab(t_file ***tab, char *arg, t_llu *llu)
{
	struct dirent	*entree;
	DIR				*ptdir;
	t_list			*lst;
	t_file			file;

	ptdir = opendir(arg);
	if (!ptdir)
	{
		ft_putstr_fd("ls: ", 2), perror(arg);
		return (0);
	}
	lst = NULL;
	while ((entree = readdir(ptdir)) != NULL)
	{
		ft_strcpy(file.name, entree->d_name);
		lstat(ft_burger(arg, '/', entree->d_name), &(file.stats));
		file.lnkname[readlink(ft_burger(arg, '/', entree->d_name),
		file.lnkname, MAXLEN)] = 0;
		if (g_a || *(file.name) != '.')
			ft_lstsmartpushback(&lst, ft_lstnew(&file, sizeof(t_file))),
			llu->total += file.stats.st_blocks;
	}
	closedir(ptdir), *tab = lst2tab(&lst, &(llu->size)), ft_lstsimpledel(&lst);
	return (1);
}

void		sort_tab(t_file ***tab, t_llu *llu)
{
	ft_sort_qck((void **)*tab, llu->size, !g_r ?
				file_name_cmp : file_r_name_cmp);
	if (g_ss)
		ft_sort_qck((void **)*tab, llu->size, !g_r ?
					file_size_cmp : file_r_size_cmp);
	else if (g_t)
		ft_sort_qck((void **)*tab, llu->size, !g_r ?
					file_time_cmp : file_r_time_cmp);
}

int			get_types(char *arg)
{
	char			buff[256];
	int				i;
	struct stat		stats;

	if (!*(arg))
	{
		lstat(arg, &stats);
		ft_putstr_fd("ls: ", 2), perror("fts_open");
		exit(1);
	}
	if (lstat(arg, &stats) == -1)
		return (3);
	if (S_ISLNK(stats.st_mode))
	{
		i = readlink(arg, buff, 256);
		buff[i] = 0;
		lstat(buff, &stats);
	}
	if (S_ISDIR(stats.st_mode) && !g_l)
		return (1);
	else if (S_ISDIR(stats.st_mode))
		return (1);
	else
		return (2);
}

void		tab_init(t_argtab *tab, int argc)
{
	tab->file.size = 0;
	tab->dir.size = 0;
	tab->error.size = 0;
	tab->file.data = (t_file *)malloc(sizeof(t_file) * argc);
	tab->file.ptr = (t_file **)malloc(sizeof(t_file*) * argc);
	tab->dir.data = (t_file *)malloc(sizeof(t_file) * argc);
	tab->dir.ptr = (t_file **)malloc(sizeof(t_file *) * argc);
	tab->error.data = (char **)malloc(sizeof(char *) * argc);
}

void		tab_distrib(t_argtab *tab, int get, char *argv)
{
	if (get == 1)
	{
		ft_strcpy(tab->dir.data[tab->dir.size].name, argv);
		lstat(tab->dir.data[tab->dir.size].name,
		&tab->dir.data[tab->dir.size].stats);
		tab->dir.data[tab->dir.size].lnkname[readlink(argv,
		tab->dir.data[tab->dir.size].lnkname, MAXLEN)] = 0;
		tab->dir.size++;
	}
	else if (get == 2)
	{
		ft_strcpy(tab->file.data[tab->file.size].name, argv);
		lstat(tab->file.data[tab->file.size].name,
		&tab->file.data[tab->file.size].stats);
		tab->file.data[tab->file.size].lnkname[readlink(argv,
		tab->file.data[tab->file.size].lnkname, MAXLEN)] = 0;
		tab->file.size++;
	}
}
