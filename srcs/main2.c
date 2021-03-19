/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:51:03 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/19 10:28:35 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		printf("1 => lst = %s\n", lst->content);
		lst = lst->next;
	}
	printf("2 => lst = %s\n", lst->content);
	lst = tmp;
}

void	clear_cmd_tmp(t_list *cmd)
{
	t_list	*lst;

	lst = NULL;
	while (cmd != NULL)
	{
		lst = cmd->next;
		free(cmd->content);
		free(cmd);
		cmd = lst;
	}
}

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
		free(cmd);
		cmd = tmp;
	}
	i = 0;
	while (cmd->arg_cmd[i] != NULL)
	{
		free(cmd->arg_cmd[i]);
		i++;
	}
	free(cmd->arg_cmd);
	free(cmd);
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	int	ret;
	t_env	env;
	t_list	*cmd_tmp;
	t_list_cmd	*cmd;	

	env = copy_env(envp);
	if (env.var_env == NULL)
		return (EXIT_FAILURE);
	ret = 0;
	line = NULL;
	cmd_tmp = NULL;
	cmd = NULL;
	while (1)
	{
		write(0, "$> ", 3);
		ret = get_next_line(0, &line, 0);
		if (ret == -1)
			printf("Error lors de la lecture de l'input du user\n");
		if (analysis_line(&line, -1, &cmd_tmp) < 1)
		{
			if (line != NULL)
				free(line);
			clear_env(&env);
			if (cmd_tmp != NULL)
				clear_cmd_tmp(cmd_tmp);
			get_next_line(0, &line, 1);
			return (EXIT_FAILURE);
		}
		print_lst(cmd_tmp);
		save_cmd(&cmd, cmd_tmp);
		if (cmd_tmp != NULL)
			clear_cmd_tmp(cmd_tmp);
		if (cmd != NULL)
			clear_cmd(cmd);
		get_next_line(0, &line, 1);
		if (line != NULL)
			free(line);
		clear_env(&env);
	}
	return (0);
}

