/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:01:59 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/26 11:46:11 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BUFFER_SIZE 1024

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>

# define CHAR_PROTEC "\"\'\\`$"
# define META_CHAR "|&;()<> "

typedef struct	s_list_cmd
{
	char	*cmd;
	char	**arg_cmd;
	int	semicolon;
	int	pipe;
	int	nb_redir;
	struct	s_list_cmd	*next_cmd;
	
}			t_list_cmd;

typedef struct	s_env
{
	char	**var_env;
	char	*tilde;
	int	return_value;
	int	exit;
	size_t	size;
}			t_env;

/*typedef struct s_cmd
{
	char	**cmd;
	int	nb_cmd;
}*/


/*
	***** GNL *****
*/
int		get_next_line(int fd, char **line, int close);
char	*ft_my_substr(char *s, int start, int len);
int		ft_is_end_line(char *str);
int		ft_new_line(char **str, char **line, int ret, int count);
char	*ft_my_strjoin(char *s1, char *s2);

/*
	***** ENV *****
*/
void	clear_env(t_env *env);
t_env	copy_env(char **env);

/*
	***** ANALYSIS LINE *****
*/
int	analysis_line(char **line, int i, t_list **cmd);

/*
	***** CMD *****
*/
int	save_cmd_tmp(t_list **cmd, char *line, int start_cmd, int end_cmd);
int	save_cmd(t_list_cmd **cmd, t_list *cmd_tmp);

/*
	***** CHAR *****
*/

int	is_escaped(char *line, int i);
int	before_char(char *line, int i);
char	*add_char(char *line, int *pos, char c, int space);
char	*strjoin_char(char *s1, char c, int space);
char	*delete_char(char *line, int *pos);
char	*process_free(char *tmp, char *tmp2);

/*
	***** CHAR ESCAPED *****
*/
int	db_quotes(char *str, int i);
int	sp_quote(char *str, int i);
int	dollar(char *str, int i);
int	sep_cmd(char *str, int i);
int	redir(char *str, int i);

/*
	***** QUOTE *****
*/
int	check_double_quotes(char *line, int *i);
int	check_simple_quote(char *line, int *i);

/*
	***** DOLLAR *****
*/
int	check_variable(char *line, int *i, int quote);
int	check_dollar(char **line, int index, int *i, t_env *env);
int	replace_variable(char **line, int *i, t_env *env);

/*
	***** DOLLAR_UTILS *****
*/
int	save_value(char **tmp, char *env);
char	*add_str(char *str, char *line, int pos);
int	swap_var_env(char **tmp, char **line, int pos, int size_var);
int	search_var_env(char **tmp, t_env *env, int size_tmp);

/*
	***** WORD *****
*/
int	delete_space(char **cmd, int i);
int	join_word(char **cmd);

/*
	***** MY SPLIT *****
*/
char	**my_split(char *str, int j);

/*
	***** PROCESS SHELL *****
*/
int	process_shell(t_env *env, t_list_cmd **cmd);
char	*edit_arg(char *str, t_env *env);

/*
	***** UTILS *****
*/
int	empty_line(char  **line, int i);
int	check_redir(char *line, int i);
int	ft_my_strncmp(char *s1, char *s2, size_t n);
char	*clean_line(char *line);


/*
	***** ERROR *****
*/
int	error_msg(int num, char c);

/*
	***** PRINT *****
*/
void	print_struct_complete(t_list_cmd **cmd);
void	print_struct(t_list_cmd *lst);
void	print_arg_cmd(char **arg_cmd);
void	print_lst(t_list *lst);

/*
	***** BUILT *****
*/
int	ft_echo(char **arg, t_env *env);
int	ft_pwd(char **arg, t_env *env);
int	ft_env(char **arg, t_env *env);
int	ft_unset(char **arg, t_env **env);
int	ft_export(char **arg, t_env **env);
int	ft_cd(char **arg, t_env **env);
int	ft_exit(char **arg, t_env **env);
char	*get_var_env(t_env **env, char *str);
char	*get_value_var_env(char *str);

#endif
