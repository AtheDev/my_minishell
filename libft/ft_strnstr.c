/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:13:22 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/20 10:33:19 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)&s1[i]);
	while (s1[i] != '\0' && i < len)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s2[j] != '\0' && s1[i + j] == s2[j] && i + j < len)
			{
				++j;
				if (len == 0)
					return (NULL);
				if (s2[j] == '\0')
					return ((char *)&s1[i]);
			}
		}
		++i;
	}
	return (NULL);
}
