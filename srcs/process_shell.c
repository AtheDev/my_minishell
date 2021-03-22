/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:34:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/22 14:29:39 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_protec(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*first_arg(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			str = delete_char(str, &i);
			i++;
			while (str[i] != '"' ||
			(str[i] == '"' && is_escaped(str, i - 1) == 1))
			{
				if (char_protec(str[i], CHAR_PROTEC) == 1 &&
				str[i] != '\'' && is_escaped(str, i - 1) == 1)
				{
					i--;
					str = delete_char(str, &i);
					i++;
					if (str[i + 1] == '"')
					{
						i++;
						str = delete_char(str, &i);
						break;
					}
				}
				else if (str[i] == '$' && is_escaped(str, i - 1) == 0)
				{
					if (replace_variable(&str, &i, env) == -1)
						return (NULL);
				}
				i++;
			}
			if (str[i] == '"')
				str = delete_char(str, &i);
		}
		else if (str[i] == '\'')
		{
			str = delete_char(str, &i);
			i++;
			while (str[i] != '\'')
				i++;
			if ((str = delete_char(str, &i)) == NULL)
				return (NULL);
		}
		else
		{
			while (((str[i] != '"' && str[i] != '\'') ||
			(str[i] == '"' && is_escaped(str, i - 1) == 1) ||
			(str[i] == '\'' && is_escaped(str, i - 1) == 1)) && str[i] != '\0')
			{
				if (char_protec(str[i], CHAR_PROTEC) == 1 &&
				is_escaped(str, i - 1) == 1)
				{
					i--;
					if ((str = delete_char(str, &i)) == NULL)
						return (NULL);
					i++;
				}
				else if (str[i] == '$' && is_escaped(str, i - 1) == 0)
				{
					if (replace_variable(&str, &i, env) == -1)
						return (NULL);
				}
				i++;
			}
			i--;
		}
		i++;
	}
printf("FIN => str = %s\n", str);
	return (str);
}

int	analysis_first_arg(t_env *env, t_list_cmd **cmd)
{
	char	*tmp;

	tmp = (*cmd)->arg_cmd[0];
	printf("tmp = %s\n", tmp);
	(*cmd)->arg_cmd[0] = first_arg(tmp, env);
	printf("arg[0] = %s\n", (*cmd)->arg_cmd[0]);
	return (1);
}

int	process_shell(t_env *env, t_list_cmd **cmd)
{
	analysis_first_arg(env, cmd);
//	char	*tmp;

//	if (cmd->pipe == 0 && cmd->nb_redir == 0)
	//	process_simple_cmd();

	return (1);
}
