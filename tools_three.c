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

int			get_time(char *file)
{
	struct stat	*stats;
	int			time;

	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_time] struct stat");
	lstat(file, stats);
	time = stats->st_mtime;
	free(stats);
	return (time);
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
