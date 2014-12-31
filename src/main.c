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

void swap(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	   sort(void **tab, int bg, int ed, int (*f)(void *, void *))
{
	void		*pvt = tab[bg];
	int			lft;
	int			rgt;

	lft = bg - 1;
	rgt = ed + 1;
	if (bg >= ed)
		return ;
	while (1)
	{
		while (f(tab[--rgt], pvt) > 0)
			;
		while (f(tab[++lft], pvt) < 0)
			;
		if (lft < rgt)
			swap(&tab[lft], &tab[rgt]);
		else
			break ;
	}
	sort(tab, bg, rgt, f);
	sort(tab, rgt + 1, ed, f);
}

void	   ft_q_sort(void **tab, size_t size, int (*f)(void *, void *))
{
	sort(tab, 0, size - 1, f);
}

void	ft_bbl2_sort(void **tab, int size, int (*f)(void *f1, void *f2))
{
	int			i;
	int		    end;

	end = 0;

	while (!end)
	{
		//printf("Alive\n");
		end = 1;
		i = 0;
		while (i < (size- 1))
		{
			if (f(tab[i], tab[i + 1]))
			{
				swap(&tab[i], &tab[i + 1]);
				end = 0;
			}
			i++;
		}
	}
}

int		file_size_cmp(void *ptr1, void *ptr2)
{
	t_file *f1 = (t_file *)ptr1;
	t_file *f2 = (t_file *)ptr2;
	if (f1->stat.st_size > f2->stat.st_size)
		return (1);
	else if (f1->stat.st_size < f2->stat.st_size)
		return (-1);
	return (0);
}

int		file_name_cmp(void *ptr1, void *ptr2)
{
	t_file *f1 = (t_file *)ptr1;
	t_file *f2 = (t_file *)ptr2;
	return(ft_strcmp(f1->name, f2->name));
}

int		file_r_name_cmp(void *ptr1, void *ptr2)
{
	t_file *f1 = (t_file *)ptr1;
	t_file *f2 = (t_file *)ptr2;
	return(ft_strcmp(f2->name, f1->name));
}

int		file_time_cmp(void *ptr1, void *ptr2)
{
	t_file *f1 = (t_file *)ptr1;
	t_file *f2 = (t_file *)ptr2;
#ifdef __APPLE__
	if (f1->stat.st_mtimespec.tv_sec == f2->stat.st_mtimespec.tv_sec)
		return (f1->stat.st_mtimespec.tv_nsec - f2->stat.st_mtimespec.tv_nsec);
	return (f1->stat.st_mtimespec.tv_sec - f2->stat.st_mtimespec.tv_sec);
#else
	return (f1->stat.st_mtime - f2->stat.st_mtime);
#endif
}

int		file_r_time_cmp(void *ptr1, void *ptr2)
{
	t_file *f1 = (t_file *)ptr1;
	t_file *f2 = (t_file *)ptr2;
#ifdef __APPLE__
	if (f1->stat.st_mtimespec.tv_sec == f2->stat.st_mtimespec.tv_sec)
		return (f2->stat.st_mtimespec.tv_nsec - f1->stat.st_mtimespec.tv_nsec);
	return (f2->stat.st_mtimespec.tv_sec - f1->stat.st_mtimespec.tv_sec);
#else
	return (f2->stat.st_mtime - f1->stat.st_mtime);
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
		ft_putchar('b');               //stickybit fonction S_ISVTX
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

			if (!ps)
			{
				if (!gp)
				{
					printf(" %3d %10d %10d %6llu %s %s\n",
						(int)file.stat.st_nlink,
						file.stat.st_uid,
						file.stat.st_gid,
						(long long unsigned int)file.stat.st_size,
						#ifdef __APPLE__
						ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
						#else
						ft_strsub(ctime(&file.stat.st_mtime), 4, 12),
						#endif
						file.name);
				}
				else
				{
					printf(" %3d %10d %6s %6llu %s %s\n",
						(int)file.stat.st_nlink,
						file.stat.st_uid,
						gp->gr_name,
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
				if (!gp)
				{
					printf(" %3d %10s %6d %6llu %s %s\n",
						(int)file.stat.st_nlink,
						ps->pw_name,
						file.stat.st_gid,
						(long long unsigned int)file.stat.st_size,
						#ifdef __APPLE__
						ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
						#else
						ft_strsub(ctime(&file.stat.st_mtime), 4, 12),
						#endif
						file.name);
				}
				else
				{
					if (!S_ISLNK(file.stat.st_mode))
						printf(" %3d %10s %6s %6llu %s %s\n",
							(int)file.stat.st_nlink,
							ps->pw_name,
							gp->gr_name,
							(long long unsigned int)file.stat.st_size,
							#ifdef __APPLE__
							ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
							#else
							ft_strsub(ctime(&file.stat.st_mtime), 4, 12),
							#endif
							file.name);
					else
						printf(" %3d %10s %6s %6llu %s %s -> %s\n",
							(int)file.stat.st_nlink,
							ps->pw_name,
							gp->gr_name,
							(long long unsigned int)file.stat.st_size,
							#ifdef __APPLE__
							ft_strsub(ctime(&file.stat.st_mtimespec.tv_sec), 4, 12),
							#else
							ft_strsub(ctime(&file.stat.st_mtime), 4, 12),
							#endif
							file.name, file.lnkname);
				}
			}
		}
	}
	else
	{
		if (a || *file.name != '.')
			printf("%s\n", file.name);
	}
}

t_file **lst2tab(t_list **lst, int *size)
{
	t_list *tmp = *lst;
	*size = 0;
	t_file **tab;

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
	ft_lstsimpledel(lst); // free
	return (tab);
}

void	ls_l(char *arg, char *dir)
{
	printf("LS_L(%s, %s);\n", arg, dir);
	DIR*			ptdir;
	t_list			*lst;
	t_file			file;
	struct dirent	*entree;
	long long		total;
	//int				test;

	total = 0;
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

		lstat(ft_strjoin(arg, ft_strjoin("/", entree->d_name)), &file.stat); //print slnk
		readlink(ft_strjoin(arg, ft_strjoin("/", entree->d_name)), file.lnkname, MAXLEN);

		if (!r)
			ft_lstsmartpushback(&lst, ft_lstnew(&file, sizeof(t_file)));
		else
			ft_lstadd(&lst, ft_lstnew(&file, sizeof(t_file)));
		if (a || *file.name != '.')
			total += file.stat.st_blocks;
	}

	int size;
	t_file	**tab;

	size = 0;
	tab = lst2tab(&lst, &size);

	if (!r)
		ft_q_sort((void **)tab, size, file_name_cmp);
	else
		ft_q_sort((void **)tab, size, file_r_name_cmp);


	if (t)
	{
		if (!r)
			ft_q_sort((void **)tab, size, file_time_cmp);
		else
			ft_q_sort((void **)tab, size, file_r_time_cmp);
	}
	if (l)
		printf("total %llu\n", total);  //affiche total mais bug quand il y a un symbolic link

	int i = 0;
	while (i < size) // affiche le contenu de la liste
	{
		file = *((t_file *)tab[i]);
		printFile(file);
		i++;
	}

	i = 0;
	while (i < size) //recursivitee si ss/dossiers
	{
		file = *((t_file *)tab[i]);
		if (a || *file.name != '.')
			if (R && S_ISDIR(file.stat.st_mode) && ft_strcmp(file.name, ".") && ft_strcmp(file.name, ".."))
			{
				total = 0;
				printf("\n%s:\n",ft_strjoin(arg, ft_strjoin( "/", file.name)));
				ls_l(ft_strjoin(arg, ft_strjoin( "/", file.name)), file.name);
			}
		i++;
	}
	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
	closedir(ptdir);
//	ft_lstdel(&lst, delete);
}

int		arg_cmp(void *na1, void *na2)
{
	return(ft_strcmp(na1, na2));
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
		{
			ls_l(".", ".");
			return (0);
		}
		sort((void **)argv, opt.nbarg, argc - 1, arg_cmp);
		if (opt.nbarg + 1 == argc)
			ls_l(argv[opt.nbarg], argv[opt.nbarg]);
		else
		{
			while (opt.nbarg < argc - 1)
			{
				ls_l(argv[opt.nbarg], argv[opt.nbarg]);
				ft_putchar('\n');
				opt.nbarg++;
			}
			ls_l(argv[opt.nbarg], argv[opt.nbarg]);
		}
	}
	return (0);
}
