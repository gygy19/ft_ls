/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 05:26:29 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 05:24:22 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_pwd(char *file, char *dir, int space)
{
	int				i;
	char			*infos;
	struct stat		*stats;
	struct passwd	*pwd;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	lstat(infos, stats);
	pwd = getpwuid(stats->st_uid);
	ft_putstr(" ");
	if (pwd != NULL)
	{
		ft_putstr(pwd->pw_name);
		i = ft_strlen(pwd->pw_name);
	}
	while (i < space)
	{
		i++;
		ft_putchar(' ');
	}
	free(infos);
	free(stats);
}

void		print_date(char *file, char *dir)
{
	char		*infos;
	struct stat	*stats;

	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	lstat(infos, stats);
	free(infos);
	infos = ctime(&stats->st_ctime);
	ft_putstr(" ");
	if (stats->st_mtime > time(0) || stats->st_mtime < (time(0) - 18493200))
	{
		ft_putstr(ft_strndup(infos + 4, 7));
		ft_putstr(" ");
		ft_putstr(ft_strndup(infos + 20, 4));
	}
	else
		ft_putstr(ft_strndup(infos + 4, 12));
	free(stats);
}

void		print_part_l(int i, t_args *args, char *dir, int space_mo)
{
	if (!print_rdev(args->files[i], dir))
		print_mo(args->files[i], dir, space_mo);
	print_date(args->files[i], dir);
	ft_putstr(" ");
}

void		print_files_l(t_args *args, int i, char *dir, int flags)
{
	char	*infos;
	int		space_lnk;
	int		space_pwd;
	int		space_grp;
	int		space_mo;

	get_total_blocks(args, dir);
	space_lnk = get_space_lnk(args, 0, dir);
	space_pwd = get_len_pwd(args, 0, dir);
	space_grp = get_len_grp(args, 0, dir);
	space_mo = get_space_mo(args, 0, dir);
	while (i < args->f_n)
	{
		infos = ft_strjoin(ft_strjoin(dir, "/"), args->files[i]);
		print_perm(infos);
		print_lnk(args->files[i], dir, space_lnk);
		if (!(flags & FLAG_G))
			print_pwd(args->files[i], dir, space_pwd);
		if (!(flags & FLAG_O))
			print_grp(args->files[i], dir, space_grp);
		print_part_l(i, args, dir, space_mo);
		put_color_type(dir, args->files[i], flags);
		i++;
		free(infos);
	}
}

void		print_files(t_args *args, int flags, int win_size, char *dir)
{
	int i;

	i = 0;
	if (args == NULL)
		return ;
	if ((flags & FLAG_L) || (flags & FLAG_O) || (flags & FLAG_G))
		print_files_l(args, 0, dir, flags);
	else if (flags & FLAG_1)
	{
		while (i < args->f_n)
		{
			put_color_type(dir, args->files[i], flags);
			i++;
		}
	}
	else
	{
		print_length(args, flags, win_size, dir);
	}
}
