/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:31:10 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/29 18:05:23 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;
	size_t	i;

	size *= count;
	if (!(new = malloc(sizeof(char) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = 0;
		i++;
	}
	return ((void *)new);
}
