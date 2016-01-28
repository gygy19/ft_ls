/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 21:52:02 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 21:52:04 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			print_rdev(char *file, char *dir)
{
	int			i;
	char		*infos;
	struct stat *stats;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	lstat(infos, stats);
	if (major(stats->st_rdev) > 0)
	{
		ft_putnbr(major(stats->st_rdev));
		ft_putstr(", ");
		ft_putnbr(minor(stats->st_rdev));
		i++;
	}
	free(infos);
	free(stats);
	return (i);
}

void		print_lnk(char *file, char *dir, int space)
{
	int			i;
	char		*infos;
	int			len;
	struct stat	*stats;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	lstat(infos, stats);
	len = stats->st_nlink;
	while ((len = len / 10))
		i++;
	while (i < space)
	{
		i++;
		ft_putchar(' ');
	}
	ft_putstr(" ");
	ft_putnbr(stats->st_nlink);
	free(infos);
	free(stats);
}

int			get_len_pwd(t_args *args, int i, char *dir)
{
	char			*infos;
	struct stat		*stats;
	int				space;
	int				len;
	struct passwd	*pwd;

	space = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_space_lnk] struct stat");
	while (i < args->f_n)
	{
		len = 0;
		infos = ft_strjoin(ft_strjoin(dir, "/"), args->files[i]);
		lstat(infos, stats);
		if ((pwd = getpwuid(stats->st_uid)) != NULL)
		{
			if ((int)ft_strlen(pwd->pw_name) > space)
				space = ft_strlen(pwd->pw_name);
		}
		free(infos);
		i++;
	}
	free(stats);
	return (space);
}

int			get_len_grp(t_args *args, int i, char *dir)
{
	char			*infos;
	struct stat		*stats;
	int				space;
	int				len;
	struct group	*grp;

	space = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_space_lnk] struct stat");
	while (i < args->f_n)
	{
		len = 0;
		infos = ft_strjoin(ft_strjoin(dir, "/"), args->files[i]);
		lstat(infos, stats);
		if ((grp = getgrgid(stats->st_gid)) != NULL)
		{
			if ((int)ft_strlen(grp->gr_name) > space)
				space = ft_strlen(grp->gr_name);
		}
		free(infos);
		i++;
	}
	free(stats);
	return (space);
}

void		print_grp(char *file, char *dir, int space)
{
	int				i;
	char			*infos;
	struct stat		*stats;
	struct group	*grp;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	lstat(infos, stats);
	grp = getgrgid(stats->st_gid);
	ft_putstr("  ");
	if (grp != NULL)
	{
		ft_putstr(grp->gr_name);
		i = ft_strlen(grp->gr_name);
	}
	while (i < space)
	{
		i++;
		ft_putchar(' ');
	}
	free(infos);
	free(stats);
}
