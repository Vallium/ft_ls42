/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:13:40 by aalliot           #+#    #+#             */
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
long long	total = 0;

void	ft_lst_bbl_sort(t_list *lst, int (*f)(t_file *f1, t_file *f2));

int		file_size_cmp(t_file *f1, t_file *f2)
{
	return(f1->stat.st_size > f2->stat.st_size);
}

int		file_name_cmp(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f1->name, f2->name) < 0 ? 0 : 1);
}

int		file_r_name_cmp(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f1->name, f2->name) > 0 ? 0 : 1);
}

int		file_time_cmp(t_file *f1, t_file *f2)
{
	#ifdef __APPLE__
	if (f1->stat.st_mtimespec.tv_sec == f2->stat.st_mtimespec.tv_sec)
		return (f1->stat.st_mtimespec.tv_nsec < f2->stat.st_mtimespec.tv_nsec);
	return (f1->stat.st_mtimespec.tv_sec < f2->stat.st_mtimespec.tv_sec);
	#else
	return (f1->stat.st_mtime < f2->stat.st_mtime);
	#endif
}

int		file_r_time_cmp(t_file *f1, t_file *f2)
{
	#ifdef __APPLE__
	if (f1->stat.st_mtimespec.tv_sec == f2->stat.st_mtimespec.tv_sec)
		return (f1->stat.st_mtimespec.tv_nsec > f2->stat.st_mtimespec.tv_nsec);
	return (f1->stat.st_mtimespec.tv_sec > f2->stat.st_mtimespec.tv_sec);
	#else
	return (f1->stat.st_mtime > f2->stat.st_mtime);
	#endif
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

	if (l)
	{
		if (a || *file.name != '.')
		{
			gp = getgrgid(file.stat.st_gid);
			ps = getpwuid(file.stat.st_uid);

			print_type(file.stat.st_mode);
			print_rights(file.stat.st_mode);

			printf(" %3d %1s %6s %6llu %s %s\n",
				(int)file.stat.st_nlink,
				ps->pw_name ,gp->gr_name,
				(long long unsigned int)file.stat.st_size,
			#ifdef __APPLE__
				ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
			#else
				ft_strsub(ctime(&file.stat.st_mtime), 4, 12),
			#endif
				file.name);
		}
	}
	else
	{
		if (a || *file.name != '.')
			printf("%s\n", file.name);
	}
}

void	ls_l(char *arg, char *dir)
{
	//printf("LS_L(%s);\n", arg);
	DIR*			ptdir;
	t_list			*lst;
	t_file			file;
	t_list			*tmp;
	struct dirent	*entree;

	if (!(ptdir = opendir(arg)))
	{
		ft_putstr_fd("ls: ", 2);
		perror(dir);
		return;
	}
	lst = NULL;

	while ((entree = readdir(ptdir)) != NULL) //stockage liste
	{
		ft_strcpy(file.name, entree->d_name);

		lstat(ft_strjoin(arg, ft_strjoin("/", entree->d_name)), &file.stat);
		if (!r)
			ft_lstsmartpushback(&lst, ft_lstnew(&file, sizeof(t_file)));
		else
			ft_lstadd(&lst, ft_lstnew(&file, sizeof(t_file)));
		total += file.stat.st_blocks;
	}

	if (!r)
		ft_lst_bbl_sort(lst, file_name_cmp);
	else
		ft_lst_bbl_sort(lst, file_r_name_cmp);


	if (t)
	{
		if (!r)
			ft_lst_bbl_sort(lst, file_time_cmp);
		else
			ft_lst_bbl_sort(lst, file_r_time_cmp);
	}

	tmp = lst;
	if (l)
		printf("total %llu\n", total);//affiche total mais bug quand il y a un symbolic link
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
		if (a || *file.name != '.')
			if (R && S_ISDIR(file.stat.st_mode) && ft_strcmp(file.name, ".") && ft_strcmp(file.name, ".."))
			{
				total = 0;
				printf("\n%s:\n",ft_strjoin(arg, ft_strjoin( "/", file.name)));
				ls_l(ft_strjoin(arg, ft_strjoin( "/", file.name)), file.name);
			}
		tmp = tmp->next;
	}
	closedir(ptdir);
//	ft_lstdel(&lst, delete);
}

int		main(int argc, char **argv)
{
	char c;
	t_opt opt;

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
			ls_l(".", ".");
		while (opt.nbarg < argc)
		{
			ls_l(argv[opt.nbarg], argv[opt.nbarg]);
			ft_putchar('\n');
			opt.nbarg++;
		}
	}
	return (0);
}
