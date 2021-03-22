/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:08:14 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/22 14:06:01 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analysis_quote(char *line, int *i)
{
	if (line[*i] == '"')
	{
		if (check_double_quotes(line, i) == 0)
			return (0);
	}
	if (line[*i] == '\'')
	{
		if (check_simple_quote(line, i) == 0)
			return (0);
	}
	return (1);
}

int	analysis_sep(char **line, int *i, int *start_cmd, t_list **cmd)
{
	if (before_char(*line, *i) == 0)
		return (error_msg(1, (*line)[*i]));
	*line = add_char(*line, i, (*line)[*i], 1);
	if (*line == NULL)
		return (error_msg(2, ' '));
	save_cmd_tmp(cmd, *line, *start_cmd, *i);
	*start_cmd = *i + 1;
	return (1);
}

int	analysis_redir(char **line, int *i)
{
	if (empty_line(line, *i) == 0 || check_redir(*line, *i) == 0)
		return (error_msg(1, (*line)[*i]));
	if ((*line)[*i] == '>' && (*line)[*i + 1] == '>')
		*line = add_char(*line, i, (*line)[*i], 2);
	else
		*line = add_char(*line, i, (*line)[*i], 1);
	if (*line == NULL)
		return (error_msg(2, ' '));
	return (1);
}

int	analysis_line(char **line, int i, t_list **cmd)
{
	int	start_cmd;
	int	ret;

	start_cmd = 0;
	if (empty_line(line, 0) == 0)
		return (0);
	while ((*line)[++i] != '\0')
	{
		ret = 1;
		if (db_quotes(*line, i) == 1 || sp_quote(*line, i) == 1)
			ret = analysis_quote(*line, &i);
		else if ((*line)[i] == '#' && (*line)[i - 1] == ' ' &&
		is_escaped(*line, i - 2) == 0)
			*line = ft_substr(*line, 0, i);
		else if (dollar(*line, i) == 1 && (*line)[i + 1] != '\0'
		&& ft_isspace((*line)[i + 1]) == 0)
			ret = check_variable(*line, &i, 0);
		else if (sep_cmd(*line, i) == 1)
			ret = analysis_sep(line, &i, &start_cmd, cmd);
		else if (redir(*line, i) == 1)
			ret = analysis_redir(line, &i);
		if (ret < 1)
			return (ret);
	}
	return (1);
}
