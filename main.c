/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:50 by engooh            #+#    #+#             */
/*   Updated: 2022/03/17 07:23:31 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

unsigned int	get_color_pixel(t_all *all, void *img, int y, int x)
{
	char	*src;
	int		color;

	all->tmp->addr = mlx_get_data_addr(img, &all->tmp->bpp,
			&all->tmp->llg, &all->tmp->edn);
	src = all->tmp->addr + (y * all->tmp->llg + x
			* (all->tmp->bpp / 8));
	color = *(unsigned int *)src;
	return (color);
}

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = all->img->addr + (y * all->img->llg + x * (all->img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_pixel(t_all *all, void *img, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			all->elem->color = get_color_pixel(all, img, i, j);
			if (!(all->elem->color == (0xFF << 24)))
				my_mlx_pixel_put(all, (x) + j,
					(y) + i, all->elem->color);
		}
	}
}

void	draw_grille(t_all *all, void *img, int x_cellule, int y_cellule)
{
	float x;
	float	y;

	all->xpm->img = mlx_xpm_file_to_image(all->mlx, img, &all->xpm->x, &all->xpm->y);
	if (!y_cellule)
	{
		x = all->map->x_start + (x_cellule * WIDTH / 2.4);
		y = (all->map->y_start) + (x_cellule * HEIGHT / 4);
	}
	else
	{
		x = all->map->x_start + (x_cellule - y_cellule) * (WIDTH / 2.4);
		y = all->map->y_start + (x_cellule + y_cellule) * (HEIGHT / 4);
	}
	put_pixel(all, all->xpm->img, x, y);
}

void	*malloc_struct(int flag)
{
	void	*s;

	if (flag == 1)
		s = (t_all *)malloc(sizeof(t_all));
	else if (flag == 2)
		s = (t_data *)malloc(sizeof(t_data));
	else if (flag == 3)
		s = (t_xpm *)malloc(sizeof(t_xpm));
	else if (flag == 4)
		s = (t_elem *)malloc(sizeof(t_elem));
	else if (flag == 5)
		s = (t_map *)malloc(sizeof(t_map));
	if (!s)
		return (NULL);
	return (s);
}

void	*malloc_all(void)
{
	t_all	*all;

	all = (t_all *)malloc_struct(1);
	all->img = (t_data *)malloc_struct(2);
	all->tmp = (t_data *)malloc_struct(2);
	all->xpm = (t_xpm *)malloc_struct(3);
	all->elem = (t_elem *)malloc_struct(4);
	all->map = (t_map *)malloc_struct(5);
	return (all);
}

void	set_elem_info(t_all *all)
{
	all->elem->wall = malloc(sizeof(char));
	if (!all->elem->wall)
		return ;
	all->elem->ground = malloc(sizeof(char));
	if (!all->elem->ground)
		return ;
	all->elem->map = malloc(sizeof(char));
	if (!all->elem->map)
		return ;
	all->elem->wall = "/mnt/nfs/homes/engooh/Tryhard/so_long/so_long-/image/image/isometric_0210.xpm";
	all->elem->ground = "image/stoneSlab.xpm";
}

void	set_map_info(t_all *all, int x, int y)
{
	all->map->w_max = x * WIDTH;
	all->map->h_max = y * HEIGHT;
	all->map->x_start = (x * WIDTH) / 2;
	all->map->y_start = 64;
	all->map->x_line = x;
	all->map->y_line = y;
	all->map->c_map = x * y;
}

void	*init(char *file, int x, int y)
{
	t_all	*all;

	all = malloc_all();
	all->mlx = mlx_init();
	all->map->map = read_to_file(file, &x, &y);
	if (!all->map->map)
		return (NULL);
	set_elem_info(all);
	set_map_info(all, x, y);
	all->img->img = mlx_new_image(all->mlx, all->map->w_max, all->map->h_max);
	all->win = mlx_new_window(all->mlx, all->map->w_max, all->map->h_max, "gosth master");
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bpp, &all->img->llg, &all->img->edn);
	return (all);
}

void print_map(t_all *all, char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				draw_grille(all, all->elem->wall, i, j);
			if (map[i][j] == '0')
				draw_grille(all, all->elem->ground, i, j);
		}
	}
}

int	main(int ac, char **av)
{
	t_all *all;

	all = init(av[ac - 1], 0, 0) ;
	print_map(all, all->map->map);
	mlx_put_image_to_window(all->mlx, all->win, all->img->img, 0, 0);
	mlx_loop(all->mlx);
	return (0);
}
