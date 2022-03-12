/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:25:02 by engooh            #+#    #+#             */
/*   Updated: 2022/03/12 17:27:59 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "/usr/include/X11/X.h"
# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"
# include <errno.h>

# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307

typedef struct s_map
{
	int	colmax;
	int	playermax;
	int	exitmax;
	int	x;
	int	y;
	int	px;
	int	py;
	int	*tab_map;
}	t_map;

typedef struct s_xpm
{
	void	*sol;
	void	*mur;
	void	*colt;
	void	*exit;
	void	*ph_close;
	void	*ph_open;
	void	*pb_close;
	void	*pb_open;
	void	*pr_close;
	void	*pr_open;
	void	*pl_close;
	void	*pl_open;
	void	***enemy;
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

typedef struct s_all
{
	void			*mlx;
	void			*win;
	void			*img;
	t_player		*player;
	t_enemy			*enemis;
	t_xpm			*xpm;
	t_map			*map;
}	t_all;

char	*ft_check_map(char *file);
t_map	*init_map(char *file);
#endif 
