/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:41:38 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/24 10:26:55 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_escaped(char *line, int i)
{
	int	nb_backslash;

	nb_backslash = 0;
	if (line[i] != '\\')
		return (0);
	while (line[i] == '\\' && i-- >= 0)
		nb_backslash++;
	if (nb_backslash % 2 == 0)
		return (0);
	return (1);
}

int		before_char(char *line, int i)
{
	while (--i >= 0)
	{
		if (line[i] != ' ' &&
			((line[i] == ';' && is_escaped(line, i - 1) == 0)
			|| (line[i] == '|' && is_escaped(line, i - 1) == 0)
			|| (line[i] == '<' && is_escaped(line, i - 1) == 0)
			|| (line[i] == '>' && is_escaped(line, i - 1) == 0)
			|| (line[i] == '(' && is_escaped(line, i - 1) == 0)
			|| (line[i] == ')' && is_escaped(line, i - 1) == 0)
			|| (line[i] == '&' && is_escaped(line, i - 1) == 0)))
			return (0);
		if (line[i] != ' ')
			return (1);
	}
	return (0);
}

char	*process_free(char *tmp, char *tmp2)
{
	if (tmp != NULL)
		free(tmp);
	if(tmp2 != NULL)
		free(tmp2);
	return (NULL);
}

/*
   si space = 0 => ne pas mettre d'espace autour du 'c'
   si space = 1 => mettre un espace autour du 'c' = '>'|'<'
   si space = 2 => mettre un espace autour du 'c' = '>>'
*/
char	*add_char(char *line, int *pos, char c, int space)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line, 0, *pos);
	tmp2 = ft_substr(line, *pos + space, (ft_strlen(line) - (*pos + space)));
	free(line);
	if (tmp == NULL || tmp2 == NULL)
		return (process_free(tmp, tmp2));
	tmp = strjoin_char(tmp, c, space);
	if (tmp == NULL)
		return (process_free(tmp, tmp2));
	line = ft_strjoin(tmp, tmp2);
	process_free(tmp, tmp2);
	if (line == NULL)
		return (process_free(tmp, tmp2));
	*pos += 2;
	return (line);
}

char	*delete_char(char *line, int *pos)
{
	int	size;
	char	*tmp;
	char	*tmp2;

	size = ft_strlen(line);
	tmp = ft_substr(line, 0, *pos);
	tmp2 = ft_substr(line, *pos + 1, size - *pos - 1);
	free(line);
	if (tmp == NULL || tmp2 == NULL)
		return (process_free(tmp, tmp2));
	line = ft_strjoin(tmp, tmp2);
	process_free(tmp, tmp2);
	if (line == NULL)
		return (process_free(tmp, tmp2));
	*pos = *pos - 1;
	return (line);
}


char	*strjoin_char(char *s1, char c, int space)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	if (!s1 || !c)
		return (NULL);
	size = 2;
	if (space == 1)
		size += 2;
	if (space == 2)
		size += 3;
	str = malloc(sizeof(char) * (ft_strlen(s1) + size));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	if (space > 0)
		str[j++] = ' ';
	str[j++] = c;
	if (space == 2)
		str[j++] = c;
	if (space > 0)
		str[j++] = ' ';
	str[j] = '\0';
	free(s1);
	return (str);
}

