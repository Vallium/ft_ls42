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
# include <dirent.h>
# include <unistd.h>
# include <grp.h>
# include <sys/types.h>
# include <pwd.h>
# include <time.h>

typedef struct		s_opt
{
	int				nbarg;
	char			err;
	char			*optstr;
}					t_opt;

typedef struct		s_file
{
	char			name[256];
	char			lnkname[MAXLEN];
	struct stat		stat;
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
	char			**data;
	int				size;
}					t_tab;

typedef struct		s_argtab
{
	t_tab			dir;
	t_tab			file;
	t_tab			error;
}					t_argtab;

int					ft_get_opt(int argc, char **argv, t_opt *opt);
void				usage(void);
void				print_type(int mode);
void				print_rights(int mode);

#endif
