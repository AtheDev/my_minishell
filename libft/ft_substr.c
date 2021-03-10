/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:16:27 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/10 15:28:57 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size < start)
	{
		if (!(str = malloc(sizeof(char))))
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > (size - start))
		len = size - start;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
