/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 21:51:22 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/24 23:06:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_flag_error(int c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ft_ls [-GRafglort1] [file ...]\n");
	exit(0);
}

void		print_error_dir_or_file(t_args *args)
{
	int i;

	i = 0;
	if (args->e_n == 0)
		return ;
	while (i < args->e_n)
	{
		ft_putstr("ft_ls: ");
		perror(args->errors[i]);
		i++;
	}
}

void		print_error_zero(void)
{
	ft_putstr("ft_ls: ");
	ft_putstr("fts_open: No such file or directory\n");
	exit(0);
}

void		print_error_malloc(char *txt)
{
	ft_putstr("ft_ls: error break ");
	ft_putstr(txt);
	ft_putstr(".\n");
	exit(0);
}
