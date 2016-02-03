/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:27:03 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/28 12:27:05 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_args		*create_args(size_t size)
{
	t_args *new;

	new = (t_args *)malloc(sizeof(t_args));
	if (new)
	{
		if (!(new->dirs = get_new_tab(O_DIR))
				|| !(new->files = get_new_tab(O_DIR))
				|| !(new->errors = get_new_tab(O_DIR)))
			return (NULL);
		new->d_n = 0;
		new->f_n = 0;
		new->e_n = 0;
		new->size = size;
		return (new);
	}
	return (NULL);
}

int			get_time(char *file, char *dir)
{
	struct stat	*stats;
	int			time;
	char		*infos;

	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_time] struct stat");
	infos = get_infos(file, dir);
	lstat(infos, stats);
	time = stats->st_mtime;
	free(stats);
	free(infos);
	return (time);
}

int			is_rdev(char *file)
{
	struct stat	*stats;
	int			dev;

	dev = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_time] struct stat");
	lstat(file, stats);
	if (major(stats->st_rdev) > 0)
		dev = 1;
	free(stats);
	return (dev);
}

char		**get_new_tab(int size)
{
	char	**new;
	int		i;

	i = 0;
	new = NULL;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		print_error_malloc("[get_new_tab] char **");
	return (new);
}

char		*get_infos(char *file, char *dir)
{
	if (dir[0] == '\0')
		return (ft_strdup(file));
	return (ft_strjoin(ft_strjoin(dir, "/"), file));
}
