/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:40:59 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/22 10:45:41 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isredir(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

int		moving_forward(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"' || (str[i] == '"' && is_escaped(str, i - 1) == 1))
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	else if (ft_isredir(str, i) == 2)
		i++;
	else if (ft_isredir(str, i) == 1)
		return (i);
	else
	{
		i++;
		while (str[i] != ' ' ||
		(str[i] == ' ' && is_escaped(str, i - 1) == 1))
			i++;
		i--;
	}
	return (i);
}

int		count_word(char *str, int i, int count, int num)
{
	int	j;
	int	k;

	j = 0;
	k = i;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && is_escaped(str, i - 1) == 0)
			i = moving_forward(str, i);
		else if (str[i] == '\'' && is_escaped(str, i - 1) == 0)
			i = moving_forward(str, i);
		else if (ft_isspace(str[i]) == 1 && is_escaped(str, i - 1) == 0)
		{
			j = i - k;
			if (num == 1)
				return (j);
			count++;
		}
		else
			i = moving_forward(str, i);
		i++;
	}
	return (count);
}

char	*new_str(char *str, int i, int size)
{
	char	*tmp;
	int		count;

	tmp = malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	count = 0;
	while (count < size)
		tmp[count++] = str[i++];
	tmp[count] = '\0';
	return (tmp);
}

char	**my_split(char *str, int j)
{
	int		nb_word;
	int		nb_char;
	char	**split;
	int		i;

	nb_word = count_word(str, 0, 0, 0);
	split = malloc(sizeof(char *) * nb_word);
	if (split == NULL)
		return (NULL);
	i = 0;
	while (++j < (nb_word - 1))
	{
		nb_char = count_word(str, i, 1, 1);
		split[j] = new_str(str, i, nb_char);
		if (split[j] == NULL)
		{
			split = ft_free(split, j);
			return (split);
		}
		i = i + nb_char + 1;
	}
	split[j] = NULL;
	return (split);
}
