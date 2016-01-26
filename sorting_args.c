/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 23:32:09 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 02:29:40 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		**sort_tab_za(char **tab, size_t tab_size,\
		char **new_tab, size_t size_new)
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
			if (ft_strcmp(tab[id], tab[i]) <= 0)
				id = i;
		i++;
	}
	if (size_new == 0 && !(new_tab = get_new_tab(tab_size + 1)))
		return (NULL);
	if (tab[id])
	{
		new_tab[size_new] = ft_strdup(tab[id]);
		size_new += 1;
		ft_bzero(tab[id], 1);
	}
	if (size_new == tab_size)
		return (new_tab);
	return (sort_tab_za(tab, tab_size, new_tab, size_new));
}

char		**sort_tab_az(char **tab, size_t tab_size, char **new_tab, size_t size_new)
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
			if (ft_strcmp(tab[id], tab[i]) >= 0)
				id = i;
		i++;
	}
	if (size_new == 0 && !(new_tab = get_new_tab(tab_size + 1)))
		return (NULL);
	if (tab[id] != NULL)
	{	
		new_tab[size_new] = ft_strdup(tab[id]);
		size_new++;
		ft_bzero(tab[id], 1);
	}
	if (size_new >= tab_size)
		return (new_tab);
	return (sort_tab_az(tab, tab_size, new_tab, size_new));
}

t_args		*create_args(size_t size)
{
	t_args *new;

	new = (t_args *)malloc(sizeof(t_args));
	if (new)
	{
		if (!(new->dirs = get_new_tab(size + 1))
				|| !(new->files = get_new_tab(size + 1))
				|| !(new->errors = get_new_tab(size + 1)))
			return (NULL);
		new->d_n = 0;
		new->f_n = 0;
		new->e_n = 0;
		new->size = size;
		return (new);
	}
	return (NULL);
}

t_args		*sort_by_flags(t_args **args, int flags)
{
	char **tmp;

	tmp = NULL;
	if ((*args)->d_n > 0 && flags & FLAG_r)
		tmp = sort_tab_za((*args)->dirs, (*args)->d_n, NULL, 0);
	else if ((*args)->d_n > 0)
		tmp = sort_tab_az((*args)->dirs, (*args)->d_n, NULL, 0);
	if ((*args)->d_n > 0)
	{
		free_tab((*args)->dirs);
		(*args)->dirs = tmp;
	}
	if ((*args)->f_n > 0 && flags & FLAG_r)
		tmp = sort_tab_za((*args)->files, (*args)->f_n, NULL, 0);
	else if ((*args)->f_n > 0)
		tmp = sort_tab_az((*args)->files, (*args)->f_n, NULL, 0);
	if ((*args)->f_n > 0)
	{
		free_tab((*args)->files);
		(*args)->files = tmp;
	}
	if ((*args)->e_n > 0)
	{
		tmp = sort_tab_az((*args)->errors, (*args)->e_n, NULL, 0);
		free_tab((*args)->errors);
		(*args)->errors = tmp;
	}
	return (*args);
}

t_args		*sorting_args(int i, int max, char **argv, int flags)
{
	t_args		*args;

	if (!(args = create_args(max)))
		return (NULL);
	while (i < max)
	{
		if ((is_dir(argv[i])) && !is_lnk(argv[i]))
		{
			args->dirs[args->d_n] = ft_strdup(argv[i]);
			args->d_n++;
		}
		else if (exist_file(argv[i]))
		{
			args->files[args->f_n] = ft_strdup(argv[i]);
			args->f_n++;
		}
		else
		{
			args->errors[args->e_n] = ft_strdup(argv[i]);
			args->e_n++;
		}
		i++;
	}
	return (sort_by_flags(&args, flags));
}

t_args	*sorting_args_end_save(int i, int max, char **argv, int flags)
{
	t_args		*args;
	
	if (!(args = create_args(max + 1)))
		return (NULL);
	while (i < max)
	{
		if ((is_dir(argv[i])) && !is_lnk(argv[i]))
		{
			args->dirs[args->d_n] = ft_strdup(argv[i]);
			args->d_n++;
		}
			args->files[args->f_n] = ft_strdup(argv[i]);
			args->f_n++;
		i++;
	}
	return (sort_by_flags(&args, flags));
}
