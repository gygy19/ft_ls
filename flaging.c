/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flaging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 20:25:09 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/23 23:09:57 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		add_flags(int flags, int part_flags)
{
	int i;
	int ret;

	i = START_FLAG;
	ret = 0;
	if (part_flags & FLAG_1 && flags & FLAG_L)
		ret -= FLAG_L;
	while (i < MAX_FLAG)
	{
		if ((part_flags & i) && !(flags & i))
			ret += i;
		i *= 2;
	}
	return (ret);
}

int		add_part(char c)
{
	if (c == '1' || c == 'a')
		return (c == '1' ? FLAG_1 : FLAG_A);
	if (c == 'l' || c == 'F')
		return (c == 'l' ? FLAG_L : FLAG_FF);
	if (c == 'r')
		return (FLAG_R);
	if (c == 'R')
		return (FLAG_RR);
	if (c == 't')
		return (FLAG_T);
	if (c == 'o')
		return (FLAG_O);
	if (c == 'g')
		return (FLAG_G);
	if (c == 'G')
		return (FLAG_GG);
	if (c == 'f')
		return (FLAG_F);
	if (c == 'd')
		return (FLAG_D);
	if (c == 'u')
		return (FLAG_U);
	if (c == '-')
		return (FLAG_PREFIX);
	return (FLAG_ERROR);
}

int		get_flag_part(int i, int argc, char **argv, int put)
{
	int i2;
	int part;

	i2 = 1;
	part = 0;
	if (i == argc || argv[i][0] != '-' || argv[i][1] == '\0')
		return (0);
	while (argv[i][i2])
	{
		if (!(part & add_part(argv[i][i2])))
			part += add_part(argv[i][i2]);
		if (add_part(argv[i][i2]) & FLAG_1 && part & FLAG_L)
			part -= FLAG_L;
		if (part & FLAG_ERROR || (argv[i][i2] == '-' && i2 > 1))
		{
			if (put)
				print_flag_error(argv[i][i2]);
			break ;
		}
		i2++;
	}
	return (part);
}

int		verif_flags(int argc, char **argv)
{
	int flags;
	int part_flags;
	int i;

	i = 1;
	flags = 0;
	while ((part_flags = get_flag_part(i, argc, argv, 0)) > 0)
	{
		flags += add_flags(flags, part_flags);
		if (flags & FLAG_ERROR || flags & FLAG_PREFIX)
			break ;
		i++;
	}
	return (flags);
}

int		started_argc(int argc, char **argv)
{
	int i;
	int part;

	i = 1;
	while ((part = get_flag_part(i, argc, argv, 1)) > 0)
	{
		if (part & FLAG_ERROR)
			break ;
		if (part & FLAG_PREFIX)
		{
			i++;
			break ;
		}
		i++;
	}
	if (i == argc)
		i = -1;
	return (i);
}
