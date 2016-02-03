/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:15:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/28 04:31:13 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	read_args(t_args *args, int flags, int win_size, int first)
{
	int id;

	id = 0;
	if (args == NULL)
		return ;
	while (id < args->d_n)
	{
		if (args->d_n > 1 || args->f_n > 0 || args->e_n > 0)
		{
			if ((first && id != 0) || !first)
				ft_putstr("\n");
			put_color_p_dir(args->dirs[id], flags);
		}
		if (have_right_open(args->dirs[id]))
			print_dir(args->dirs[id], flags, win_size, 0);
		id++;
	}
	free(args);
}

int		main(int argc, char **argv)
{
	int		flags;
	int		i;
	t_args	*args;

	if (argc > 1)
	{
		flags = verif_flags(argc, argv);
		i = started_argc(argc, argv);
		if (flags & FLAG_ERROR)
			return (0);
		if (i == -1)
			print_dir(".", flags, get_size(), 0);
		else
		{
			args = sorting_args(i, argc, argv, flags);
			print_error_dir_or_file(args);
			if (args->f_n > 0 && !(i = 0))
				print_files(args, flags, get_size(), "");
			if (args->d_n > 0)
				read_args(args, flags, get_size(), i > 0 ? 1 : 0);
		}
	}
	else
		print_dir(".", 0, get_size(), 0);
	return (0);
}
