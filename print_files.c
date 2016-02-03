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
	infos = get_infos(file, dir);
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

void		print_date(char *file, char *dir, int flags)
{
	char		*infos;
	struct stat	*stats;
	int			n_time;

	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = get_infos(file, dir);
	lstat(infos, stats);
	free(infos);
	n_time = (flags & FLAG_U) ? stats->st_atime : stats->st_mtime;
	infos = ctime((flags & FLAG_U) ? &stats->st_atime : &stats->st_mtime);
	ft_putstr(" ");
	if (n_time > time(0) || n_time < (time(0) - 18493200))
	{
		if (ft_strlen(infos) > 4)
			ft_putstr(ft_strndup(infos + 4, 7));
		ft_putstr(" ");
		if (ft_strlen(infos) > 20)
			ft_putstr(ft_strndup(infos + 20, 4));
	}
	else
		ft_putstr(ft_strndup(infos + 4, 12));
	free(stats);
}

void		print_part1_l(int i, t_args *args, char *dir, int space_lnk)
{
	char	*infos;

	infos = get_infos(args->files[i], dir);
	print_perm(infos);
	free(infos);
	print_lnk(args->files[i], dir, space_lnk);
}

void		print_files_l(t_args *args, int i, char *dir, int flags)
{
	int		all_space[4];
	int		is_dev;

	get_total_blocks(args, dir, flags);
	all_space[0] = get_space_lnk(args, 0, dir);
	all_space[1] = get_len_pwd(args, 0, dir);
	all_space[2] = get_len_grp(args, 0, dir);
	all_space[3] = get_space_mo(args, 0, dir);
	is_dev = l_mjr(args, 0, dir, 0);
	while (i < args->f_n)
	{
		print_part1_l(i, args, dir, all_space[0]);
		if (!(flags & FLAG_G))
			print_pwd(args->files[i], dir, all_space[1]);
		if (!(flags & FLAG_O))
			print_grp(args->files[i], dir, all_space[2]);
		if (!is_dev || !print_rdev(args->files[i], dir, args))
			print_mo(args->files[i], dir, all_space[3]);
		print_date(args->files[i], dir, flags);
		ft_putstr(" ");
		put_color_type(dir, args->files[i], flags, 1);
		i++;
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
			put_color_type(dir, args->files[i], flags, 0);
			i++;
		}
	}
	else
	{
		print_length(args, flags, win_size, dir);
	}
}
