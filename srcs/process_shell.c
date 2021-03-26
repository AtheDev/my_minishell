/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:34:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/26 11:45:34 by adupuy           ###   ########.fr       */
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

char	*edit_arg(char *str, t_env *env)
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
			/*	if ((char_protec(str[i], CHAR_PROTEC) == 1 &&
				is_escaped(str, i - 1) == 1) ||
				(char_protec(str[i], META_CHAR) == 1 &&
				is_escaped(str, i - 1) == 1))
				{
					if (str[i] == '\\')
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
				i++;*/
				if (str[i] == '\\' && str[i + 1] == '\\')
				{
					if ((str = delete_char(str, &i)) == NULL)
						return (NULL);
					i++;
					printf("i1 => str = %s et str[%d] = %c\n", str, i, str[i]);
				}
				else if (str[i] == '\\' && str[i + 1] != '\\')
				{
					if ((str = delete_char(str, &i)) == NULL)
						return (NULL);
					i++;
					printf("2 => str = %s et str[%d] = %c\n", str, i, str[i]);
				}
				else if (str[i] == '$')
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

int	analysis_arg(t_env *env, t_list_cmd **cmd, int i)
{
	char	*tmp;

	tmp = (*cmd)->arg_cmd[i];
	printf("tmp = %s\n", tmp);
	(*cmd)->arg_cmd[i] = edit_arg(tmp, env);
	printf("arg[%d] = %s\n", i, (*cmd)->arg_cmd[0]);
	return (1);
}

int	process_simple_cmd(t_env *env, t_list_cmd **cmd)
{
	if (ft_strncmp((*cmd)->arg_cmd[0], "echo", 5) == 0)
	{
		printf("ECHO\n");
		ft_echo((*cmd)->arg_cmd, env);
	}
	if (ft_strncmp((*cmd)->arg_cmd[0], "pwd", 4) == 0)
	{
		printf("PWD\n");
		ft_pwd((*cmd)->arg_cmd, env);
	}
	if (ft_strncmp((*cmd)->arg_cmd[0], "env", 4) == 0)
	{
		printf("ENV\n");
		ft_env((*cmd)->arg_cmd, env);
	}
	if (ft_strncmp((*cmd)->arg_cmd[0], "unset", 6) == 0)
	{
		printf("UNSET\n");
		ft_unset((*cmd)->arg_cmd, &env);
	}
	if (ft_strncmp((*cmd)->arg_cmd[0], "export", 7) == 0)
	{
		printf("EXPORT\n");
		ft_export((*cmd)->arg_cmd, &env);
	}
	if (ft_strncmp((*cmd)->arg_cmd[0], "cd", 3) == 0)
	{
		printf("CD\n");
		ft_cd((*cmd)->arg_cmd, &env);
	}
	if (ft_strncmp((*cmd)->arg_cmd[0], "exit", 5) == 0)
	{
		printf("EXIT\n");
		ft_exit((*cmd)->arg_cmd, &env);
	}
	return (1);
}

int	process_shell(t_env *env, t_list_cmd **cmd)
{
	analysis_arg(env, cmd, 0);
	if ((*cmd)->pipe == 0 && (*cmd)->nb_redir == 0)
		process_simple_cmd(env, cmd);

	return (1);
}
