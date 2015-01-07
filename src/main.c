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

int		g_a = 0;
int		g_l = 0;
int		g_re = 0;
int		g_r = 0;
int		g_t = 0;

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

void		usage(void)
{
	ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
}

void		print_type(int mode)
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

void		print_rights(int mode)
{
	ft_putchar((mode & 0400) ? 'r' : '-');
	ft_putchar((mode & 0200) ? 'w' : '-');
	if (mode & 04000)
		ft_putchar((mode & 0100) ? 's' : 'S');
	else
		ft_putchar((mode & 0100) ? 'x' : '-');
	ft_putchar((mode & 040) ? 'r' : '-');
	ft_putchar((mode & 020) ? 'w' : '-');
	if (mode & 02000)
		ft_putchar((mode & 010) ? 's' : 'S');
	else
		ft_putchar((mode & 010) ? 'x' : '-');
	ft_putchar((mode & 04) ? 'r' : '-');
	ft_putchar((mode & 02) ? 'w' : '-');
	if (mode & 01000)
		ft_putchar((mode & 01) ? 't' : 'T');
	else
		ft_putchar((mode & 01) ? 'x' : '-');
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
	prt->tmp = ft_intlen(file[i]->stats.st_size);
	if (prt->tmp > prt->size_len)
		prt->size_len = prt->tmp;
}

void		print_acl_attr(t_file **file, int i, char *arg)
{
	if (listxattr(ft_burger(arg, '/', file[i]->name), NULL, 256, 1) > 0)
		ft_putstr("@ ");
	else if (acl_get_link_np(ft_burger(arg, '/', file[i]->name),
										ACL_TYPE_EXTENDED))
		ft_putstr("+ ");
	else
		ft_putstr("  ");
}

void		print(t_file **file, t_print *prt, int i, char *arg)
{
	print_type(file[i]->stats.st_mode);
	print_rights(file[i]->stats.st_mode);
	print_acl_attr(file, i, arg);
	to_wedge_lli(file[i]->stats.st_nlink, prt->link_len);
	ft_putchar(' ');
	if (prt->ps)
		to_wedge2(prt->ps->pw_name, prt->ps_len);
	else
		to_wedge_lli2(file[i]->stats.st_uid, prt->ps_len);
	ft_putstr("  ");
	if (prt->gp)
		to_wedge2(prt->gp->gr_name, prt->gp_len);
	else
		to_wedge_lli2(file[i]->stats.st_gid, prt->gp_len);
	ft_putstr("  ");
	to_wedge_lli(file[i]->stats.st_size, prt->size_len);
	ft_putchar(' ');
	print_date(file[i]);
	ft_putchar(' ');
	ft_putstr(file[i]->name);
	if (S_ISLNK(file[i]->stats.st_mode))
		ft_putstr(" -> "),
		ft_putstr(file[i]->lnkname);
	ft_putchar('\n');
}

void		prt_init(t_print *prt)
{
	prt->gp_len = 0;
	prt->ps_len = 0;
	prt->name_len = 0;
	prt->size_len = 0;
	prt->link_len = 0;
}

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

void		free_ls(t_file **tab, t_llu *llu)
{
	llu->i = 0;
	while (llu->i < llu->size)
		free(tab[llu->i++]);
	free(tab);
}

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
	if (g_t)
		ft_sort_qck((void **)*tab, llu->size, !g_r ?
					file_time_cmp : file_r_time_cmp);
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

int			arg_cmp(void *na1, void *na2)
{
	return (ft_strcmp(na1, na2));
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

void		get_opt_assi(int argc, char **argv, t_opt *opt)
{
	char	c;

	opt->optstr = "Ralrt1";
	opt->nb = 1;
	while ((c = ft_get_opt(argc, argv, opt)) > 0)
	{
		if (c == '?')
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2);
			ft_putchar_fd(opt->err, 2);
			ft_putchar_fd('\n', 2);
			usage();
			exit (2);
		}
		if (c == 'l')
			g_l = 1;
		else if (c == 'R')
			g_re = 1;
		else if (c == 'a')
			g_a = 1;
		else if (c == 'r')
			g_r = 1;
		else if (c == 't')
			g_t = 1;
	}
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

int			main(int argc, char **argv)
{
	t_opt			opt;

	if (argc == 1)
		ls_l(".");
	else
	{
		get_opt_assi(argc, argv, &opt);
		if (argc == opt.nb)
		{
			ls_l(".");
			return (0);
		}
		arg_to_tab(argc - opt.nb, argv + opt.nb);
	}
	return (0);
}
