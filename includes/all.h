/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 21:02:52 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/24 08:59:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

#include "libft.h"
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

# define FLAG_a 1024
# define FLAG_l 2048
# define FLAG_r 4096
# define FLAG_R 8192
# define FLAG_1 16384
# define FLAG_t 32768
# define FLAG_PREFIX 65536
# define FLAG_ERROR 131072

# define START_FLAG 1024
# define MAX_FLAG 131073
										/*##############
										#   flaging.c  #
										##############*/

int		started_argc(int argc, char **argv);
int		add_flags(int flags, int part_flags);
int		add_part(char c);
int		get_flag_part(int i, int argc, char **argv, int put);
int		verif_flags(int argc, char **argv);

										/*################
										# sorting_args.c #
										################*/

typedef struct		s_args
{
		char		**dirs;
		char		**files;
		char		**errors;
		int			f_n;
		int			d_n;
		int			e_n;
		int			*space;
}					t_args;

t_args	*sorting_args(int i, int max, char **argv, int flags);
t_args	*sorting_args_end_save(int i, int max, char **argv, int flags);
int		exist_file(char *file);
										/*###############
										# print_error.c #
										###############*/

void	print_error_dir_or_file(t_args *args);
void	print_flag_error(int c);


void	print_files(t_args *args, int flags, int win_size);

t_args	*print_dir(char *dir, int flags, int win_size);
#endif
