/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:12:43 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/19 12:21:16 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 && n)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return (((unsigned char)*s1) - ((unsigned char)*s2));
	return (0);
}
