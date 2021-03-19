/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:12:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/18 15:23:27 by adupuy           ###   ########.fr       */
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

/*int	check_dollar(char **line, int index, int *i, t_env *env)
{
	int	size_tot;

	size_tot = 0;
	while ((*line)[index] != '"' && !is_escaped(*line, index - 1))
	{
		if ((*line)[index] == '$')
		{
			*i = index;
			if (replace_variable(line, i, env, 1) < 0)
				return (0);
			index = ++(*i);
			index--;
		}
		index++;
	}
	*i += 1;
	return (1);
}

int	replace_variable(char **line, int *i, t_env *env, int quote)
{
	char	*tmp;
	int	index;
	int	pos_dollar;
	int	size_var;
	int	j;
	int	ret;
	int	size_tmp;

	index = *i;
	pos_dollar = index;
	tmp = NULL;
	size_var = 0;
	while ((*line)[++*i] != '\0' && (ft_isalnum((*line)[*i]) == 1
	|| (*line)[*i] == '_'))
		size_var++;
	if (((*line)[*i] == '"' && quote == 0) || (*line)[*i] == '\'' || (*line)[*i] == '`' ||
	(*line)[*i] == '|' || ((*line)[*i] == '\\' && (*line)[*i + 1] == '\0'))
	{
		printf("Erreur n°1\n");
		return (0);
	}
	if ((*line)[*i] == '(' || (*line)[*i] == ')' || ((*line)[*i] == '>' &&
	(*line)[*i + 1] == '>' && empty_line(line, *i + 2) == 0) || ((((*line)[*i] == '<'
	|| ((*line)[*i] == '>' && (*line)[*i + 1] != '>'))) && empty_line(line, *i + 1) == 0))
		return (error_msg(1, (*line)[*i]));
	tmp = malloc(sizeof(char) * (size_var + 1));
	if (tmp == NULL)
		return (-1);
	j = 0;
	while (++index < *i)
		tmp[j++] = (*line)[index];
	tmp[j] = '\0';
printf("tmp = %s et size_var = %d\n", tmp, size_var);
	ret = search_var_env(&tmp, env, size_var);
	size_tmp = ft_strlen(tmp);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		printf("Pas de variable existante\n");
		*line = add_char(*line, &pos_dollar, '"', 0);
		pos_dollar += size_var;
		*line = add_char(*line, &pos_dollar, '"', 0 );
	
	//	return (0);
	}
	if (ret == 1)
	{
		printf("Variable trouvée et échangée\n");
		printf("before swap_var_env line = %s\n", *line);
		swap_var_env(&tmp, line, pos_dollar, size_var);
		printf("after swap_var_env line = %s\n", *line);
		
	}
printf("tmp = %s et line = %s\n", tmp, *line);
	if (tmp != NULL)
		free(tmp);
	if (ret == 0)
		*i = pos_dollar - 2;
	else
		*i = --(*i) + size_tmp - size_var - 1;
	return (1);
}*/

