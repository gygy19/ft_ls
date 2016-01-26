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

void		print_perm(char *file)
{
	char x;
	struct stat *stats;

	x = '-';
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_perm] struct stat");
	lstat(file, stats);
	if (is_dir(file))
	{
		if (S_ISLNK(stats->st_mode))
			x = 'l';
		else
			x = 'd';
	}
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
	free(stats);
}

void		get_total_blocks(t_args *args, char *dir)
{
	int i;
	int total;
	char *infos;
	struct stat *stats;

	i = 0;
	total = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_total_bloc] struct stat");
	while (i < args->f_n)
	{
		infos = ft_strjoin(ft_strjoin(dir, "/"), args->files[i]);
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
	char *infos;
	struct stat *stats;
	int space;
	int len;

	space = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_space_lnk] struct stat");
	while (i < args->f_n)
	{
		len = 0;
		infos = ft_strjoin(ft_strjoin(dir, "/"), args->files[i]);
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
	char *infos;
	struct stat *stats;
	int space;
	int len;

	space = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_space_mo] struct stat");
	while (i < args->f_n)
	{
		len = 0;
		infos = ft_strjoin(ft_strjoin(dir, "/"), args->files[i]);
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
	int i;
	char *infos;
	int len;
	struct stat *stats;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
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

void		print_rdev(char *file, char *dir)
{
	int i;
	char *infos;
	//int len;
	struct stat *stats;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	lstat(infos, stats);
	if (stats->st_rdev > 0)
	{
		ft_putnbr(stats->st_dev);
		ft_putstr(", ");
	}
	free(infos);
	free(stats);
}

void		print_lnk(char *file, char *dir, int space)
{
	int i;
	char *infos;
	int len;
	struct stat *stats;

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
	ft_putstr("  ");
	ft_putnbr(stats->st_nlink);
	free(infos);
	free(stats);
}

int		get_len_pwd(t_args *args, int i, char *dir)
{
	char *infos;
	struct stat *stats;
	int space;
	int len;
	struct passwd *pwd;

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

int		get_len_grp(t_args *args, int i, char *dir)
{
	char *infos;
	struct stat *stats;
	int space;
	int len;
	struct group *grp;

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
	int i;
	char *infos;
	struct stat *stats;
	struct group *grp;

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

void		print_pwd(char *file, char *dir, int space)
{
	int i;
	char *infos;
	struct stat *stats;
	struct passwd *pwd;

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
	int i;
	char *infos;
	struct stat *stats;

	i = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[print_lnk] struct stat");
	infos = ft_strjoin(ft_strjoin(dir, "/"), file);
	stat(infos, stats);
	free(infos);
	infos = ctime(&stats->st_ctime);
	ft_putstr(" ");
	ft_putstr(ft_strndup(infos + 4, 12));
	free(stats);
}

void		print_files_l(t_args *args, int i, char *dir)
{
	char *infos;
	int space_lnk;
	int	space_pwd;
	int	space_grp;
	int space_mo;

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
		print_pwd(args->files[i], dir, space_pwd);
		print_grp(args->files[i], dir, space_grp);
		print_rdev(args->files[i], dir);
		print_mo(args->files[i], dir, space_mo);
		print_date(args->files[i], dir);
		ft_putstr(" ");
		if (is_dir(ft_strjoin(ft_strjoin(dir, "/"), args->files[i])))
			ft_putstr(COLOR_DIR);
		ft_putstr(args->files[i]);
		ft_putstr(COLOR_END);
		ft_putstr("\n");
		i++;
		free(infos);
	}
}

int			get_long_work(t_args *args)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i < args->f_n)
	{
		if ((int)(ft_strlen(args->files[i]) + 1) > len)
			len = ft_strlen(args->files[i]) + 1;
		i++;
	}
	return (len);
}

int			get_line(int win_size, int long_work)
{
	int line;
	int i;
	int lim;

	line = long_work;
	i = 1;
	lim = long_work - 10;
	while (line < (win_size - lim))
	{
		line += long_work;
		i++;
	}
	return (i);
}

int			get_ll(int line, t_args *args)
{
	int ret;
	int i;
	int o;

	i = 0;
	ret = 1;
	o = 1;
	while (i < args->f_n)
	{
		if (o > line)
		{
			o = 1;
			ret++;
		}
		o++;
		i++;
	}
	return (ret);
}

void		print_files(t_args *args, int flags, int win_size, char *dir)
{
	int line;
	int i;
	int i2;
	int s;
	int space;
	int work;

	if (flags & FLAG_l)
	{
		print_files_l(args, 0, dir);
		return ;
	}
	work = get_long_work(args);
	line = get_line(win_size, work);
	line = get_ll(line, args);
	i = 0;
	while (i < line)
	{
		i2 = i;
		s = 0;
		while (i2 < args->f_n)
		{
			space = (work - ft_strlen(args->files[i2]));
			if (is_dir(ft_strjoin(dir, args->files[i2])))
				ft_putstr(COLOR_DIR);
			ft_putstr(args->files[i2]);
			ft_putstr(COLOR_END);
			if (i2 < (args->f_n))
			{
				while (space > 0)
				{
					ft_putchar(' ');
					space--;
				}
				s++;
			}
			i2 += line;
		}
		ft_putstr("\n");
		i++;
	}
}
