/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 21:02:52 by jguyet            #+#    #+#             */
/*   Updated: 2016/01/26 04:48:55 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include "libft.h"
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <sys/xattr.h>
# include <unistd.h>

# define FLAG_A 1024
# define FLAG_L 2048
# define FLAG_R 4096
# define FLAG_RR 8192
# define FLAG_1 16384
# define FLAG_T 32768
# define FLAG_PREFIX 65536
# define FLAG_ERROR 131072
# define FLAG_O 262144
# define FLAG_G 524288
# define FLAG_GG 1048576
# define FLAG_F 2097152
# define FLAG_D 4194304
# define FLAG_U 8388608
# define FLAG_FF 16777216

# define START_FLAG 1024
# define MAX_FLAG 16777217

# define O_DIR 4096

# define COLOR_DIR "\033[36m"
# define COLOR_P_DIR "\033[33m"
# define COLOR_EXE "\033[31m"
# define COLOR_LNK "\033[35m"
# define COLOR_DEV "\033[7;49;33m"
# define COLOR_END "\033[00m"

typedef struct	s_args
{
	char		**dirs;
	char		**files;
	char		**errors;
	int			f_n;
	int			d_n;
	int			e_n;
	int			*space;
	int			total;
	int			size;
}				t_args;

int				started_argc(int argc, char **argv);
int				add_flags(int flags, int part_flags);
int				add_part(char c);
t_args			*create_args(size_t size);
int				get_flag_part(int i, int argc, char **argv, int put);
int				verif_flags(int argc, char **argv);
t_args			*sorting_args(int i, int max, char **argv, int flags);
t_args			*sorting_args_end_save(int max, char **argv,\
				int flags, char *dir);
void			print_error_dir_or_file(t_args *args);
void			print_flag_error(int c);
void			print_error_malloc(char *txt);
void			print_files(t_args *args, int flags, int win_size,\
				char *dir);
void			print_files_l(t_args *args, int i, char *dir, int flags);
void			print_dir(char *dir, int flags, int w_s, int i);
int				get_size_args(t_args *args, int line);
size_t			get_size(void);
size_t			exist_file(char *file);
size_t			is_dir(char *dir);
DIR				*open_directory(char *dir);
char			**get_new_tab(int size);
int				is_lnk(char *dir);
void			free_tab(char **tab, int size);
void			free_args(t_args *args);
size_t			have_right_open(char *dir);
char			*end_slash(char *dir);
void			print_error_zero(void);
void			read_args(t_args *args, int flags, int win_size,\
				int first);
void			print_length(t_args *args, int flags, int win_size,\
				char *dir);
int				get_ll(int line, t_args *args);
int				get_line(int win_size, int long_work);
int				get_long_work(t_args *args);
int				print_rdev(char *file, char *dir, t_args *args);
void			print_lnk(char *file, char *dir, int space);
int				get_len_pwd(t_args *args, int i, char *dir);
int				get_len_grp(t_args *args, int i, char *dir);
void			print_grp(char *file, char *dir, int space);
void			print_perm(char *file);
void			get_total_blocks(t_args *args, char *dir, int flags);
int				get_space_lnk(t_args *args, int i, char *dir);
int				get_space_mo(t_args *args, int i, char *dir);
void			print_mo(char *file, char *dir, int space);
void			put_attr(char *file);
void			put_color_p_dir(char *dir, int flags);
void			put_color_type(char *dir, char *file, int flags, int l);
void			put_color_type_length(char *dir, char *file, int flags);
int				sort_az(char **tab, size_t tab_size, char *dir);
int				sort_za(char **tab, size_t tab_size, char *dir);
int				sort_by_time(char **tab, size_t tab_size, char *dir);
int				get_time(char *file, char *dir);
int				is_rdev(char *file);
char			*get_infos(char *file, char *dir);
int				l_mjr(t_args *args, int i, char *dir, int major);
int				get_time_u(char *file, char *dir);
int				sort_by_time_u(char **tab, size_t tab_size, char *dir);
int				is_exe(char *file);
#endif
