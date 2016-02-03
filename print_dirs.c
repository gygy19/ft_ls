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

int			add_new_dir(char *dir, int flags, char *d_name)
{
	if (flags & FLAG_RR && ft_strcmp(d_name, ".") != 0)
		if (ft_strcmp(d_name, "..") != 0)
			if (is_dir(ft_strjoin(ft_strjoin(dir, "/"), d_name)) > 0)
				return (1);
	return (0);
}

void		print_d(char *dir, int flags)
{
	if (flags & FLAG_D)
	{
		ft_putstr(dir);
		ft_putstr("\n");
		exit(0);
	}
}

void		print_dir(char *dir, int flags, int w_s, int i)
{
	char			**args;
	char			**here;
	int				o;
	DIR				*dirp;
	struct dirent	*files;

	print_d(dir, flags);
	dirp = open_directory(dir);
	o = 0;
	files = malloc(sizeof(struct dirent));
	args = get_new_tab(O_DIR);
	here = get_new_tab(O_DIR);
	while ((files = readdir(dirp)) != 0)
	{
		if ((files->d_name[0] == '.' && !(flags & FLAG_A) && !(flags & FLAG_F)))
			continue;
		here[o++] = ft_strdup(files->d_name);
		if (add_new_dir(dir, flags, files->d_name))
			args[i++] = ft_strjoin(ft_strjoin(dir, "/"), files->d_name);
	}
	closedir(dirp);
	print_files(sorting_args_end_save(o, here, flags, dir), flags, w_s, dir);
	free(files);
	if (flags & FLAG_RR && i > 0)
		read_args(sorting_args_end_save(i, args, flags, dir), flags, w_s, 0);
}
