/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:51:03 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/26 11:38:39 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	print_prompt(t_env *env)
{
	(void)env;
	char	*value;
	char	*prompt;

	value = getcwd(NULL, 0);
	write(0, "\033[32mminishell\033[37m:", 21);
	prompt = "\033[34m";
	prompt = ft_strjoin(prompt, value);
	prompt = ft_strjoin(prompt, "\033[37m");
	ft_putstr_fd(prompt, 0);
	write(0, "$> ", 3);
	return (1);
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
//	cmd_tmp = NULL;
//	cmd = NULL;
	while (1)
	{
	cmd_tmp = NULL;
	cmd = NULL;
	line = NULL;	
		//write(0, "$> ", 3);
		print_prompt(&env);
		ret = get_next_line(0, &line, 0);
		if (ret == -1)
			printf("Error lors de la lecture de l'input du user\n");
		ret = analysis_line(&line, -1, &cmd_tmp);
		if (ret < 0)
		{
			if (line != NULL)
				free(line);
			clear_env(&env);
			if (cmd_tmp != NULL)
				clear_cmd_tmp(cmd_tmp);
			get_next_line(0, &line, 1);
			printf("DEAD\n");
			return (EXIT_FAILURE);
		}
		if (ret > 0)
		{
	//	print_lst(cmd_tmp);
			save_cmd(&cmd, cmd_tmp);
			process_shell(&env, &cmd);
		}
		if (cmd_tmp != NULL)
			clear_cmd_tmp(cmd_tmp);
		if (cmd != NULL)
			clear_cmd(cmd);
	//	get_next_line(0, &line, 1);
		if (line != NULL)
			free(line);
	//	clear_env(&env);
		if (env.exit == 1)
			return (env.return_value);
	}
	return (0);
}

