/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:40:32 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/24 11:37:16 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_cmd_tmp(t_list **cmd, char *line, int start_cmd, int end_cmd)
{
	char	*tmp;
	int		ret;
	t_list	*new;

	while (ft_isspace(line[start_cmd]) == 1)
		start_cmd++;
	tmp = ft_substr(line, start_cmd, end_cmd - start_cmd + 1);
	if (tmp == NULL)
		return (error_msg(2, ' '));
	ret = delete_space(&tmp, -1);
	if (ret == -1)
		return (ret);
	new = ft_lstnew(tmp);
	if (new == NULL)
		return (error_msg(2, ' '));
	ft_lstadd_back(cmd, new);
	return (1);
}

int	count_redir(char **arg)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (arg[++i] != NULL)
	{
		if (ft_strncmp(arg[i], ">>", ft_strlen(arg[i])) == 0)
			count++;
		else if (ft_strncmp(arg[i], "<", ft_strlen(arg[i])) == 0)
			count++;
	}
	return (count);
}

void	complete_struct(char *str, t_list_cmd **new)
{
	int	size;

	size = ft_strlen(str) - 1;
	while (ft_isspace(str[size]) == 1 && size > 0)
		size--;
	if (str[size] == ';')
		(*new)->semicolon = 1;
	else
		(*new)->semicolon = 0;
	if (str[size] == '|')
		(*new)->pipe = 1;
	else
		(*new)->pipe = 0;
	(*new)->nb_redir = count_redir((*new)->arg_cmd);
}

t_list_cmd	*ft_lstnew_cmd(char *content)
{
	t_list_cmd	*new;

	new = malloc(sizeof(t_list_cmd));
	if (new == NULL)
		return (NULL);
	new->cmd = content;
	new->arg_cmd = my_split(content, -1);
	if (new->arg_cmd == NULL)
	{
		free(new);
		return (NULL);
	}
	complete_struct(content, &new);
	new->next_cmd = NULL;
	return (new);
}

void	ft_lstadd_back_cmd(t_list_cmd **cmd, t_list_cmd *new)
{
	t_list_cmd	*tmp;

	tmp = *cmd;
	if (*cmd != NULL)
	{
		while ((*cmd)->next_cmd != NULL)
			(*cmd) = (*cmd)->next_cmd;
		(*cmd)->next_cmd = new;
		*cmd = tmp;
	}
	else
		*cmd = new;
}

int	save_cmd(t_list_cmd **cmd, t_list *cmd_tmp)
{
	t_list	*tmp;
	t_list_cmd	*new;

	tmp = cmd_tmp;
	while (cmd_tmp != NULL)
	{
		new = ft_lstnew_cmd(cmd_tmp->content);
		ft_lstadd_back_cmd(cmd, new);
		cmd_tmp = cmd_tmp->next;
	}
	cmd_tmp = tmp;
	print_struct_complete(cmd);
	return (1);
}
