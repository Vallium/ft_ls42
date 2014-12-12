/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:13:40 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/12 12:46:14 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <time.h>


int		a = 0;
int		l = 0;

void	usage(void)
{
	ft_putstr_fd("usage: ft_ls [-Ralrt][file ...]\n", 2);
}

void	ls_l(DIR* ptdir)
{
	struct dirent* entree;
	struct stat statbuff;
	struct group *gp;
	struct passwd *ps;

	if (!l)
	{
		while((entree=readdir(ptdir))!= NULL)
			if (a || *entree->d_name != '.')
				printf("%s\n", entree->d_name);
	}
	else
	{
		while((entree=readdir(ptdir))!= NULL)
			if (a || *entree->d_name != '.')
			{
				stat(entree->d_name, &statbuff);
				gp = getgrgid (statbuff.st_gid);
				ps = getpwuid(statbuff.st_uid);

				printf("drwxrwxrwx\t%d\t%s\t%s\t%llu\t%s\t%s\n",
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

	if (argc == 1)
		ptdir = opendir(".");
	else
	{
		while ((c = ft_get_opt(argc, argv, "la")) > 0)
		{
			if (c == 'l')
				l = 1;
			else if (c == 'a')
				a = 1;
		}
		ptdir = opendir(".");
	}

	ls_l(ptdir);

	/*printf("%d\n",stat("main.c", &buff));
	printf("%d %d\n",buff.st_size, buff.st_gid);*/
	closedir(ptdir);
	return (0);
}
