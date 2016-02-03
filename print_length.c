/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 22:14:30 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/01 17:54:03 by jguyet           ###   ########.fr       */
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
	lim = long_work - 1;
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

int			g_t(char *dir, char *file, int flags)
{
	char	*tmp;
	int		ret;

	ret = 0;
	if (flags & FLAG_FF)
	{
		tmp = get_infos(file, dir);
		if (is_lnk(tmp))
			return (1);
		else if (is_dir(tmp))
			return (1);
		else if (is_exe(tmp))
			return (1);
		free(tmp);
	}
	return (ret);
}

void		print_length(t_args *args, int f, int win_size, char *d)
{
	int		line;
	int		i;
	int		i2;
	int		s;
	int		w;

	w = get_long_work(args);
	line = get_line(win_size, w);
	line = get_ll(line, args);
	i = 0;
	while (i < line)
	{
		i2 = i;
		while (i2 < args->f_n)
		{
			s = ((w - ft_strlen(args->files[i2])) - g_t(d, args->files[i2], f));
			put_color_type_length(d, args->files[i2], f);
			if (i2 < (args->f_n))
				while (s-- > 0)
					ft_putchar(' ');
			i2 += line;
		}
		ft_putstr("\n");
		i++;
	}
}
