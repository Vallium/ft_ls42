/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 16:47:55 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/16 16:47:57 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			ft_swap_char(char *c1, char *c2)
{
	char		tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}