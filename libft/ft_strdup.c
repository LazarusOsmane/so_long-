/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <erickngooh.1@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:10:17 by engooh            #+#    #+#             */
/*   Updated: 2021/12/03 13:28:12 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	l;

	l = ft_strlen(s1) + 1;
	p = malloc(l * sizeof(char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, l);
	return (p);
}
