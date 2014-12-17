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

int		a = 0;
int		l = 0;

void	ft_lst_bbl_sort(t_list *lst, int (*f)(t_file *f1, t_file *f2));

int		file_size_cmp(t_file *f1, t_file *f2)
{
	return(f1->stat.st_size > f2->stat.st_size);
}

int		file_name_cmp(t_file *f1, t_file *f2)
{
	return(ft_strcmp(f1->entree->d_name, f2->entree->d_name) < 0 ? 0 : 1);
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

void	ls_l(char *arg)
{
	DIR*			ptdir;
	t_list			*lst;
	t_file			file;
	struct group	*gp;
	struct passwd	*ps;
	ptdir = opendir(arg);
	lst = NULL;
	arg = arg;
	while((file.entree=readdir(ptdir)) != NULL)
	{
		stat(file.entree->d_name, &file.stat);
		ft_lstadd(&lst, ft_lstnew(&file, sizeof(t_file)));
	}
	ft_lst_bbl_sort(lst, file_name_cmp);
	//ft_lst_bbl_sort(lst, file_date_cmp);

	t_list  *tmp = lst;


	while (tmp)
	{
		file = *((t_file *)tmp->content);
		stat(ft_strjoin(arg, file.entree->d_name), &file.stat);
		gp = getgrgid (file.stat.st_gid);
		ps = getpwuid(file.stat.st_uid);
		print_type(file.stat.st_mode);
		print_rights(file.stat.st_mode);

		printf("\t%d\t%s\t%s\t%llu\t%s\t%s\n",
		file.stat.st_nlink,
		ps->pw_name ,gp->gr_name,
		file.stat.st_size,
		ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
		file.entree->d_name);
		//printf("%s\t\t\t\t\t%llu\n",file.entree->d_name, file.stat.st_size);
		tmp = tmp->next;
	}
	tmp = lst;

	while (tmp)
	{
		file = *((t_file *)tmp->content);
		//ptdir = opendir(file.entree->d_name);

		if (S_ISDIR(file.stat.st_mode) && ft_strcmp(file.entree->d_name, ".") && ft_strcmp(file.entree->d_name, ".."))
		{
			printf("\n-------------\n");
			stat(ft_strjoin(arg, file.entree->d_name), &file.stat);
			gp = getgrgid (file.stat.st_gid);
			ps = getpwuid(file.stat.st_uid);
			print_type(file.stat.st_mode);
			print_rights(file.stat.st_mode);

			printf("\t%d\t%s\t%s\t%llu\t%s\t%s\n",
			file.stat.st_nlink,
			ps->pw_name ,gp->gr_name,
			file.stat.st_size,
			ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
			file.entree->d_name);


			printf("\n\n%s:\n",ft_strjoin(arg, ft_strjoin("/", file.entree->d_name)));
			ls_l(ft_strjoin(arg, ft_strjoin("/", file.entree->d_name)));
		}
		tmp = tmp->next;
	}

	/*

	if (!l)
	{

	}
	else
	{
		while((entree=readdir(ptdir)) != NULL)
			if (a || *entree->d_name != '.')
			{
				stat(ft_strjoin(arg, entree->d_name), &statbuff);
				gp = getgrgid (statbuff.st_gid);
				ps = getpwuid(statbuff.st_uid);
				print_type(statbuff.st_mode);
				print_rights(statbuff.st_mode);

				printf("\t%d\t%s\t%s\t%llu\t%s\t%s\n",
					statbuff.st_nlink,
					ps->pw_name ,gp->gr_name,
					statbuff.st_size,
					ft_strsub(ctime(&statbuff.st_mtimespec.tv_sec), 4, 12),
					entree->d_name);
			}
	}
	*/
}

int		main(int argc, char **argv)
{
	DIR* ptdir;
	char c;
	t_opt opt;

	opt.optstr = "Ralrt";
	opt.nbarg = 1;
	if (argc == 1)
	{
		ls_l(".");
	}
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
			else if (c == 'a')
				a = 1;
		}
		if (argc == opt.nbarg)
		{
			ptdir = opendir("./");
	//		ls_l(ptdir, "./");
		}
		while (opt.nbarg < argc)
		{
			ptdir = opendir(argv[opt.nbarg]);
			printf("%s:\n", argv[opt.nbarg]);
	//		ls_l(argv[opt.nbarg]);
			ft_putchar('\n');
			opt.nbarg++;
		}
	}
	closedir(ptdir);
	return (0);
}
