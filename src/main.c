/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:13:40 by adoussau          #+#    #+#             */
/*   Updated: 2014/12/20 20:52:42 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <stdlib.h>

int		a = 0;
int		l = 0;
int		R = 0;
int		r = 0;
int		t = 0;

int		ft_intlen(int i)
{
	int ret;

	ret = 1;
	while (i /= 10)
		ret++;
	return (ret);
}

int		ft_llilen(long long int i)
{
	int ret;

	ret = 1;
	while (i /= 10)
		ret++;
	return (ret);
}

void	to_wedge(const char *str, int n)
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

void	to_wedge2(const char *str, int n)
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

void	to_wedge_lli2(long long int nb, int n)
{
	int		l;

	l = ft_llilen(nb);
	ft_putnbrll(nb);
	while (l++ < n)
		ft_putchar(' ');
}

void	to_wedge_lli(long long int nb, int n)
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

int		file_size_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	if (f1->stat.st_size > f2->stat.st_size)
		return (1);
	else if (f1->stat.st_size < f2->stat.st_size)
		return (-1);
	return (0);
}

int		file_name_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	return (ft_strcmp(f1->name, f2->name));
}

int		file_r_name_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	return (ft_strcmp(f2->name, f1->name));
}

int		file_time_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	if (f1->stat.st_mtimespec.tv_sec == f2->stat.st_mtimespec.tv_sec)
		return (f1->stat.st_mtimespec.tv_nsec - f2->stat.st_mtimespec.tv_nsec);
	return (f1->stat.st_mtimespec.tv_sec - f2->stat.st_mtimespec.tv_sec);
}

int		file_r_time_cmp(void *ptr1, void *ptr2)
{
	t_file *f1;
	t_file *f2;

	f1 = (t_file *)ptr1;
	f2 = (t_file *)ptr2;
	if (f1->stat.st_mtimespec.tv_sec == f2->stat.st_mtimespec.tv_sec)
		return (f2->stat.st_mtimespec.tv_nsec - f1->stat.st_mtimespec.tv_nsec);
	return (f2->stat.st_mtimespec.tv_sec - f1->stat.st_mtimespec.tv_sec);
}

void	usage(void)
{
	ft_putstr_fd("usage: ft_ls [-Ralrt][file ...]\n", 2);
}

void	print_type(int mode)
{
	if (S_ISDIR(mode))
		ft_putchar('d');
	else if (S_ISREG(mode))
		ft_putchar('-');
	else if (S_ISLNK(mode))
		ft_putchar('l');
	else if (S_ISSOCK(mode))
		ft_putchar('s');
	else if (S_ISFIFO(mode))
		ft_putchar('p');
	else if (S_ISCHR(mode))
		ft_putchar('c');
	else if (S_ISBLK(mode))
		ft_putchar('b');
}

void	print_rights(int mode)
{
	ft_putchar((mode & 0400) ? 'r' : '-');
	ft_putchar((mode & 0200) ? 'w' : '-');
	ft_putchar((mode & 0100) ? 'x' : '-');
	ft_putchar((mode & 040) ? 'r' : '-');
	ft_putchar((mode & 020) ? 'w' : '-');
	ft_putchar((mode & 010) ? 'x' : '-');
	ft_putchar((mode & 04) ? 'r' : '-');
	ft_putchar((mode & 02) ? 'w' : '-');
	ft_putchar((mode & 01) ? 'x' : '-');
}

void	printdate(t_file *file)
{
	if (file->stat.st_mtimespec.tv_sec > time(0) - 15778463)
		ft_putstr_sub(ctime(&file->stat.st_mtimespec.tv_sec), 4, 12);
	else
		ft_putstr_sub(ctime(&file->stat.st_mtimespec.tv_sec), 4, 7),
		ft_putchar(' '),
		ft_putstr_sub(ctime(&file->stat.st_mtimespec.tv_sec), 20, 4);
}

void	fill_prt(t_file **file, t_print *prt, int i)
{
	prt->gp = getgrgid(file[i]->stat.st_gid);
	prt->ps = getpwuid(file[i]->stat.st_uid);
	prt->tmp = ft_intlen(file[i]->stat.st_nlink);
	if (prt->tmp > prt->link_len)
		prt->link_len = prt->tmp;
	prt->tmp = ft_strlen(file[i]->name);
	if (prt->tmp > prt->name_len)
		prt->name_len = prt->tmp;
	if (prt->ps)
		prt->tmp = ft_strlen(prt->ps->pw_name);
	else
		prt->tmp = ft_intlen(file[i]->stat.st_uid);
	if (prt->tmp > prt->ps_len)
		prt->ps_len = prt->tmp;
	if (prt->gp)
		prt->tmp = ft_strlen(prt->gp->gr_name);
	else
		prt->tmp = ft_intlen(file[i]->stat.st_gid);
	if (prt->tmp > prt->ps_len)
		prt->gp_len = prt->tmp;
	prt->tmp = ft_intlen(file[i]->stat.st_size);
	if (prt->tmp > prt->size_len)
		prt->size_len = prt->tmp;
}

void			print(t_file **file, t_print *prt, int i)
{
	print_type(file[i]->stat.st_mode);
	print_rights(file[i]->stat.st_mode);
	ft_putstr("  ");
	to_wedge_lli(file[i]->stat.st_nlink, prt->link_len);
	ft_putchar(' ');
	if (prt->ps)
		to_wedge2(prt->ps->pw_name, prt->ps_len);
	else
		to_wedge_lli2(file[i]->stat.st_uid, prt->ps_len);
	ft_putstr("  ");
	if (prt->gp)
		to_wedge2(prt->gp->gr_name, prt->gp_len);
	else
		to_wedge_lli2(file[i]->stat.st_gid, prt->gp_len);
	ft_putstr("  ");
	to_wedge_lli(file[i]->stat.st_size, prt->size_len);
	ft_putchar(' ');
	printdate(file[i]);
	ft_putchar(' ');
	ft_putstr(file[i]->name);
	if (S_ISLNK(file[i]->stat.st_mode))
		ft_putstr(" -> "),
		ft_putstr(file[i]->lnkname);
	ft_putchar('\n');
}

void			prt_init(t_print *prt)
{
	prt->gp_len = 0;
	prt->ps_len = 0;
	prt->name_len = 0;
	prt->size_len = 0;
	prt->link_len = 0;
}

void			printfilelist(t_file **file, int size)
{
	int			i;
	t_print		prt;

	prt_init(&prt);
	i = 0;
	if (!l)
	{
		while (i++ < size)
			if (a || *file[i - 1]->name != '.')
				ft_putstr(file[i - 1]->name),
				ft_putchar('\n');
	}
	else
	{
		while (i++ < size)
			if (a || *file[i - 1]->name != '.')
				fill_prt(file, &prt, i - 1);
		i = 0;
		while (i++ < size)
			if (a || *file[i - 1]->name != '.')
				prt.gp = getgrgid(file[i - 1]->stat.st_gid),
				prt.ps = getpwuid(file[i - 1]->stat.st_uid),
				print(file, &prt, i - 1);
	}
}

t_file			**lst2tab(t_list **lst, int *size)
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

void				ls_l(char *arg, char *dir)
{
	DIR				*ptdir;
	t_list			*lst;
	t_file			file;
	int				size;
	struct dirent	*entree;
	long long		total;
	t_file			**tab;
	int				i;

	i = 0;
	total = 0;
	if (!(ptdir = opendir(arg)))
	{
		ft_putstr_fd("ls: ", 2);
		perror(dir);
		return ;
	}
	lst = NULL;
	while ((entree = readdir(ptdir)) != NULL)
	{
		ft_strcpy(file.name, entree->d_name);
		lstat(ft_burger(arg, '/', entree->d_name), &file.stat);
		readlink(ft_burger(arg, '/', entree->d_name), file.lnkname, MAXLEN);
		if (!r)
			ft_lstsmartpushback(&lst, ft_lstnew(&file, sizeof(t_file)));
		else
			ft_lstadd(&lst, ft_lstnew(&file, sizeof(t_file)));
		if (a || *file.name != '.')
			total += file.stat.st_blocks;
	}
	size = 0;
	tab = lst2tab(&lst, &size);
	if (!r)
		ft_sort_qck((void **)tab, size, file_name_cmp);
	else
		ft_sort_qck((void **)tab, size, file_r_name_cmp);
	if (t)
	{
		if (!r)
			ft_sort_qck((void **)tab, size, file_time_cmp);
		else
			ft_sort_qck((void **)tab, size, file_r_time_cmp);
	}
	if (l)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	printfilelist(tab, size);
	while (i < size)
	{
		file = *((t_file *)tab[i]);
		if (a || *file.name != '.')
			if (R && S_ISDIR(file.stat.st_mode) && ft_strcmp(file.name, ".")
				&& ft_strcmp(file.name, ".."))
			{
				total = 0;
				printf("\n%s:\n", ft_burger(arg, '/', file.name));
				ls_l(ft_burger(arg, '/', file.name), file.name);
			}
		i++;
	}
	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
	closedir(ptdir);
	ft_lstsimpledel(&lst);
}

int				arg_cmp(void *na1, void *na2)
{
	return (ft_strcmp(na1, na2));
}

int				main(int argc, char **argv)
{
	char			c;
	t_opt			opt;

	opt.optstr = "Ralrt";
	opt.nbarg = 1;
	if (argc == 1)
		ls_l(".", ".");
	else
	{
		while ((c = ft_get_opt(argc, argv, &opt)) > 0)
		{
			if (c == '?')
			{
				printf("ft_ls: illegal option -- %c\n", opt.err);
				usage();
				return (0);
			}
			if (c == 'l')
				l = 1;
			else if (c == 'R')
				R = 1;
			else if (c == 'a')
				a = 1;
			else if (c == 'r')
				r = 1;
			else if (c == 't')
				t = 1;
		}
		if (argc == opt.nbarg)
		{
			ls_l(".", ".");
			return (0);
		}
		ft_sort_qck((void **)argv + opt.nbarg, argc - 1 - opt.nbarg, arg_cmp);
		if (opt.nbarg + 1 == argc)
			ls_l(argv[opt.nbarg], argv[opt.nbarg]);
		else
		{
			while (opt.nbarg < argc - 1)
			{
				ft_putstr(argv[opt.nbarg]);
				ft_putstr(":\n");
				ls_l(argv[opt.nbarg], argv[opt.nbarg]);
				ft_putchar('\n');
				opt.nbarg++;
			}
			ft_putstr(argv[opt.nbarg]);
			ft_putstr(":\n");
			ls_l(argv[opt.nbarg], argv[opt.nbarg]);
		}
	}
	return (0);
}
