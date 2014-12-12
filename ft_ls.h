/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 11:14:55 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/12 10:56:50 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

#include "libft/includes/get_next_line.h"

typedef struct		s_opt
{
	int				nbarg;
	char			*optstr;

}					t_opt;

int		ft_get_opt(int argc, char **argv, t_opt opt);

#endif
