/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 21:51:49 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 21:51:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_perm(char *file)
{
	char		x;
	struct stat	*stats;

	x = '-';
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_perm] struct stat");
	lstat(file, stats);
	if (S_ISLNK(stats->st_mode))
		x = 'l';
	else if (S_ISCHR(stats->st_mode))
		x = 'c';
	else if (S_ISDIR(stats->st_mode))
		x = 'd';
	ft_putchar(x);
	ft_putchar((stats->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((stats->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((stats->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((stats->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((stats->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((stats->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((stats->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((stats->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((stats->st_mode & S_IXOTH) ? 'x' : '-');
	put_attr(file);
	free(stats);
}

void		get_total_blocks(t_args *args, char *dir, int flags)
{
	int			i;
	int			total;
	char		*infos;
	struct stat	*stats;

	i = 0;
	total = 0;
	if (flags & FLAG_D)
		return ;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_total_bloc] struct stat");
	while (i < args->f_n)
	{
		infos = get_infos(args->files[i], dir);
		lstat(infos, stats);
		total += stats->st_blocks;
		free(infos);
		i++;
	}
	free(stats);
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

int			get_space_lnk(t_args *args, int i, char *dir)
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
		while ((stats->st_nlink = stats->st_nlink / 10) > 0)
			len++;
		if (len > space)
			space = len;
		free(infos);
		i++;
	}
	free(stats);
	return (space);
}

int			get_space_mo(t_args *args, int i, char *dir)
{
	char		*infos;
	struct stat	*stats;
	int			space;
	int			len;

	space = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_space_mo] struct stat");
	while (i < args->f_n)
	{
		len = 0;
		infos = get_infos(args->files[i], dir);
		lstat(infos, stats);
		while ((stats->st_size = stats->st_size / 10) > 0)
			len++;
		if (len > space)
			space = len;
		free(infos);
		i++;
	}
	free(stats);
	return (space);
}

void		print_mo(char *file, char *dir, int space)
{
	int			i;
	char		*infos;
	int			len;
	struct stat	*stats;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = get_infos(file, dir);
	lstat(infos, stats);
	len = stats->st_size;
	while ((len = len / 10))
		i++;
	while (i < space)
	{
		i++;
		ft_putchar(' ');
	}
	ft_putstr("  ");
	ft_putnbr(stats->st_size);
	free(infos);
	free(stats);
}
