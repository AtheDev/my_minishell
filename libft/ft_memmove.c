/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:00:51 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/20 10:17:36 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	if (((unsigned char *)(dst)) > ((unsigned char *)(src)))
	{
		while (i < n)
		{
			((unsigned char *)(dst))[n - 1] = ((unsigned char *)(src))[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)(dst))[i] = ((unsigned char *)(src))[i];
			i++;
		}
	}
	return ((void *)dst);
}
