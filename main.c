/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:13:40 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/13 12:36:39 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <stdlib.h>

int		a = 0;
int		l = 0;
int		R = 0;

void	ft_lst_bbl_sort(t_list *lst, int (*f)(t_file *f1, t_file *f2));

int		file_size_cmp(t_file *f1, t_file *f2)
{
	return(f1->stat.st_size > f2->stat.st_size);
}

int		file_name_cmp(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f1->name, f2->name) < 0 ? 0 : 1);
}

int		file_date_cmp(t_file *f1, t_file *f2)
{
	if (f1->stat.st_mtimespec.tv_sec == f2->stat.st_mtimespec.tv_sec)
		return (f1->stat.st_mtimespec.tv_nsec < f2->stat.st_mtimespec.tv_nsec);
	return (f1->stat.st_mtimespec.tv_sec < f2->stat.st_mtimespec.tv_sec);
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


void	printFile(t_file file)
{
	struct group	*gp;
	struct passwd	*ps;

	gp = getgrgid(file.stat.st_gid);
	ps = getpwuid(file.stat.st_uid);
	print_type(file.stat.st_mode);
	print_rights(file.stat.st_mode);

	printf("\t%d\t%s\t%s\t%llu\t%s\t%s\n",
		file.stat.st_nlink,
		ps->pw_name ,gp->gr_name,
		file.stat.st_size,
		ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
		file.name);
}

void			delete(void *a, size_t sz)
{
	t_file		*file;

	(void)sz;
	file = (t_file*)a;
}

void	ls_l(char *arg)
{
	//printf("LS_L(%s);\n", arg);
	DIR*			ptdir;
	t_list			*lst;
	t_file			file;
	t_list			*tmp;
	struct dirent	*entree;

	ptdir = opendir(arg);
	lst = NULL;

	while ((entree = readdir(ptdir)) != NULL) //stockage liste
	{
		ft_strcpy(file.name, entree->d_name);

		stat(ft_strjoin(arg, ft_strjoin("/", entree->d_name)), &file.stat);
		ft_lstsmartpushback(&lst, ft_lstnew(&file, sizeof(t_file)));
	}

	ft_lst_bbl_sort(lst, file_name_cmp);

	tmp = lst;

	while (tmp) // affiche le contenu de la liste
	{
		file = *((t_file *)tmp->content);
		printFile(file);

		tmp = tmp->next;
	}

	tmp = lst;

	while (tmp) //recursivitee si ss/dossiers
	{
		file = *((t_file *)tmp->content);
		if (S_ISDIR(file.stat.st_mode) && ft_strcmp(file.name, ".") && ft_strcmp(file.name, ".."))
		{
			printf("\n%s:\n",ft_strjoin(arg, ft_strjoin( "/", file.name)));
			ls_l(ft_strjoin(arg, ft_strjoin( "/", file.name)));
		}
		tmp = tmp->next;
	}
//	ft_lstdel(&lst, delete);
}

int		main(int argc, char **argv)
{
	char c;
	t_opt opt;

	opt.optstr = "Ralrt";
	opt.nbarg = 1;

	if (argc == 1)
		ls_l(".");

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
		}
		if (argc == opt.nbarg)
			ls_l(".");
		while (opt.nbarg < argc)
		{
			ls_l(argv[opt.nbarg]);
			ft_putchar('\n');
			opt.nbarg++;
		}
	}
	return (0);
}
