/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:34:06 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/31 14:01:51 by adupuy           ###   ########.fr       */
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
					if (str[i] == '\\' && str[i + 1] == '\\')
					{
						if ((str = delete_char(str, &i)) == NULL)
							return (NULL);
						i++;
					}
					else
					{
						i--;
						str = delete_char(str, &i);
						i++;
					/*	if (str[i + 1] == '"')
						{
							i++;
							str = delete_char(str, &i);
							break;
						}*/
					}
				}
				else if (str[i] == '$' && is_escaped(str, i - 1) == 0 && str[i + 1] != '"')
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
				if (str[i] == '\\' && str[i + 1] == '\\')
				{
					if ((str = delete_char(str, &i)) == NULL)
						return (NULL);
					i++;
				//	printf("i1 => str = %s et str[%d] = %c\n", str, i, str[i]);
				}
				else if (str[i] == '\\' && str[i + 1] != '\\')
				{
					if ((str = delete_char(str, &i)) == NULL)
						return (NULL);
					i++;
				//	printf("2 => str = %s et str[%d] = %c\n", str, i, str[i]);
				}
				else if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '\\')
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
//printf("FIN => str = %s\n", str);
	return (str);
}

int	analysis_arg(t_env *env, t_list_cmd **cmd, int i)
{
	char	*tmp;

	tmp = (*cmd)->arg_cmd[i];
//	printf("tmp = %s\n", tmp);
	(*cmd)->arg_cmd[i] = edit_arg(tmp, env);
//	printf("arg[%d] = %s\n", i, (*cmd)->arg_cmd[0]);
	return (1);
}

void	free_tab_string(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

int	exec_other_cmd(char **arg, t_env **env)
{
	char	**path;
	char	*bin;
	struct stat	file_status;

	path = ft_split(get_value_var_env(get_var_env(env, "PATH")), ':');
	int i = 0;
/*	while (path[i] != NULL)
	{
		printf("path[%d] = %s\n", i, path[i]);
		i++;
	}*/
	if (path == NULL)
		return (0);
	i = 0;
	bin = NULL;
	if (arg[0][0] != '/' && ft_strncmp(arg[0], "./", 2) != 0 && ft_strncmp(arg[0], "../", 3) != 0)
	{
		arg[0] = ft_strjoin("/", arg[0]);
		while (path[i] != NULL)
		{
			bin = ft_strjoin(path[i], arg[0]);
			if (bin == NULL)
				return (0);
			if (stat(bin, &file_status) == 0)
				break;
			free(bin);
			bin = NULL;
			i++;
		}
		free_tab_string(path);
		free(arg[0]);
		arg[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
		return (0);
	}
	return (1);
}

void	exec_cmd(char **cmd, t_env **env)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
 		 if (WIFEXITED (status))
    			printf ("processus fils terminé normalement, le code de sortie %d\n", WEXITSTATUS (status));
 		 else
    			printf ("processus fils terminé anormalement\n");
		(*env)->return_value = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, (*env)->var_env) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

int	dvlpmt_arg(char **arg, t_env *env)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		arg[i] = edit_arg(arg[i], env);
		if (arg[i] == NULL)
			return (0);
		i++;
	}
	return (1);
}

int	process_simple_cmd(t_env *env, t_list_cmd **cmd)
{
	if (ft_strncmp((*cmd)->arg_cmd[0], "echo", 5) == 0)
	{
	//	printf("ECHO\n");
		ft_echo((*cmd)->arg_cmd, env);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[0], "pwd", 4) == 0)
	{
	//	printf("PWD\n");
		ft_pwd((*cmd)->arg_cmd, env);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[0], "env", 4) == 0)
	{
	//	printf("ENV\n");
		ft_env((*cmd)->arg_cmd, env);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[0], "unset", 6) == 0)
	{
	//	printf("UNSET\n");
		ft_unset((*cmd)->arg_cmd, &env);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[0], "export", 7) == 0)
	{
	//	printf("EXPORT\n");
		ft_export((*cmd)->arg_cmd, &env);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[0], "cd", 3) == 0)
	{
	//	printf("CD\n");
		ft_cd((*cmd)->arg_cmd, &env);
	}
	else if (ft_strncmp((*cmd)->arg_cmd[0], "exit", 5) == 0)
	{
	//	printf("EXIT\n");
		ft_exit((*cmd)->arg_cmd, &env);
	}
	else if ((*cmd)->arg_cmd[0] == NULL || (*cmd)->arg_cmd[0][0] == ' ' || (*cmd)->arg_cmd[0][0] == '\0')
		printf("%s: commande not found\n", (*cmd)->arg_cmd[0]);
	else
	{
		if (exec_other_cmd((*cmd)->arg_cmd, &env) == 0)
		{
			env->return_value = 127;
			printf("bash: %s: No such file or directory\n", (*cmd)->arg_cmd[0]);
			return (0);
		}
		if (dvlpmt_arg((*cmd)->arg_cmd, env) == 0)
			return (0);
		exec_cmd((*cmd)->arg_cmd, &env);
	}
	return (1);
}

int	size_tab(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count] != NULL)
		count++;
	return (count);
}

char	**delete_redir_and_file(char **cmd, int nb)
{
	char	**new;
	int	i;
	int	j;

	new = malloc(sizeof(char *) * (size_tab(cmd) - (2 * nb) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], ">", 2) == 0 ||
		ft_strncmp(cmd[i], "<", 2) == 0 ||
		ft_strncmp(cmd[i], ">>", 3) == 0)
			i = i + 2;
		else if (cmd[i] != NULL)
		{
			new[j] = ft_strdup(cmd[i]);
			if (new[j] == NULL)
			{
				new = ft_free(new, i);
				//free_tab_string(cmd);
				return (new);
			}
			j++;
			i++;
		}
	//	i++;
	//	j++;
	}
	new[j] = NULL;
//	free_tab_string(cmd);
//	cmd = new;
	return (new);
}

int	process_redir_cmd(t_list_cmd **cmd, int nb_redir, t_env *env)
{
	int	i;
	int	fd;
	int	nb;

	i = 0;
	nb = nb_redir;
	if (dvlpmt_arg((*cmd)->arg_cmd, env) == 0)
		return (0);
	while (nb_redir > 0)
	{
		fd = 0;
		while ((ft_strncmp((*cmd)->arg_cmd[i], ">", 2) != 0 &&
		ft_strncmp((*cmd)->arg_cmd[i], "<", 2) != 0 &&
		ft_strncmp((*cmd)->arg_cmd[i], ">>", 3) != 0) &&
		(*cmd)->arg_cmd[i] != NULL)
			i++;
		if (ft_strncmp((*cmd)->arg_cmd[i], "<", 2) == 0)
			fd = open((*cmd)->arg_cmd[i + 1], O_RDONLY);
		else if (ft_strncmp((*cmd)->arg_cmd[i], ">", 2) == 0)
			fd = open((*cmd)->arg_cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
		else if (ft_strncmp((*cmd)->arg_cmd[i], ">>", 3) == 0)
			fd = open((*cmd)->arg_cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
		if (fd == -1)
			return (0);
		if (ft_strncmp((*cmd)->arg_cmd[i], "<", 2) == 0)
			dup2(fd, 0);
		else
			dup2(fd, 1);
		close(fd);
		i++;
		nb_redir--;
	}
	if (((*cmd)->arg_cmd = delete_redir_and_file((*cmd)->arg_cmd, nb)) == NULL)
		return (0);
//print_arg_cmd((*cmd)->arg_cmd);
	return (1);
}

int	process_shell(t_env *env, t_list_cmd **cmd)
{
// ***** Processus pour lancer de simple commandes *****

/*	t_list_cmd	*tmp;

	tmp = *cmd;
	while ((*cmd)->next_cmd != NULL)
	{
		analysis_arg(env, cmd, 0);
		if ((*cmd)->pipe == 0 && (*cmd)->nb_redir == 0)
			process_simple_cmd(env, cmd);
		(*cmd) = (*cmd)->next_cmd;
	}
	analysis_arg(env, cmd, 0);
	if ((*cmd)->pipe == 0 && (*cmd)->nb_redir == 0)
		process_simple_cmd(env, cmd);
	*cmd = tmp;*/


// ***** Processus pour faire des redirections vers des fichiers *****

	analysis_arg(env, cmd, 0);
	if ((*cmd)->pipe == 0)
	{
		if ((*cmd)->nb_redir != 0)
		{
			process_redir_cmd(cmd, (*cmd)->nb_redir, env);
		//	print_arg_cmd((*cmd)->arg_cmd);
		}
		process_simple_cmd(env, cmd);
		close(1);
	}
	return (1);
}
