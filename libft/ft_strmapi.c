/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:11:40 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/20 10:35:36 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (!(str = ft_strdup(s)))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = (*f)(i, str[i]);
		i++;
	}
	return (str);
}
