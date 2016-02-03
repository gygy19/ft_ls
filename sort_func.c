/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 12:27:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/02/01 17:47:14 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			sort_az(char **tab, size_t tab_size, char *dir)
{
	size_t i;
	size_t id;

	i = 0;
	id = -1;
	(void)dir;
	while (i < tab_size)
	{
		if ((int)id == -1 && tab[i][0] != '\0')
			id = i;
		else if (tab[i][0] != '\0' && id != i)
			if (ft_strcmp(tab[id], tab[i]) >= 0)
				id = i;
		i++;
	}
	return (id);
}

int			sort_za(char **tab, size_t tab_size, char *dir)
{
	size_t i;
	size_t id;

	i = 0;
	id = -1;
	(void)dir;
	while (i < tab_size)
	{
		if ((int)id == -1 && tab[i][0] != '\0')
			id = i;
		else if (tab[i][0] != '\0' && id != i)
			if (ft_strcmp(tab[id], tab[i]) <= 0)
				id = i;
		i++;
	}
	return (id);
}

int			sort_by_time(char **tab, size_t tab_size, char *dir)
{
	size_t i;
	size_t id;

	i = 0;
	id = -1;
	while (i < tab_size)
	{
		if ((int)id == -1 && tab[i][0] != '\0')
			id = i;
		else if (tab[i][0] != '\0' && id != i)
		{
			if (get_time(tab[id], dir) < get_time(tab[i], dir))
				id = i;
			else if (get_time(tab[id], dir) == get_time(tab[i], dir))
				if (ft_strcmp(tab[id], tab[i]) >= 0)
					id = i;
		}
		i++;
	}
	return (id);
}

int			sort_by_time_u(char **tab, size_t tab_size, char *dir)
{
	size_t i;
	size_t id;

	i = 0;
	id = -1;
	while (i < tab_size)
	{
		if ((int)id == -1 && tab[i][0] != '\0')
			id = i;
		else if (tab[i][0] != '\0' && id != i)
		{
			if (get_time_u(tab[id], dir) < get_time_u(tab[i], dir))
				id = i;
			else if (get_time_u(tab[id], dir) == get_time_u(tab[i], dir))
				if (ft_strcmp(tab[id], tab[i]) >= 0)
					id = i;
		}
		i++;
	}
	return (id);
}
