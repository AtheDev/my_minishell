/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:32:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/18 14:56:50 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* permet ve vérifier que l'on retrouve bien une " fermante */
int	check_double_quotes(char *line, int *i)
{
	int	index;
	char	*tmp;
	int	j;

	++*i;
	index = *i;
	j = 0;
	while ((line[*i] != '"' || (line[*i] == '"' &&
		is_escaped(line, *i - 1) == 1)) && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (error_msg(3, '"'));
	if (line[*i] == '"' && is_escaped(line, *i - 1) == 0)
		printf("OK pour \"\n\n");
	tmp = ft_substr(line, index, *i - index);
	if (check_variable(tmp, &j, 1) == 0)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
//	if (check_dollar(line, index, i, env) == 0)
//		return (0);
	return (1);
}

/* permet de vérifier que l'on retrouve bien le ' fermante */
int	check_simple_quote(char *line, int *i)
{
	++*i;
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0')
		return (error_msg(3, '\''));
	if (line[*i] == '\'')
		printf("OK pour \'\n\n");
	return (1);
}

