/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:14:55 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/13 12:36:53 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# define MAXLEN 1024

#include "libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <grp.h>
//#include <uuid/uuid.h>
#include <sys/types.h>
#include <pwd.h>
//#include <uuid/uuid.h>
#include <time.h>

typedef struct			s_opt
{
	int					nbarg;
	char				err;
	char				*optstr;
}						t_opt;

typedef struct			s_file
{
	char				name[256];
	char				lnkname[MAXLEN];
	struct stat			stat;
}						t_file;

int						ft_get_opt(int argc, char **argv, t_opt *opt);
void					usage(void);
void					print_type(int mode);
void					print_rights(int mode);

#endif
