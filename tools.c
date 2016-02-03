/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 22:24:41 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/29 22:07:57 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

size_t		get_size(void)
{
	size_t			size;
	struct winsize	*w;

	if (!(w = malloc(sizeof(struct winsize))))
		print_error_malloc("[get_size] struct winsize");
	ioctl(0, TIOCGWINSZ, w);
	size = (size_t)w->ws_col;
	free(w);
	return (size);
}

size_t		exist_file(char *file)
{
	size_t		ret;
	struct stat	*stats;

	ret = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[exist_file] struct stat");
	if (stat(file, stats) == 0)
		ret = 1;
	free(stats);
	return (ret);
}

size_t		is_dir(char *dir)
{
	size_t		ret;
	struct stat	*stats;

	ret = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[exist_file] struct stat");
	if (stat(dir, stats) == 0)
		if (S_ISDIR(stats->st_mode))
			ret = 1;
	free(stats);
	return (ret);
}

size_t		have_right_open(char *dir)
{
	DIR *dirp;

	dirp = NULL;
	dirp = opendir(dir);
	if (dirp == NULL)
	{
		ft_putstr("ft_ls : ");
		dir = end_slash(dir);
		perror(dir);
		return (0);
	}
	closedir(dirp);
	return (1);
}

DIR			*open_directory(char *dir)
{
	DIR *dirp;

	dirp = NULL;
	if (!is_dir(dir))
	{
		perror(dir);
		return (NULL);
	}
	dirp = opendir(dir);
	return (dirp);
}
