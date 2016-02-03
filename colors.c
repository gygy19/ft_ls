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
	if (ft_strlen(dir) >= 2)
	{
		if (dir[0] == '/' && dir[1] == '/')
			ft_putstr(dir + 1);
		else
			ft_putstr(dir);
	}
	else
		ft_putstr(dir);
	ft_putstr(":");
	if (flags & FLAG_GG)
		ft_putstr(COLOR_END);
	ft_putstr("\n");
}

void		put_pointer_dir(char *infos)
{
	char	*link;
	int		ret;

	ret = 0;
	if (is_lnk(infos))
	{
		if (!(link = (char *)malloc(sizeof(char) * O_DIR)))
			print_error_malloc("[put_pointer_dir] link");
		ft_putstr(" -> ");
		ret = readlink(infos, link, O_DIR);
		link[ret] = '\0';
		ft_putstr(link);
		free(link);
	}
	free(infos);
}

void		put_name_type(char *dir, char *file, int flags)
{
	char *tmp;

	if (flags & FLAG_FF)
	{
		tmp = get_infos(file, dir);
		if (is_lnk(tmp))
			ft_putstr("@");
		else if (is_dir(tmp))
			ft_putstr("/");
		else if (is_exe(tmp))
			ft_putstr("*");
		free(tmp);
	}
}

void		put_color_type(char *dir, char *file, int flags, int l)
{
	char *tmp;

	if (flags & FLAG_GG)
	{
		tmp = get_infos(file, dir);
		if (is_lnk(tmp))
			ft_putstr(COLOR_LNK);
		else if (is_dir(tmp))
			ft_putstr(COLOR_DIR);
		else if (is_rdev(tmp))
			ft_putstr(COLOR_DEV);
		else if (is_exe(tmp))
			ft_putstr(COLOR_EXE);
		free(tmp);
	}
	ft_putstr(file);
	if (flags & FLAG_GG)
		ft_putstr(COLOR_END);
	put_name_type(dir, file, flags);
	if (l)
		put_pointer_dir(get_infos(file, dir));
	ft_putstr("\n");
}

void		put_color_type_length(char *dir, char *file, int flags)
{
	char *tmp;

	if (flags & FLAG_GG)
	{
		tmp = get_infos(file, dir);
		if (is_lnk(tmp))
			ft_putstr(COLOR_LNK);
		else if (is_dir(tmp))
			ft_putstr(COLOR_DIR);
		else if (is_rdev(tmp))
			ft_putstr(COLOR_DEV);
		else if (is_exe(tmp))
			ft_putstr(COLOR_EXE);
		free(tmp);
	}
	ft_putstr(file);
	if (flags & FLAG_GG)
		ft_putstr(COLOR_END);
	put_name_type(dir, file, flags);
}
