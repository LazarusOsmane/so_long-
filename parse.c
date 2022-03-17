/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:13:43 by engooh            #+#    #+#             */
/*   Updated: 2022/03/17 05:37:39 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	*ft_free(void *s)
{
	if (s)
		free(s);
	s = NULL;
	return (s);
}

int    errno_check(void)
{
    if (errno == EACCES)
        return (-1);
    if (errno == ENAMETOOLONG)
        return (-1);
    if (errno == ENFILE)
        return (-1);
    if (errno == ENOENT)
        return (-1);
    return (1);
}

void	*ft_malloc(int size, int size_of)
{
	void	*s;

	s = malloc(size_of * size);
	if (!s)
		return (NULL);
	return (s);
}

int	ft_strcpy1(char *s1, char *s2)
{
	int	i;

	i = -1;
	if (!s2 || !s1)
		return (0);
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (i);
}

int ft_strcmp(char *charset, char c)
{
	int i;

	if (!c)
		return (0);
	i = 0;
	while (charset[i] != c)
		i++;
	if (!charset[i])
		return (0);
	i++;
	return (i);
}

char	*ft_strjoin1(char *s1, char *s2, int len)
{
	char	*new;

	if (!s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (len));
	if (!new)
		return (NULL);
	ft_strcpy1(new + ft_strcpy1(new, s1), s2);
	if (s1)
		free(s1);
	return (new);
}

char	*get_next_line(int fd)
{
	int     ret;
	int     len;
	char    *line;
	char    buf[2];

	ret = 1;
	len = 1;
	line = NULL;
	buf[0] = '\0';
	while (ret && *buf != '\n')
	{
		ret = read(fd, buf, 1);
		len += ret;
		buf[1] = '\0';
		line = ft_strjoin1(line, buf, len);
	}
	if (ret <= 0 && !*buf)
	{
		return (ft_free(line));
	}
	return (line);
}

char **check_map(char **tab_map, int nbr_line)
{
	(void)nbr_line;
	return (tab_map);
}

char    **read_to_file(char *file, int *x, int *y)
{
	int		fd;	
	char	*map;
	char	*line;
	int		nbr_line;
	int		size_map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = NULL;
	nbr_line = 0;
	size_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (check_map(ft_split(map, '\n'), nbr_line)); // rajouter ft_split pour parser la map
		*y = ft_strlen(line);
		size_map += *y;
		map = ft_strjoin1(map, line, size_map + 1);
		free(line);
		*x += nbr_line++;
	}
	return (NULL);
}
