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

void	ls_l(DIR* ptdir)
{
	struct dirent* entree;
	struct stat statbuff;
	struct group *gp;
	struct passwd *ps;

	if (!l)
	{
		while((entree=readdir(ptdir)) != NULL)
			if (a || *entree->d_name != '.')
				printf("%s\n", entree->d_name);
	}
	else
	{
		while((entree=readdir(ptdir)) != NULL)
			if (a || *entree->d_name != '.')
			{
				stat(entree->d_name, &statbuff);
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
		ptdir = opendir(".");
		ls_l(ptdir);
	}
	else
	{
		while ((c = ft_get_opt(argc, argv, &opt)) > 0)
		{
			if (c == 'l')
				l = 1;
			else if (c == 'a')
				a = 1;
		}
		if (argc == opt.nbarg)
		{
			ptdir = opendir(".");
			ls_l(ptdir);
		}
		while (opt.nbarg < argc)
		{
			ptdir = opendir(argv[opt.nbarg]);
			printf("%s:\n", argv[opt.nbarg]);
			ls_l(ptdir);
			ft_putchar('\n');
			opt.nbarg++;
		}
	}
	//ls_l(ptdir);
	closedir(ptdir);
	return (0);
}
