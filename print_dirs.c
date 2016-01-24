/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 07:56:44 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/24 09:03:30 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_dir_l(char *dir)
{
	(void)dir;
}

long		get_nbr_files(char *dir)
{
	struct stat stats;
	stat(dir, &stats);
	return (stats.st_ino - 2);
}

int			is_dir(char *dir)
{
	DIR	*dirp;

	if ((dirp = opendir(dir)) != NULL)
		return(1);
	return (0);
}

t_args		*print_dir(char *dir, int flags, int win_size)
{
	DIR *dirp;
	struct dirent *files;
	char **new_args;
	int i;
	
	(void)win_size;
	if (flags & FLAG_l)
	{
		print_dir_l(dir);
		return (NULL);
	}
	dirp = opendir(dir);
	if (dirp == NULL)
		return (NULL);
	i = 0;
	new_args = (char **)malloc(sizeof(char *) * get_nbr_files(dir));
	while ((files = readdir(dirp)))
	{
		ft_putstr(files->d_name);
		if (files->d_name[0] != '.' && is_dir(ft_strjoin(ft_strjoin(dir, "/"), files->d_name)) > 0)
		{
			new_args[i] = ft_strjoin(ft_strjoin(dir, "/"), files->d_name);
			i++;
		}
		ft_putstr("\n");
	}
	if (flags & FLAG_R)
		return (sorting_args_end_save(0, i, new_args, flags));
	return (NULL);
}
