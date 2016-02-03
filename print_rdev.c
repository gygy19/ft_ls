/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rdev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 19:55:01 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/01 19:55:03 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			l_mjr(t_args *args, int i, char *dir, int major)
{
	char		*infos;
	struct stat	*stats;
	int			space;
	int			len;

	space = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_space_lnk] struct stat");
	while (i < args->f_n)
	{
		len = 0;
		infos = get_infos(args->files[i], dir);
		lstat(infos, stats);
		major = major(stats->st_rdev);
		if (major(stats->st_rdev) <= 0 && ++i)
			continue;
		while ((major = major / 10) > 0)
			len++;
		if (len > space)
			space = len;
		free(infos);
		i++;
	}
	free(stats);
	return (space);
}

int			l_mnr(t_args *args, int i, char *dir, int minor)
{
	char		*infos;
	struct stat	*stats;
	int			space;
	int			len;

	space = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_space_lnk] struct stat");
	while (i < args->f_n)
	{
		len = 0;
		infos = get_infos(args->files[i], dir);
		lstat(infos, stats);
		minor = minor(stats->st_rdev);
		if (minor(stats->st_rdev) <= 0 && ++i)
			continue;
		while ((minor = minor / 10) > 0)
			len++;
		if (len > space)
			space = len;
		free(infos);
		i++;
	}
	free(stats);
	return (space);
}

void		print_space(int len, int space)
{
	int i;

	i = 0;
	while ((len = len / 10))
		i++;
	while (i < space)
	{
		i++;
		ft_putchar(' ');
	}
}

int			print_rdev(char *file, char *dir, t_args *args)
{
	int			i;
	char		*infos;
	struct stat *stats;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = get_infos(file, dir);
	lstat(infos, stats);
	if (major(stats->st_rdev) > 0)
	{
		ft_putstr("   ");
		print_space(major(stats->st_rdev), l_mjr(args, 0, dir, 0));
		ft_putnbr(major(stats->st_rdev));
		ft_putstr(", ");
		print_space(minor(stats->st_rdev), l_mnr(args, 0, dir, 0));
		ft_putnbr(minor(stats->st_rdev));
		i++;
	}
	else
		print_space(0, l_mjr(args, 0, dir, 0) + l_mnr(args, 0, dir, 0) + 4);
	free(infos);
	free(stats);
	return (i);
}
