/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 23:32:09 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/24 08:52:53 by jguyet           ###   ########.fr       */
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
	if (size_new == 0 && !(new_tab =\
				(char **)malloc(sizeof(char *) * tab_size)))
		return (NULL);
	new_tab[size_new] = ft_strdup(tab[id]);
	size_new += 1;
	ft_bzero(tab[id], ft_strlen(tab[id]));
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
	if (size_new == 0 && !(new_tab = (char **)malloc(sizeof(char *) * tab_size)))
		return (NULL);
	new_tab[size_new] = ft_strdup(tab[id]);
	size_new += 1;
	ft_bzero(tab[id], ft_strlen(tab[id]));
	if (size_new == tab_size)
		return (new_tab);
	return (sort_tab_az(tab, tab_size, new_tab, size_new));
}

t_args		*create_args(size_t size)
{
	t_args *new;

	new = (t_args *)malloc(sizeof(t_args));
	if (new)
	{
		if (!(new->dirs = (char **)malloc(sizeof(char *) * size))
				|| !(new->files = (char **)malloc(sizeof(char *) * size))
				|| !(new->errors = (char **)malloc(sizeof(char *) * size))
				|| !(new->space = (int *)malloc(sizeof(char *) * size)))
			return (NULL);
		new->d_n = 0;
		new->f_n = 0;
		new->e_n = 0;
		return (new);
	}
	return (NULL);
}

int			exist_file(char *file)
{
	struct stat	stats;

	return ((stat(file, &stats)) == 0);
}

t_args		*sort_by_flags(t_args **args, int flags)
{
	if ((*args)->d_n > 0 && flags & FLAG_r)
		(*args)->dirs = sort_tab_za((*args)->dirs, (*args)->d_n, NULL, 0);
	else if ((*args)->d_n > 0)
		(*args)->dirs = sort_tab_az((*args)->dirs, (*args)->d_n, NULL, 0);
	if ((*args)->f_n > 0 && flags & FLAG_r)
		(*args)->files = sort_tab_za((*args)->files, (*args)->f_n, NULL, 0);
	else if ((*args)->f_n > 0)
		(*args)->files = sort_tab_az((*args)->files, (*args)->f_n, NULL, 0);
	if ((*args)->e_n > 0)
		(*args)->errors = sort_tab_az((*args)->errors, (*args)->e_n, NULL, 0);
	return (*args);
}

t_args		*sorting_args(int i, int max, char **argv, int flags)
{
	t_args		*args;
	DIR			*dirp;

	if (!(args = create_args(max)))
		return (NULL);
	while (i < max)
	{
		if ((dirp = opendir(argv[i])))
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
	DIR			*dirp;

	if (!(args = create_args(max)))
		return (NULL);
	while (i < max)
	{
		if ((dirp = opendir(argv[i])))
		{
			args->dirs[args->d_n] = ft_strdup(argv[i]);
			args->d_n++;
		}
		if (exist_file(argv[i]))
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
