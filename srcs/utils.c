/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:06:16 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/18 14:13:18 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_line(char **line, int i)
{
	while ((*line)[i] != '\0')
	{
		if (ft_isprint((*line)[i]) == 1 && ft_isspace((*line)[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_redir(char *line, int i)
{
	if (line[i] == '<')
	{
		if (line[--i] == ' ')
			while (line[i] == ' ' && i > 0)
				i--;
		if (line[i] == '<' || line[i] == '>')
			return (0);
	}
	if (line[i] == '>')
	{
		if (line[--i] == ' ')
		{
			while (line[i] == ' ' && i > 0)
				i--;
			if (line[i] == '>')
				return (0);
		}
		else if (line[i] == '<')
			return (0);
		else if (line[i] == '>')
		{
			if (line[--i] == ' ')
				while (line[i] == ' ' && i > 0)
					i--;
			if (line[i] == '<' || line[i] == '>')
				return (0);
		}		
	}
	return (1);
}


int	ft_my_strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 && n)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return (((unsigned char)*s1) - ((unsigned char)*s2));
	if ((*s1) != '=')
		return (1);
	return (0);
}

