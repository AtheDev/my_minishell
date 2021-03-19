/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_escaped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:12:26 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/18 16:12:48 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	db_quotes(char *str, int i)
{
	if (str[i] == '"' && is_escaped(str, i - 1) == 0)
		return (1);
	return (0);
}

int	sp_quote(char *str, int i)
{
	if (str[i] == '\'' && is_escaped(str, i - 1) == 0)
		return (1);
	return (0);
}

int	dollar(char *str, int i)
{
	if (str[i] == '$' && is_escaped(str, i - 1) == 0)
		return (1);
	return (0);
}

int	sep_cmd(char *str, int i)
{
	if ((str[i] == ';' || str[i] == '|') && is_escaped(str, i - 1) == 0)
		return (1);
	return (0);
}

int	redir(char *str, int i)
{
	if ((str[i] == '<' || str[i] == '>') && is_escaped(str, i - 1) == 0)
		return (1);
	return (0);
}
