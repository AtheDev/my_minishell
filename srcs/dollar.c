/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:12:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/23 11:15:37 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_variable(char *line, int *i, int quote)
{
	*i += 1;
	while (line[*i] != '\0' && (ft_isalnum(line[*i]) == 1 || line[*i] == '_'))
		(*i)++;
	if (line[*i] == '`')
		printf("> \"Ouvre une ligne en boucle et pas  possible de faire une commande\"\n");
	if (quote == 0 && line[*i] == '\\' && line[*i + 1] == '\0')
		printf("> \"Ouvre une ligne et ré-écris tout à partir de arg[1] \"\n");
	if (line[*i] == '|' && quote == 0)
	{
		printf("> \"Ouvre une ligne et exécute une fois certaines commandes, si commande n'existe pas => renvoie commande introuvable\"\n");
		(*i)--;
		return (1);
	}
	if (quote == 0 && (line[*i] == '(' || line[*i] == ')' || (line[*i] == '>' &&
	line[*i + 1] == '>' && empty_line(&line, *i + 2) == 0) || (((line[*i] == '<'
	|| (line[*i] == '>' && line[*i + 1] != '>'))) && empty_line(&line, *i + 1) == 0)))
		return (error_msg(1, line[*i]));
	if (line[*i] == ';' && quote == 0)
		(*i)--;
	else if (quote == 0)
		(*i)--;
	return (1);
}

int	check_dollar(char **line, int index, int *i, t_env *env)
{
	int	size_tot;

	size_tot = 0;
	while ((*line)[index] != '"' && !is_escaped(*line, index - 1))
	{
		if ((*line)[index] == '$')
		{
			*i = index;
			if (replace_variable(line, i, env) < 0)
				return (0);
			index = ++(*i);
			index--;
		}
		index++;
	}
	*i += 1;
	return (1);
}

int	replace_variable(char **line, int *i, t_env *env)
{
	char	*tmp;
	char	*tmp2;
	int	index;
	int	pos_dollar;
	int	size_var;
	int	j;
	int	ret;
	int	size_tmp;

	index = *i;
	pos_dollar = index;
	tmp = NULL;
	tmp2 = NULL;
	size_var = 0;
	if (ft_isdigit((*line)[*i + 1]) == 1)
	{
		*line = delete_char((*line), i);
		(*i)++;
		*line = delete_char((*line), i);
		return (1);
	}
	while ((*line)[++*i] != '\0' && (ft_isalnum((*line)[*i]) == 1
	|| (*line)[*i] == '_'))
		size_var++;
/*	if (((*line)[*i] == '"' && quote == 0) || (*line)[*i] == '\'' || (*line)[*i] == '`' ||
	(*line)[*i] == '|' || ((*line)[*i] == '\\' && (*line)[*i + 1] == '\0'))
	{
		printf("Erreur n°1\n");
		return (0);
	}*/
/*	if ((*line)[*i] == '(' || (*line)[*i] == ')' || ((*line)[*i] == '>' &&
	(*line)[*i + 1] == '>' && empty_line(line, *i + 2) == 0) || ((((*line)[*i] == '<'
	|| ((*line)[*i] == '>' && (*line)[*i + 1] != '>'))) && empty_line(line, *i + 1) == 0))
		return (error_msg(1, (*line)[*i]));*/
	tmp = malloc(sizeof(char) * (size_var + 1));
	if (tmp == NULL)
		return (-1);
	j = 0;
	while (++index < *i)
		tmp[j++] = (*line)[index];
	tmp[j] = '\0';
//printf("tmp = %s et size_var = %d et *line = %s\n", tmp, size_var, *line);
	ret = search_var_env(&tmp, env, size_var);
//printf("ICI tmp = %s\n", tmp);
	size_tmp = ft_strlen(tmp);
	if (ret == -1)
	{
		free(tmp);
		return (-1);
	}
	if (ret == 0)
	{
		printf("Pas de variable existante\n");
		tmp = ft_substr(*line, 0, pos_dollar);
		tmp2 = ft_substr(*line, pos_dollar + size_var + 1, ft_strlen(*line) - (pos_dollar + size_var + 1));
		if (tmp == NULL || tmp2 == NULL)
		{
			*line = process_free(tmp, tmp2);
			return (-1);
		}
		*line = ft_strjoin(tmp, tmp2);
		if (*line == NULL)
		{
			process_free(tmp, tmp2);
			return (-1);
		}
	}
	if (ret == 1)
	{
		printf("Variable trouvée et échangée\n");
		//printf("before swap_var_env line = %s\n", *line);
		if (swap_var_env(&tmp, line, pos_dollar, size_var) == -1)
		{
			process_free(tmp, tmp2);
			return (-1);
		}
		//printf("after swap_var_env line = %s\n", *line);
	}
//printf("tmp = %s et line = %s\n", tmp, *line);
	process_free(tmp, tmp2);
	if (ret == 0)
		*i = pos_dollar - 1;
	else
		*i = --(*i) + size_tmp - size_var - 2;
//printf("*line = %s\n", *line);
	return (1);
}

