/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fourth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 02:51:35 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/02 02:51:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			is_exe(char *file)
{
	struct stat	*stats;
	int			ret;

	ret = 0;
	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[is_exe] struct stat");
	lstat(file, stats);
	if ((stats->st_mode & S_IXUSR) || (stats->st_mode & S_IXGRP)
		|| (stats->st_mode & S_IXOTH))
		ret = 1;
	free(stats);
	return (ret);
}

int			get_time_u(char *file, char *dir)
{
	struct stat	*stats;
	int			time;
	char		*infos;

	if (!(stats = malloc(sizeof(struct stat))))
		print_error_malloc("[get_time_u] struct stat");
	infos = get_infos(file, dir);
	lstat(infos, stats);
	time = stats->st_atime;
	free(stats);
	free(infos);
	return (time);
}
