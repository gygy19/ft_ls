/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 07:13:19 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/28 07:13:23 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		put_color_p_dir(char *dir, int flags)
{
	if (flags & FLAG_GG)
		ft_putstr(COLOR_P_DIR);
	ft_putstr(dir);
	if (flags & FLAG_GG)
		ft_putstr(COLOR_END);
	ft_putstr("\n");
}

void		put_color_type(char *dir, char *file, int flags)
{
	char *tmp;

	if (flags & FLAG_GG)
	{
		tmp = ft_strjoin(ft_strjoin(dir, "/"), file);
		if (is_lnk(tmp))
			ft_putstr(COLOR_LNK);
		else if (is_dir(tmp))
			ft_putstr(COLOR_DIR);
	}
	ft_putstr(file);
	if (flags & FLAG_GG)
		ft_putstr(COLOR_END);
	ft_putstr("\n");
}

void		put_color_type_length(char *dir, char *file, int flags)
{
	char *tmp;

	if (flags & FLAG_GG)
	{
		tmp = ft_strjoin(ft_strjoin(dir, "/"), file);
		if (is_lnk(tmp))
			ft_putstr(COLOR_LNK);
		else if (is_dir(tmp))
			ft_putstr(COLOR_DIR);
	}
	ft_putstr(file);
	if (flags & FLAG_GG)
		ft_putstr(COLOR_END);
}
