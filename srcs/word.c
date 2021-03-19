/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:22:55 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/18 19:50:36 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_space(char **cmd, int i)
{
	while ((*cmd)[++i + 1] != '\0')
	{
		if ((*cmd)[i] != '"' && (*cmd)[i] != ' ' && (*cmd)[i] != '\'')
		{
			while ((((*cmd)[i] != ' ' && (*cmd)[i] != '"' &&
			(*cmd)[i] != '\'') ||
			((*cmd)[i] == '"' && is_escaped(*cmd, i - 1) == 1) ||
			((*cmd)[i] == ' ' && is_escaped(*cmd, i - 1) == 1) ||
			((*cmd)[i] == '\'' && is_escaped(*cmd, i - 1) == 1))
			/*&& (*cmd)[i] != ';'*/ && (*cmd)[i + 1] != '\0')
				i++;
			--i;
		}
		else if ((*cmd)[i] == '"' && is_escaped(*cmd, i - 1) == 0)
		{
			i++;
			while (((*cmd)[i] != '"' || ((*cmd)[i] == '"' &&
			is_escaped(*cmd, i - 1) == 1)))
				i++;
		}
		else if ((*cmd)[i] == '\'' && is_escaped(*cmd, i - 1) == 0)
		{
			i++;
			while ((*cmd)[i] != '\'')
				i++;
		}
		else if ((*cmd)[i] == ' ' && is_escaped(*cmd , i - 1) == 0)
		{
			i++;
			while ((*cmd)[i] == ' '  && (*cmd)[i] != '\0')
			{
				*cmd = delete_char(*cmd, &i);
				if (*cmd == NULL)
					return (error_msg(2, ' '));
				++i;
			}
			i--;
		}
	}
	return (1);
}

int	join_word(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while((*cmd)[i] != '\0')
	{
		if ((*cmd)[i] == '"' && is_escaped(*cmd, i - 1) == 0)
		{
			i++;
			while (((*cmd)[i] != '"' || ((*cmd)[i] == '"' &&
			is_escaped(*cmd, i - 1) == 1)) && (*cmd)[i] != '\0')
				i++;
			if ((*cmd)[i] == '"' && (*cmd)[i + 1] == '"')
			{
				while (count < 2)
				{
					*cmd = delete_char(*cmd, &i);
					printf("la -> *cmd[%d] = %c\n", i, (*cmd)[i]);
					i++;
					count++;
				}
				printf("OK -> *cmd = %s\n", *cmd);
			}
		}
		i++;
	}
	return (1);
}
