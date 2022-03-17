/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:25:02 by engooh            #+#    #+#             */
/*   Updated: 2022/03/17 04:49:54 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define HEIGHT 64
# define WIDTH 64
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "libft/libft.h"
# ifdef __linux__
#  include "./minilibx-linux/mlx.h"
#  include "/usr/include/X11/X.h"
# endif
# ifdef __APPLE__
#  include "minilibx_opengl_20191021/mlx.h"
# endif

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307

typedef struct s_xpm
{
	int		x;
	int		y;
	void	*img;
	int		format;
}	t_xpm;

typedef struct s_player
{
	int	pos;
	int	dir;
	int	prev;
	int	input;
	int	count;
	int	moves;
}	t_player;

typedef struct s_enemy
{
	int	pos;
	int	dir;
	int	prev;
}	t_enemy;

typedef struct s_map
{
	int		w_max;
	int		h_max;
	int		c_map;
	int		x_start;
	int		y_start;
	int		x_line;
	int		y_line;
	char	**map;
}	t_map;

typedef struct s_elem
{
	char	*wall;
	char	*ground;
	char	*map;
	int		color;
}	t_elem;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		llg;
	int		edn;
}	t_data;

typedef struct s_all
{
	void			*mlx;
	void			*win;
	t_data			*img;
	t_data			*tmp;
	t_xpm			*xpm;
	t_map			*map;
	t_elem			*elem;
}	t_all;

char	*ft_check_map(char **tab_map, char *file);
//t_map	*init_map(char *file);
char	**read_to_file(char *file, int *x, int *y);
#endif
