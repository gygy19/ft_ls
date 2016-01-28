/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 22:14:30 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/24 22:24:18 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			get_long_work(t_args *args)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i < args->f_n)
	{
		if ((int)(ft_strlen(args->files[i]) + 1) > len)
			len = ft_strlen(args->files[i]) + 1;
		i++;
	}
	return (len);
}

int			get_line(int win_size, int long_work)
{
	int line;
	int i;
	int lim;

	line = long_work;
	i = 1;
	lim = long_work - 5;
	while (line < (win_size - lim))
	{
		line += long_work;
		i++;
	}
	return (i);
}

int			get_ll(int line, t_args *args)
{
	int ret;
	int i;
	int o;

	i = 0;
	ret = 1;
	o = 1;
	while (i < args->f_n)
	{
		if (o > line)
		{
			o = 1;
			ret++;
		}
		o++;
		i++;
	}
	return (ret);
}

void		print_length(t_args *args, int flags, int win_size, char *dir)
{
	int		line;
	int		i;
	int		i2;
	int		space;
	int		work;

	work = get_long_work(args);
	line = get_line(win_size, work);
	line = get_ll(line, args);
	i = 0;
	while (i < line)
	{
		i2 = i;
		while (i2 < args->f_n)
		{
			space = (work - ft_strlen(args->files[i2]));
			put_color_type_length(dir, args->files[i2], flags);
			if (i2 < (args->f_n))
				while (space-- > 0)
					ft_putchar(' ');
			i2 += line;
		}
		ft_putstr("\n");
		i++;
	}
}
