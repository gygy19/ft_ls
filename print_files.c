/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 05:26:29 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/24 07:57:44 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_files_l(t_args *args)
{
	(void)args;
}

int			get_len_all_args(t_args *args, int line)
{
	int i;
	int i2;
	int total;
	int ret;
	int s;
	int	*space;

	i = 0;
	ret = 0;
	space = (int *)malloc(sizeof(int) * (args->f_n));
	while (i < line)
	{
		i2 = i;
		total = 0;
		s = 0;
		while (i2 < args->f_n)
		{
			total += ft_strlen(args->files[i2]) + 5;
			space[s] = ft_strlen(args->files[i2]) + 5;
			i2 += line;
			s++;
		}
		if (total > ret)
		{
			s = 0;
			args->space = space;
			ret = total;
		}
		i++;
	}
	return (ret);
}

void		print_files(t_args *args, int flags, int win_size)
{
	int line;
	int ok;
	int i;
	int i2;
	int s;
	int space;

	ok = 0;
	line = 0;
	if (flags & FLAG_l)
	{
		print_files_l(args);
		return ;
	}
	while (ok != 1)
	{
		line++;
		if (get_len_all_args(args, line) <= (win_size + 5))
			ok = 1;
	}
	i = 0;
	while (i < win_size)
	{
		ft_putchar('-');
		i++;
	}
	i = 0;
	while (i < line)
	{
		i2 = i;
		s = 0;
		while (i2 < args->f_n)
		{
			space = args->space[s] - ft_strlen(args->files[i2]);
			ft_putstr(args->files[i2]);
			if (i2 < (args->f_n + 1))
			{
				while (space > 0)
				{
					ft_putchar(' ');
					space--;
				}
				s++;
			}
			i2 += line;
		}
			ft_putstr("\n");
		i++;
	}
	i = 0;
	while (i < win_size)
	{
		ft_putchar ('-');
		i++;
	}
}
