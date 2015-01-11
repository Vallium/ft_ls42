/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 19:16:08 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/07 19:16:12 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		printfilelist(t_file **file, int size, char *arg)
{
	int			i;
	t_print		prt;

	prt_init(&prt);
	i = 0;
	if (!g_l)
		while (i++ < size)
		{
			ft_putstr(file[i - 1]->name);
			if (g_p && S_ISDIR(file[i - 1]->stats.st_mode))
				ft_putchar('/');
			ft_putchar('\n');
		}
	else
	{
		while (i++ < size)
			fill_prt(file, &prt, i - 1);
		i = 0;
		while (i++ < size)
		{
			prt.gp = getgrgid(file[i - 1]->stats.st_gid);
			prt.ps = getpwuid(file[i - 1]->stats.st_uid);
			print(file, &prt, i - 1, arg);
		}
	}
}

void		print_total(t_llu *llu)
{
	if (g_l && llu->size)
	{
		ft_putstr("total ");
		ft_putnbr(llu->total);
		ft_putchar('\n');
	}
}

void		print_error(t_argtab tab)
{
	int			i;

	i = 0;
	while (i < tab.error.size)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(tab.error.data[i], 2);
		ft_putendl_fd(": No such file or directory", 2);
		i++;
	}
	free(tab.error.data);
}

void		prt_init(t_print *prt)
{
	prt->gp_len = 0;
	prt->ps_len = 0;
	prt->name_len = 0;
	prt->size_len = 0;
	prt->link_len = 0;
	prt->maj_len = 0;
	prt->min_len = 0;
	prt->dev = 0;
}

void		fill_prt(t_file **file, t_print *prt, int i)
{
	prt->gp = getgrgid(file[i]->stats.st_gid);
	prt->ps = getpwuid(file[i]->stats.st_uid);
	prt->tmp = ft_intlen(file[i]->stats.st_nlink);
	if (prt->tmp > prt->link_len)
		prt->link_len = prt->tmp;
	prt->tmp = ft_strlen(file[i]->name);
	if (prt->tmp > prt->name_len)
		prt->name_len = prt->tmp;
	if (prt->ps)
		prt->tmp = ft_strlen(prt->ps->pw_name);
	else
		prt->tmp = ft_intlen(file[i]->stats.st_uid);
	if (prt->tmp > prt->ps_len)
		prt->ps_len = prt->tmp;
	if (prt->gp)
		prt->tmp = ft_strlen(prt->gp->gr_name);
	else
		prt->tmp = ft_intlen(file[i]->stats.st_gid);
	if (prt->tmp > prt->gp_len)
		prt->gp_len = prt->tmp;
	if (S_ISCHR(file[i]->stats.st_mode) || S_ISBLK(file[i]->stats.st_mode))
	{
		prt->dev = 1;
		prt->tmp = ft_intlen(major(file[i]->stats.st_rdev));
		prt->maj_len = (prt->tmp > prt->maj_len ? prt->tmp : prt->maj_len);
		prt->tmp = ft_intlen(minor(file[i]->stats.st_rdev));
		prt->min_len = (prt->tmp > prt->min_len ? prt->tmp : prt->min_len);
		prt->tmp = prt->maj_len + prt->min_len + 2;
	}
	else
		prt->tmp = ft_intlen(file[i]->stats.st_size);
	if (prt->tmp > prt->size_len)
		prt->size_len = prt->tmp;
}
