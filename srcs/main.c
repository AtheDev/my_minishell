/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:21:52 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/19 10:28:46 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg_cmd(char **);

void	print_struct(t_list_cmd *cmd)
{
//	t_list_cmd	*first;
printf("=>=> cmd = %s\n", cmd->cmd);
//	first = cmd;
	while (cmd->next_cmd != NULL)
	{
		printf("LA cmd->cmd = %s\n", cmd->cmd);
		print_arg_cmd(cmd->arg_cmd);
		printf("2\n");
		cmd = cmd->next_cmd;
		printf("LA cmd->cmd = %s et cmd->next_cmd = %d\n", cmd->cmd, cmd->next_cmd == NULL ? 1 : 0);
	
		if (cmd->next_cmd == NULL)
			printf("NULLLLLL\n");
	//	printf("ICI cmd->next_cmd = %s\n", cmd->next_cmd->cmd);
	}
printf("1\n");
	print_arg_cmd(cmd->arg_cmd);
//	printf("result = %d\n", cmd->previous_cmd->nb_redir);
//	cmd = first;
}

void	print_arg_cmd(char **arg_cmd)
{
	int	i;

	i = -1;
	while (arg_cmd[++i] != NULL)
		printf("arg_cmd[%d] = %s\n", i, arg_cmd[i]);
	printf("arg_cmd[%d] = %s\n", i, arg_cmd[i]);
}

/*void	add_sep_word(char **cmd)
{
	int	i;
	int	j;
	int	var;

	i = 0;
	j = 0;
	var = 0;
	while ((*cmd)[i] != '\0')
	{
		var = 0;
		if ((*cmd)[i] != '"' && (*cmd)[i] != ' ')
		{
			if ((*cmd)[i] == '$')
				var = 1;
			*cmd = add_char(*cmd, &i, '"', 0);
			printf("ici *cmd = %s\n", *cmd);
			--i;
			printf("*cmd[%d] = %c\n", i, (*cmd)[i]);
			while (((*cmd)[i] != ' ' && (*cmd)[i] != '"') &&
			is_escaped(*cmd, i - 1) == 1 && (*cmd)[i] != '\0')
			{
			//	i++;
				if (((*cmd)[i] == ' ' &&
				is_escaped(*cmd, i - 1) == 1) || ((*cmd)[i] == '"'
				&& is_escaped(*cmd, i - 1) == 1 && var == 1))
				{
					*cmd = add_char(*cmd, &i, '"',  0);
					printf("la *cmd = %s\n", *cmd);
					--i;
					break;
				}
				else if ((*cmd)[i] == '"' &&
				is_escaped(*cmd, i - 1) == 1)
				{
					*cmd = delete_char(*cmd, &i);
				//	while ((*cmd)[i] != '"' && is_escaped(*cmd, i - 1) == 1)
				//		i++;
					printf("i = %d\n", i);
				}
				i++;
			}
		}
		else if ((*cmd)[i] == '"')
		{
			i++;
			if ((*cmd)[i] == '$')
				var = 1;
			while ((*cmd)[i] != '"' && is_escaped(*cmd, i - 1) == 1)
				i++;
			if ((*cmd)[i + 1] == '"' && var == 0)
			{
				j = i;
				printf("1 -> i = %d\n", i);
				*cmd = delete_char(*cmd, &i);
				i = j;
				printf("2 -> i = %d et *cmd = %s\n", i, *cmd);
				*cmd = delete_char(*cmd, &i);
				printf("*cmd = %s\n", *cmd);
				if ((*cmd)[i] == '\0')
					break;
				while ((*cmd)[i] != '"' && is_escaped(*cmd, i - 1) == 1)
					i++;
			//	-> suprime les 2 " et on avance jusqu'au prochain "
			}
		}
		i++;
	}

	printf("cmd = %s\n", *cmd);
}*/

void	count_redir(int *nb_redir, char **arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i] != NULL)
	{
		if (ft_strncmp(">>", arg[i], ft_strlen(arg[i])) == 0)
			count++;
	/*	else if (ft_strncmp(">", arg[i], ft_strlen(arg[i])) == 0)
		{
			printf("2\n");
			count++;
		}*/
		else if (ft_strncmp("<", arg[i], ft_strlen(arg[i])) == 0)
			count++;
		i++;
	}
	*nb_redir = count;
}

void	complete_struct_cmd(char c, t_list_cmd *cmd)
{
	if (c == ';')
		(cmd)->semicolon = 1;
	else
		(cmd)->semicolon = 0;
	if (c == '|')
		(cmd)->pipe = 1;
	else
		(cmd)->pipe = 0;
	count_redir(&((cmd)->nb_redir), (cmd)->arg_cmd);
	cmd->next_cmd = NULL;	
	printf("nb_redir = %d et pipe = %d et semicolon = %d\n", (cmd)->nb_redir, (cmd)->pipe, (cmd)->semicolon);
}

int	save_cmd(int start_cmd, int end_cmd, char *line, t_list_cmd *cmd)
{
	int	ret;
	t_list_cmd	*tmp;
	t_list_cmd	*first;
//	t_list_cmd	*prev;

	ret = 0;
	tmp = malloc(sizeof(t_list_cmd));
	if (tmp == NULL)
		return (0);
	while (line[start_cmd] == ' ')
		start_cmd++;
	tmp->cmd = ft_substr(line, start_cmd, end_cmd - start_cmd + 1);
	if (tmp->cmd == NULL)
		return (0);
	ret = delete_space(&tmp->cmd, -1);
	if (ret == 0)
		return (0);
	tmp->arg_cmd = my_split(tmp->cmd, -1);
	if (tmp->arg_cmd == NULL)
		return (0);
	complete_struct_cmd(line[end_cmd - 1], tmp);
//	if (tmp.next_cmd == NULL)
//		printf("ICI NULLLL\n");
printf("33\n");
print_arg_cmd(tmp->arg_cmd);
printf("FIN\n");
	if (cmd == NULL)
	{
		(cmd) = tmp;
		cmd->next_cmd = NULL;
		printf("ICI cmd->cmd = %s et cmd->next_cmd = %d\n", cmd->cmd, cmd->next_cmd == NULL ? 1 : 0);
		printf("cmd == NULL? => %d\n", cmd == NULL ? 1 : 0);
	//	cmd->previous_cmd = NULL;
	}
	else
	{
		first = cmd;
		while (cmd->next_cmd != NULL)
			cmd = cmd->next_cmd;
	//	prev = cmd;
		cmd->next_cmd = tmp;
	//	cmd->next_cmd->next_cmd = NULL;
		printf("ICI 2 cmd->next_cmd->cmd = %s et cmd->next_cmd = %d\n", cmd->next_cmd->cmd, cmd->next_cmd->next_cmd == NULL ? 1 : 0);
	
	//	cmd->previous_cmd = prev;
		cmd = first;
	}
//	print_struct(cmd);
	return (1);
}

/*int	analysis_line(char **line, t_env *env, t_list_cmd *cmd)
{(void)env;
	int	i;
	int	start_cmd;

	i = -1;
	start_cmd = 0;
	if (empty_line(line, 0) == 0)
		return (0);
	while ((*line)[++i] != '\0')
	{
		if ((*line)[i] == '"' && is_escaped(*line, i - 1) == 0 &&
		(check_double_quotes(line, &i) == 0))
			return (0);
		else if ((*line)[i] == '\'' && is_escaped(*line, i - 1) == 0 &&
		(check_simple_quote(*line, &i) == 0))
			return (0);
		else if (((*line)[i] == ';' || (*line)[i] == '|')
		&& is_escaped(*line, i - 1) == 0)
		{
			if ((before_char(*line, i) == 0))
				return (error_msg(1, (*line)[i]));
			*line = add_char(*line, &i, (*line)[i], 1);
			if (save_cmd(start_cmd, i, *line, cmd) == 0)
				return (0);
			start_cmd = i + 1;
		}
		else if (((*line)[i] == '<' || (*line)[i] == '>')
		&& is_escaped(*line, i - 1) == 0)
		{
			if (empty_line(line, i + 1) == 0 || check_redir(*line, i) == 0)
				return (error_msg(1, (*line)[i]));
			else if ((*line)[i] == '>' && (*line)[i + 1] == '>')
				*line = add_char(*line, &i, (*line)[i], 2);
			else
				*line = add_char(*line, &i, (*line)[i], 1);
			if (*line == NULL)
				return (error_msg(2, ' '));
			printf("*line = %s\n", *line);	
		}
		else if ((*line)[i] == '#' && (*line)[i - 1] == ' ' &&
		is_escaped(*line, i - 2) == 0)
				*line = ft_substr(*line, 0, i);
		else if ((*line)[i] == '$' && is_escaped(*line, i - 1) == 0  &&
		(*line)[i + 1] != '\0' && (*line)[i + 1] != ' ')
		{
			//replace_variable(line, &i, env, 0);
			check_variable(*line, &i, 0);
		//	printf("line = %s\n", *line);
			--i;
		}
	}
//	save_cmd(start_cmd, i, *line, &cmd);
	print_struct(cmd);
printf("OK OK\n");
	return (1);
}*/

void	clear_cmd(t_list_cmd *cmd)
{
	t_list_cmd	*tmp;
	int	i;

	while (cmd->next_cmd != NULL)
	{
		tmp = cmd->next_cmd;
		i = 0;
		while (cmd->arg_cmd[i] != NULL)
		{
			free(cmd->arg_cmd[i]);
			i++;
		}
		free(cmd->arg_cmd);
		free(cmd->cmd);
		cmd = tmp;
	}
	i = 0;
	while (cmd->arg_cmd[i] != NULL)
	{
		free(cmd->arg_cmd[i]);
		i++;
	}
	free(cmd->arg_cmd);
	free(cmd->cmd);
}

int	main(int argc, char **argv, char **envp)
{
(void)argc;
(void)argv;
	char	*line;
	int	ret;
	int	exit;
	t_env	env;
	t_list_cmd	*cmd;

	env = copy_env(envp);
	if (env.var_env[0] == NULL)
		return (EXIT_FAILURE);
	exit = 1;
	ret = 0;
	line = NULL;
//	cmd.cmd = NULL;
	cmd = malloc(sizeof(t_list_cmd));
	cmd = NULL;
printf("RESULT cmd = %d\n", cmd == NULL ? 1: 0);
	while (exit == 1)
	{
		write(0, "$> ", 3);
		ret = get_next_line(0, &line, 0);
		if (ret == -1)
			printf("Error\n");
		if (analysis_line(&line, &env, cmd) < 0)
		{
			free(line);
			clear_env(&env);
			if (cmd != NULL)
				clear_cmd(cmd);
			get_next_line(0, &line, 1);
			return (EXIT_FAILURE);
		}
		free(line);
	//	process_shell(&env, &cmd);
		clear_cmd(cmd);
	//	cmd.cmd = NULL;
	//	printf("OK OK cmd.cmd = %s\n", cmd.cmd);
	}		
	return 0;
}
