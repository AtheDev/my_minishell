/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:13:48 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/07 18:13:00 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_end_line(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

int		ft_new_line(char **str, char **line, int ret, int count)
{
	if (ret != 0)
	{
		*line = ft_my_substr(*str, 0, count - 1);
		*str = ft_my_substr(*str, count, ft_strlen(*str) - count);
		return (1);
	}
	*line = *str;
	*str = NULL;
	return (0);
}

char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		if (!(s1 = malloc(sizeof(char))))
			return (NULL);
		s1[0] = '\0';
	}
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (i + j + 1))))
	{
		free(s1);
		return (NULL);
	}
	str[i + j] = '\0';
	while (--j >= 0)
		str[i + j] = s2[j];
	while (--i >= 0)
		str[i] = s1[i];
	if (s1)
		free(s1);
	return (str);
}

char	*ft_my_substr(char *s, int start, int len)
{
	char	*str;
	int		i;
	int		size;

	if (!s)
		return (NULL);
	if ((size = ft_strlen(s)) < start)
	{
		if (!(str = malloc(sizeof(char))))
			return (NULL);
		str[0] = '\0';
	}
	else
	{
		if (!(str = malloc(sizeof(char) * (len + 1))))
			return (NULL);
		i = -1;
		while (++i < len)
			str[i] = s[start + i];
		str[i] = '\0';
	}
	if (start != 0)
		free(s);
	return (str);
}

