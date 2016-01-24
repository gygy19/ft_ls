/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:15:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/24 09:01:00 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <stdio.h>

int			get_size(void)
{
	struct winsize w;

	(void)ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

void		read_args(t_args *args, int flags, int win_size)
{
	int d;
	t_args *oo;

	d = 0;
	while (d < args->d_n)
	{
		if (args->d_n > 1 || args->f_n > 0)
		{
			ft_putstr(args->dirs[d]);
			ft_putstr(":\n");
		}
		oo = print_dir(args->dirs[d], flags, win_size);
		if (oo != NULL)
			read_args(oo, flags, win_size);
		d++;
	}
}

int		main(int argc, char **argv)
{
	int flags;
	int	i;
	t_args *args;

	if (argc > 1)
	{
		/*flags*/
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
				print_files(args, flags, get_size());
				ft_putstr("\n");
			}
			read_args(args, flags, get_size());

		}
		/*start argc*/
		/*if (start == argc) { doc|local. }*/
		/*else total argv files and directory.*/
	}
	else
	{
		/*doc|local.*/
	}
	return (0);
}
