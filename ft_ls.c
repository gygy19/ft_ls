/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:15:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 05:24:37 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		read_args(t_args *args, int flags, int win_size)
{
	int id;
	t_args *new;

	id = 0;
	while (id < args->d_n)
	{
		if (is_lnk(args->dirs[id]) && id++)
			continue;
		if (args->d_n > 1 || args->f_n > 0)
		{
			ft_putstr("\n\033[33m");
			ft_putstr(args->dirs[id]);
			ft_putstr("\033[00m:\n");
		}
		if ((new = print_dir(args->dirs[id], flags, win_size)) != NULL)
			read_args(new, flags, win_size);
		id++;
	}
	free_args(args);
}

int		main(int argc, char **argv)
{
	int flags;
	int	i;
	t_args *args;

	if (argc > 1)
	{
		flags = verif_flags(argc, argv);
		i = started_argc(argc, argv);
		if (flags & FLAG_ERROR)
			return (0);
		if (i == -1)
			print_dir("./", flags, get_size());
		else
		{
			args = sorting_args(i, argc, argv, flags);
			print_error_dir_or_file(args);
			if (args->f_n > 0)
			{
				print_files(args, flags, get_size(), "");
				ft_putstr("\n");
			}
			if (args->d_n > 0)
				read_args(args, flags, get_size());

		}
	}
	else
	{
		print_dir("./", 0, get_size());
	}
	return (0);
}
