/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:59:39 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/18 14:45:51 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n &&
		(((unsigned char *)(s1))[i]) == (((unsigned char *)(s2))[i]))
	{
		i++;
		if (i == n)
			return (0);
	}
	return ((((unsigned char *)(s1))[i]) - (((unsigned char *)(s2))[i]));
}
