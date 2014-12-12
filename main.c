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

void		usage(void)
{
	ft_putstr_fd("usage: ft_ls [-Ralrt][file ...]\n", 2);
}

void ls_a(DIR* ptdir)
{
	struct dirent* entree;
	while((entree=readdir(ptdir))!= NULL)
		printf("%s\n", entree->d_name);
}

int			main(int argc, char **argv)
{
	DIR* ptdir;
	//struct stat buff;
	//struct dirent* entree;
	if (argc == 1)
		ptdir = opendir(".");
	else
		ptdir = opendir(argv[1]);

	ls_a(ptdir);
	/*printf("%d\n",stat("main.c", &buff));
	printf("%d %d\n",buff.st_size, buff.st_gid);*/
	closedir(ptdir);
	return (0);
}
