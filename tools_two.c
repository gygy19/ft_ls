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

void		free_tab(char **tab)
{
	int i;

	if (!tab || !tab[0])
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

void		free_args(t_args *args)
{
	free_tab(args->files);
	free_tab(args->errors);
	free_tab(args->dirs);
	free(args);
}
