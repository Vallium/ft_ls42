/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:14:55 by adoussau          #+#    #+#             */
/*   Updated: 2014/12/13 12:36:53 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# define MAXLEN 1024

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <unistd.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

int		g_a;
int		g_l;
int		g_re;
int		g_r;
int		g_t;
int		g_p;
int		g_ss;

typedef struct		s_opt
{
	int				nb;
	char			err;
	char			*optstr;
}					t_opt;

typedef struct		s_file
{
	char			name[256];
	char			lnkname[MAXLEN];
	struct stat		stats;
}					t_file;

typedef struct		s_print
{
	int				gp_len;
	int				ps_len;
	int				name_len;
	int				size_len;
	int				link_len;
	int				tmp;
	struct group	*gp;
	struct passwd	*ps;
}					t_print;

typedef struct		s_llu
{
	int				i;
	int				size;
	long long		total;
}					t_llu;

typedef struct		s_tab
{
	t_file			*data;
	t_file			**ptr;
	int				size;
}					t_tab;

typedef struct		s_tab2
{
	char			**data;
	int				size;
}					t_tab2;

typedef struct		s_argtab
{
	t_tab			dir;
	t_tab			file;
	t_tab2			error;
}					t_argtab;

int					file_name_cmp(void *ptr1, void *ptr2);
int					file_r_name_cmp(void *ptr1, void *ptr2);
int					file_time_cmp(void *ptr1, void *ptr2);
int					file_r_time_cmp(void *ptr1, void *ptr2);
int					file_size_cmp(void *ptr1, void *ptr2);
int					file_r_size_cmp(void *ptr1, void *ptr2);
int					arg_cmp(void *na1, void *na2);

int					ft_get_opt(int argc, char **argv, t_opt *opt);
void				get_opt_assi(int argc, char **argv, t_opt *opt);
int					get_types(char *arg);
void				usage(void);

void				print_type(int mode);
void				print_rights(int mode);
void				print_total(t_llu *llu);
void				print_date(t_file *file);
void				print_acl_attr(t_file **file, int i, char *arg);
void				print(t_file **file, t_print *prt, int i, char *arg);
void				printfilelist(t_file **file, int size, char *arg);
void				print_error(t_argtab tab);

void				tab_init(t_argtab *tab, int argc);
void				tab_distrib(t_argtab *tab, int get, char *argv);
void				tab_fill(t_argtab *tab, int argc, char *argv[]);
void				tab_sort(t_argtab *tab);
void				arg_to_tab(int argc, char *argv[]);
void				tab_free(t_argtab *tab);
int					fill_tab(t_file ***tab, char *arg, t_llu *llu);
void				sort_tab(t_file ***tab, t_llu *llu);

int					ft_intlen(int i);
int					ft_llilen(long long int i);

void				to_wedge(const char *str, int n);
void				to_wedge2(const char *str, int n);
void				to_wedge_lli2(long long int nb, int n);
void				to_wedge_lli(long long int nb, int n);

void				fill_prt(t_file **file, t_print *prt, int i);
void				prt_init(t_print *prt);

void				ls_l(char *arg);
t_file				**lst2tab(t_list **lst, int *size);
void				free_ls(t_file **tab, t_llu *llu);
void				ls_mult_arg(char *argv, int i);

#endif
