/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:08:39 by engooh            #+#    #+#             */
/*   Updated: 2022/03/12 17:09:22 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int ft_cmp(char *charset, char c, t_map *map)
{
	while (charset && *charset)
	{
		if (*charset == c)
		{
			if (*charset == 'C')
				map->colmax++;
			if (*charset == 'P')
				map->playermax++;
			if (*charset == 'E')
				map->exitmax++;
			return (1);
		}
		charset++;
	}
	return (0);
}

/*int	ft_parse(char *str, t_map *map)
{
	int i;
	int x;
	int count;
	int	size;

	i = -1;
	x = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[++i])
	{
		size = 0;
		while (str[i] && str[i] != '\n' && ++size)
			if (!ft_cmp("10CPE\n", str[i], map) || (str[i++] != '1' && !count) )
				return (-2);
		if (str[i] == '\n')
			count++;
		if (!x)
			x = i;

		printf("x = %d\n i = %d\n count = %d\n  i - x = %d\n  x * count = %d\n", x, i, count, i - x, x * count);
		if (str[i - x] != '1' || str[x * count] != '1')
			return (-3);
	}
	if (count < 3)
		return (-4);
	while (str[i - x])
	{
		if (str[i + x] != '1')
			return (-5);
		x--;
	}
	map->x = x;
	map->y = count;
	return (1);
}*/



int	ft_first_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (i);
}

int ft_last_line(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	i--;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '1')
			return (0);
		i--;
	}
	return (count);
}

int	valide_items(char *str, t_map *map)
{
	int i;
	int line;

	map->y = ft_last_line(str);
	map->x = ft_first_line(str);
	if (!map->x || !map->y || map->x == map->y) 
		return (-1);
	i = -1;
	line = 0;
	while (str[++i])
	{
		if (!ft_cmp("10ECP\n", str[i], map))
			return (-1);
		if (str[i] == '\n' && str[i + 1] && str[i + 1] != '1')
			return (-2);
		if (str[i] == '\n' && i && str[i - 1] != '1')
			return (-3);
	}
	return (1);
}

char	*ft_check_map(char *file)
{
	int		fd;
	char	*str;
	int		len;
	char	c;

	len = 0;
	str = NULL;
	fd = open(file, O_RDONLY | O_NOFOLLOW);
	if (fd < 0)
		return (NULL);
	if (errno == EISDIR)
		return (NULL);
	if (errno == EACCES)
		return (NULL);
	if (errno == ELOOP)
		return (NULL);
	if (errno == ENOENT)
		return (NULL);b
	while (read(fd, &c, 1))
		len++;
	close (fd);
	fd = open(file, O_RDONLY | O_NOFOLLOW);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	read(fd, str, len);
	printf("%s\n", str);
	close(fd);
	return (str);
}

void *ft_free(void	*s1, void *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

int	*ft_chardup(char *src, size_t len)
{
	int	*p;
	int	i;

	i = -1;
	p = NULL;
	p = (int *)malloc(len * sizeof(int));
	if (p == NULL)
		return (NULL);
	while (src[++i])
		if (src[i] != '\n')
			p[i] = src[i];
	return (p);
}

t_map *init_map(char *file)
{
	char	*str;
	t_map	*map;

	str = ft_check_map(file);
	if (!str)
		return (NULL);
	map = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (ft_free(str, NULL));
	map->colmax = 0;
	map->exitmax = 0;
	map->playermax = 0;
	if (!valide_items(str, map))
		return (ft_free(str, map));
	map->tab_map = ft_chardup(str, ft_strlen(str));
	return (map);
}
