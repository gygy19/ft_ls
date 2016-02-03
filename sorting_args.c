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

char		**sort_tab(char **tab, size_t tab_size,
	int f(char **, size_t, char *), char *dir)
{
	size_t	id;
	size_t	size_new;
	char	**new_tab;

	size_new = 0;
	new_tab = get_new_tab(tab_size + 1);
	while (size_new < tab_size)
	{
		id = f(tab, tab_size, dir);
		if (tab[id] != NULL)
		{
			new_tab[size_new] = ft_strdup(tab[id]);
			size_new++;
			ft_bzero(tab[id], 1);
		}
	}
	return (new_tab);
}

void		sort_dirs(t_args **args, int flags, char *dir)
{
	char **tmp;

	tmp = NULL;
	if ((*args)->d_n > 0 && flags & FLAG_T)
		tmp = sort_tab((*args)->dirs, (*args)->d_n, sort_by_time, dir);
	else if ((*args)->d_n > 0 && flags & FLAG_R)
		tmp = sort_tab((*args)->dirs, (*args)->d_n, sort_za, "");
	else if ((*args)->d_n > 0)
		tmp = sort_tab((*args)->dirs, (*args)->d_n, sort_az, "");
	free_tab((*args)->dirs, O_DIR);
	if ((*args)->d_n > 0)
		(*args)->dirs = tmp;
}

t_args		*sort_by_flags(t_args **args, int flags, char *dir)
{
	char **tmp;

	tmp = NULL;
	sort_dirs(args, flags, dir);
	if ((*args)->f_n > 0 && flags & FLAG_T && flags & FLAG_U)
		tmp = sort_tab((*args)->files, (*args)->f_n, sort_by_time_u, dir);
	else if ((*args)->f_n > 0 && flags & FLAG_T)
		tmp = sort_tab((*args)->files, (*args)->f_n, sort_by_time, dir);
	else if ((*args)->f_n > 0 && flags & FLAG_R)
		tmp = sort_tab((*args)->files, (*args)->f_n, sort_za, "");
	else if ((*args)->f_n > 0)
		tmp = sort_tab((*args)->files, (*args)->f_n, sort_az, "");
	free_tab((*args)->files, O_DIR);
	if ((*args)->f_n > 0)
		(*args)->files = tmp;
	if ((*args)->e_n > 0)
		tmp = sort_tab((*args)->errors, (*args)->e_n, sort_az, "");
	free_tab((*args)->errors, O_DIR);
	if ((*args)->e_n > 0)
		(*args)->errors = tmp;
	return (*args);
}

t_args		*sorting_args(int i, int max, char **argv, int flags)
{
	t_args	*args;

	if (!(args = create_args(max + 1)))
		return (NULL);
	while (i < max)
	{
		if (argv[i][0] == '\0')
			print_error_zero();
		if ((is_dir(argv[i])) && !(flags & FLAG_D))
		{
			args->dirs[args->d_n] = ft_strdup(argv[i]);
			args->d_n++;
		}
		else if (exist_file(ft_strtrim(argv[i])))
		{
			args->files[args->f_n] = ft_strdup(argv[i]);
			args->f_n++;
		}
		else
			args->errors[args->e_n++] = ft_strdup(argv[i]);
		i++;
	}
	if (flags & FLAG_F)
		return (args);
	return (sort_by_flags(&args, flags, ""));
}

t_args		*sorting_args_end_save(int max, char **argv, int flags, char *dir)
{
	int		i;
	t_args	*args;

	i = 0;
	if (max <= 0)
		return (NULL);
	if (!(args = create_args(max + 1)))
		return (NULL);
	while (i < max)
	{
		if ((is_dir(argv[i])) && !is_lnk(argv[i]) && !(flags & FLAG_D))
		{
			args->dirs[args->d_n] = ft_strdup(argv[i]);
			args->d_n++;
		}
		args->files[args->f_n] = ft_strdup(argv[i]);
		args->f_n++;
		i++;
	}
	if (flags & FLAG_F)
		return (args);
	return (sort_by_flags(&args, flags, dir));
}
