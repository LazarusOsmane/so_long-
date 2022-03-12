/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:28:50 by engooh            #+#    #+#             */
/*   Updated: 2022/03/11 23:26:55 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int main(int ac, char **av)
{
	t_all all;

	if (ac != 2)
		return (0);
	all.map = init_map(av[1]);
	if (!all.map)
		return (0);
	printf("x = %d ||| y = %d\n", all.map->x, all.map->y);
	all.map->px = 32;
	all.map->py = 32;
	all.mlx = mlx_init();
	all.win = mlx_new_window(all.mlx, all.map->x * all.map->px, all.map->y * all.map->py, "pacman");
	mlx_loop(all.mlx);
	return (0);
}
