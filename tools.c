/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 22:24:41 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 02:42:41 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

size_t			get_size(void)
{
	size_t size;
	struct winsize *w;

	if (!(w = malloc(sizeof(struct winsize))))
		print_error_malloc("[get_size] struct winsize");
	(void)ioctl(0, TIOCGWINSZ, w);
	size = (size_t)w->ws_col;
	free(w);
	return (size);
}

size_t			exist_file(char *file)
{
	size_t ret;
	struct stat *stats;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[exist_file] struct stat");
	ret = (stat(file, stats) == 0);
	free(stats);
	return (ret);
}

size_t			is_dir(char *dir)
{
	DIR *dirp;

	dirp = NULL;
	dirp = opendir(dir);
	if (dirp == NULL)
		return (0);
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

char		**get_new_tab(int size)
{
	char **new;

	new = NULL;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		print_error_malloc("[get_new_tab] char **");
	//size = 0;
	while (size > -1)
	{
		if (new[size])
			new[size] = NULL;
		size--;
	}
	return(new);
}
