/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:14:44 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/20 10:39:38 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sep(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	while (ft_sep(*s1, set) && *s1 != '\0')
		s1++;
	while (s1[i] != '\0')
	{
		if (ft_sep(s1[i], set))
			j++;
		else
			j = 0;
		i++;
	}
	i = i - j;
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
		str[i] = s1[i];
	return (str);
}
