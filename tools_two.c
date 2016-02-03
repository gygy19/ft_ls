/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 01:48:44 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 05:24:31 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		free_tab(char **tab, int size)
{
	int i;

	if (!tab || !tab[0])
		return ;
	i = 0;
	while (tab[i] && i < size)
	{
		free(tab[i]);
		i++;
	}
}

void		free_args(t_args *args)
{
	if (args->f_n > 0)
		free_tab(args->files, args->f_n);
	if (args->e_n > 0)
		free_tab(args->errors, args->e_n);
}

char		*end_slash(char *dir)
{
	int		i;
	char	*tmp;

	tmp = dir;
	i = ft_strlen(dir);
	tmp += i;
	while (i > 0)
	{
		if (tmp[0] == '/')
			return (tmp + 1);
		tmp--;
		i--;
	}
	return (tmp);
}

void		put_attr(char *file)
{
	if (listxattr(file, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putstr("@");
	else
		ft_putstr(" ");
}

int			is_lnk(char *dir)
{
	int			lnk;
	struct stat	*stats;

	stats = malloc(sizeof(struct stat));
	lstat(dir, stats);
	lnk = (S_ISLNK(stats->st_mode));
	free(stats);
	return (lnk);
}
