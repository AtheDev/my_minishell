/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:14:32 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/22 19:33:08 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* permet de récupérer la valeur de la var et de l'enregistrer dans tmp */
int	save_value(char **tmp, char *env)
{
	int	count;
	int	i;
	int	index;

	i = 0;
	while (env[i] != '=')
		i++;
	index = i + 1;
	count = 0;
	while (env[++i] != '\0')
		count++;
	*tmp = ft_substr(env, index, count);
//	*tmp = ft_strjoin("\"", *tmp);
//	*tmp = ft_strjoin(*tmp, "\"");
	if (*tmp == NULL)
		return (0);
	return (1);
}

/* ajoute la fin de la line à la nouvelle line */
char	*add_str(char *str, char *line, int pos)
{
	char	*tmp;
	int	size_line;
	int	size_str;
	int	i;

	size_line = ft_strlen(line) - pos;
	size_str = ft_strlen(str);
	tmp = malloc(sizeof(char) * (size_str + size_line + 1));
	if (tmp == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != '\0')
		tmp[i] = str[i];
	while (i < (size_str + size_line))
		tmp[i++] = line[pos++];
	tmp[i] = '\0';
	return (tmp);
}

/* permet de ré-écrire line avec l'échange de la valeur de $var par sa value */
int	swap_var_env(char **tmp, char **line, int pos, int size_var)
{
	int	size_tmp;
	char	*str;

	size_tmp = ft_strlen(*tmp);
	str = ft_substr(*line, 0, pos);
	if (str == NULL)
		return (-1);
	str = ft_strjoin(str, *tmp);
	if (str == NULL)
		return (-1);
	str = add_str(str, *line, size_var + pos + 1);
	if (str == NULL)
		return (-1);
//	free(*line);
	*line = str;
	return (1);
}

/* recherche si la var d'env contenue dans tmp existe si oui on récupère la valeur*/
int	search_var_env(char **tmp, t_env *env, int size_tmp)
{
	int	i;

	i = 0;
	while (env->var_env[i] != NULL)
	{
		if (ft_my_strncmp(env->var_env[i], *tmp, size_tmp) == 0)
		{
		//	printf("env->var_env[%d] = %s\n", i, env->var_env[i]);
			free(*tmp);
			*tmp = NULL;
			if (save_value(tmp, env->var_env[i]) == 0)
				return (-1);
		//	printf("after save_value tmp = %s\n", *tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

