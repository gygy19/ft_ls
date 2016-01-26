/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 07:56:44 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 02:53:10 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_args		*print_dir_l(char *dir, int flags)
{
	(void)dir;
	(void)flags;
	return (NULL);
}

long		get_nbr_files(char *dir)
{
	long caca;
	struct stat *stats;

	stats = malloc(sizeof(struct stat));
	stat(dir, stats);
	caca = stats->st_nlink - 2;
	free(stats);
	return (caca);
}

int			is_lnk(char *dir)
{
	int lnk;
	struct stat *stats;

	stats = malloc(sizeof(struct stat));
	lstat(dir, stats);
	lnk = (S_ISLNK(stats->st_mode));
	free(stats);
	return (lnk);
}

t_args		*print_dir(char *dir, int flags, int win_size)
{
	DIR *dirp;
	struct dirent *files;
	char **new_args;
	char **here;
	int i;
	int o;
	
	(void)win_size;
	//if (flags & FLAG_l)
		//return (print_dir_l(dir, flags));
	dirp = open_directory(dir);
	if (dirp == NULL)
		return (NULL);
	i = 0;
	o = 0;
	files = NULL;
	files = malloc(sizeof(struct dirent));
	new_args = get_new_tab(40960);
	here = get_new_tab(40960);
	while ((files = readdir(dirp)) != 0)
	{
		if (files->d_name[0] == '.' && !(flags & FLAG_a))
			continue;
		here[o] = ft_strdup(files->d_name);
		//ft_putstr(files->d_name);
		if (files->d_name[0] != '.' && is_dir(ft_strjoin(ft_strjoin(dir, "/"), files->d_name)) > 0)
		{
				new_args[i] = ft_strjoin(ft_strjoin(dir, "/"), files->d_name);
				i++;
		}
		o++;
	}
	closedir(dirp);
	if (o > 0)
		print_files(sorting_args_end_save(0, o, here, flags), flags, win_size, dir);
	free(files);
	free_tab(here);
	free(here);
	if (flags & FLAG_R && i > 0)
	{
		read_args(sorting_args_end_save(0, i, new_args, flags), flags, win_size);
		return (NULL);
	}
	free_tab(new_args);
	return (NULL);
}
