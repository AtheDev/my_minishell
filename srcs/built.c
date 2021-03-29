/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:22:35 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/29 15:56:54 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_echo(char *str, int i)
{
	if (str[i] == '-')
	{
		i++;
		if (str[i] == 'n')
		{
			while (str[i] != '\0')
			{
				if (str[i] != 'n')
					return (0);
				i++;
			}
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char **arg, t_env *env)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (arg[i] != NULL)
	{
		arg[i] = edit_arg(arg[i], env);
		if (arg[i] == NULL)
			return (0);
		i++;
	}
	if (arg[1] != NULL)
	{
		if (check_option_echo(arg[1], 0) == 1)
			n = 1;
	}
	i = 1 + n;
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			write(1, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (1);
}

int	ft_pwd(char **arg, t_env *env)
{
	(void)	arg;
	(void)env;
	char	*pwd;
//	int	i;

/*	pwd = "$PWD";
	i = 0;
	if (replace_variable(&pwd, &i, env) != 1 )
		return (0);*/
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		printf("%s\n", pwd);
	else
		return (0);
	return (1);
}

int	ft_env(char **arg, t_env *env)
{
	int	i;

	i = 0;
	if (arg[1] != NULL)
		printf("Erreur pour ENV\n");
	else
	{
		while (env->var_env[i] != NULL)
		{
			printf("%s\n", env->var_env[i]);
			i++;
		}	
	}
	return (1);
}

void	free_tab(char **tmp)
{
	int	i;

	i = -1;
	while (tmp[++i] != NULL)
		free(tmp[i]);
	free(tmp);
}

char	**delete_var_env(char **var_env, int num, size_t size)
{
	char	**tmp;
	int	j;
	int	i;

	j = 0;
	i = 0;
	tmp = malloc(sizeof(char *) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	while (var_env[i] != NULL)
	{
		if (j == num)
			i++;
		if (var_env[i] == NULL)
			break;
		tmp[j] = ft_strdup(var_env[i]);
		if (tmp[j] == NULL)
		{
			free_tab(tmp);
			return (NULL);
		}
		j++;
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

int	process_delete_var_env(char *arg, t_env **env)
{
	int	i;

	i = 0;
	while ((*env)->var_env[i] != NULL)
	{
		if (ft_my_strncmp((*env)->var_env[i], arg, ft_strlen(arg)) == 0)
		{
			printf("var_env[%d] = %s\n", i, (*env)->var_env[i]);
			(*env)->size--;
			(*env)->var_env = delete_var_env((*env)->var_env, i, (*env)->size);
			if ((*env)->var_env == NULL)
				return (0);
			return (1);
		}
		i++;
	}
	return (1);
}

char	**add_var_env(char *arg, char **var_env, size_t size)
{
	char	**tmp;
	int	i;

	i = 0;
	tmp = malloc(sizeof(char *) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	while (i < ((int)size - 3))
	{
		tmp[i] = ft_strdup(var_env[i]);
		if (tmp[i] == NULL)
		{
			free_tab(tmp);
			return (NULL);
		}
		i++;
	}
	tmp[i] = ft_strdup(arg);
	if (tmp[i] == NULL)
	{
		free_tab(tmp);
		return (NULL);
	}
	tmp[i + 1] = ft_strdup(var_env[i]);
	if (tmp[i + 1] == NULL)
	{
		free_tab(tmp);
		return (NULL);
	}
	tmp[i + 2] = NULL;
	return (tmp);
}

int	process_add_var_env(char *arg, t_env **env)
{
	int	i;
	char	*key;

	i = 0;
	while (arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	if (key == NULL)
		return (0);
	while ((*env)->var_env[i] != NULL)
	{
		if (ft_my_strncmp((*env)->var_env[i], key, ft_strlen(key)) == 0)
		{
			(*env)->var_env[i] = ft_strdup(arg);
			if ((*env)->var_env[i] == NULL)
				return (0);
			return (1);
		}
		i++;
	}
	if ((*env)->var_env[i] == NULL)
	{
		(*env)->size++;
		(*env)->var_env = add_var_env(arg, (*env)->var_env, (*env)->size);
		if ((*env)->var_env == NULL)
			return (0);
	}
	return (1);
}

/*int	tilde_development(char **arg, char *tilde)
{
	int	i;

	i = 0;
	while ((*arg)[i] != '=')
		i++;
	i++;
	if ((*arg)[i] == '~')

	return (1);
}*/

int	check_arg_var(char **arg, int cmd/*, t_env **env*/)
{
	int	i;

	i = 0;
	if (ft_isdigit((*arg)[i]) == 1)
		return (0);
	while ((*arg)[i] != '\0')
	{
		if (ft_isalnum((*arg)[i]) == 0 && (*arg)[i] != '_')
		{
			if ((*arg)[i] == '=' && cmd == 1)
			{
			//	if ((*arg)[i + 1] == '~')
			//	tilde_development(arg, env);
				return (1);
			}
			return (0);
		}
		i++;
	}
	if (cmd == 1)
		return (-1);
	return (1);
}

int	ft_unset(char **arg, t_env **env)
{
	int	i;

	i = 1;
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			arg[i] = edit_arg(arg[i], *env);
			if (arg[i] == NULL)
				return (0);
			i++;
		}	
	}
	i = 1;
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			if (check_arg_var(&arg[i], 0/*, env*/) == 1)
			{
				printf("VAR OK\n");
				if (process_delete_var_env(arg[i], env) == 0)
					return (0);
			}
			else
				printf("bash: unset: « %s » : identifiant non valable\n", arg[i]);
			i++;
		}
	}
	return (1);	
}

int	sort_env(t_env **env)
{
	int	i;
	t_env	cp_env;
	char	*tmp;

	cp_env = copy_env((*env)->var_env, 0);
	if (cp_env.var_env == NULL)
		return (0);
	i = 0;
	while (cp_env.var_env[i + 1] != NULL)
	{
		if (ft_strncmp(cp_env.var_env[i + 1], cp_env.var_env[i], ft_strlen(cp_env.var_env[i])) < 0)
		{
			tmp = ft_strdup(cp_env.var_env[i]);
			free(cp_env.var_env[i]);
			cp_env.var_env[i] = ft_strdup(cp_env.var_env[i + 1]);
			free(cp_env.var_env[i + 1]);
			cp_env.var_env[i + 1] = ft_strdup(tmp);
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (cp_env.var_env[i] != NULL)
	{
		if (ft_strncmp(cp_env.var_env[i], "_=", 2) != 0)
			printf("declare -x %s=\"%s\"\n", get_key_var_env(cp_env.var_env[i]), get_value_var_env(get_var_env(env, cp_env.var_env[i])));
		i++;
	}
	return (1);
}

int	ft_export(char **arg, t_env **env)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (arg[i] == NULL)
	{
		if (sort_env(env) == 0)
			return (0);
		return (1);
	}
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			arg[i] = edit_arg(arg[i], *env);
			if (arg[i] == NULL)
				return (0);
			i++;
		}	
	}
	i = 1;
	if (arg[i] != NULL)
	{
		while (arg[i] != NULL)
		{
			ret = check_arg_var(&arg[i], 1/*, env*/);
		//	printf("AFTER TILDE_DELPT = %s\n", arg[i]);
			if (ret == 1)
			{
				printf("EXPORT VAR OK\n");
				if (process_add_var_env(arg[i], env) == 0)
					return (0);
			}
			else if (ret == 0)
				printf("bash: export: « %s » : identifiant non valable\n", arg[i]);
			i++;
		}
	}
	return (1);
}

char	*get_value_var_env(char *str)
{
	char	*value;
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '=')
		i++;
	value = ft_substr(str, i + 1, ft_strlen(str) - i);
//printf("value = %s\n", value);
	return (value);
}

char	*get_key_var_env(char *str)
{
	char	*key;
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (key == NULL)
		return (NULL);
	return (key);
}

char	*get_var_env(t_env **env, char *str)
{
	int	i;

	i = 0;
	while ((*env)->var_env[i] != NULL)
	{
		if (ft_strncmp((*env)->var_env[i], str, ft_strlen(str)) == 0)
			return ((*env)->var_env[i]);
		i++;
	}
	return (NULL);
}

int	check_nb_arg(char **arg, int count)
{
	while (arg[count] != NULL)
		count++;
	return (count);
}

int	process_cd(t_env **env, char *var_env, int num)
{
	char	*pwd;
	char	*oldpwd;
	char	*var;
	char	*path;

	if (num == 0)
	{
		var = get_var_env(env, var_env);
		pwd = get_var_env(env, "PWD");
		if (ft_strncmp(var_env, "OLDPWD", 6) == 0)
		{
			if (pwd == NULL && (var == NULL ||  var[ft_strlen(var_env) + 1] == '\0'))
			{
				printf("bash: cd: « %s » non défini\n", var_env);
				if (process_delete_var_env(var_env, env) == 0)
					return (0);
				return (1);
			}
			
		}
		if (var == NULL)
		{
			printf("bash: cd: « %s » non défini\n", var_env);
			return (0);
		}
		if (var[ft_strlen(var_env) + 1] == '\0')
		{
			printf("Pas d'erreur => change le prompt \'~\' en \'/home/user42\'\n");
			return (1);
		}
		path = get_value_var_env(var);
	}
	else
		path = var_env;
	if (chdir(path) == 0)
	{
		pwd = get_value_var_env(get_var_env(env, "PWD"));
		oldpwd = get_value_var_env(get_var_env(env, "OLDPWD"));
		if (pwd == NULL)
		{
			if (oldpwd != NULL)
			{
				if (process_add_var_env("OLDPWD=", env) == 0)
				{
					printf("1 => Erreur lors du changement de OLDPWD\n");
					return (0);
				}
			}
		}
		if (pwd != NULL && oldpwd != NULL)
		{
			oldpwd = ft_strdup(pwd);
			if (oldpwd == NULL)
			{
				printf("Erreur sur OLDPWD et la mémoire\n");
				return (0);
			}
			if (process_add_var_env(ft_strjoin("OLDPWD=", oldpwd), env) == 0)
			{
				printf("2 => Erreur lors du changement de OLDPWD\n");
				return (0);
			}
			
		}
		if (pwd != NULL)
		{
			pwd = getcwd(NULL, 0);
			if (pwd == NULL)
			{
				printf("Erreur lors de la récupération de PWD\n");
				return (0);
			}
			if (process_add_var_env(ft_strjoin("PWD=", pwd), env) == 0)
			{
				printf("Erreur lors du changement de PWD\n");
				return (0);
			}
		}
		if (ft_strncmp(var_env, "OLDPWD", 6) == 0)
			printf("%s\n", getcwd(NULL, 0));
	}
	else
	{
		printf("Erreur CHDIR\n");
		return (0);
	}
	return (1);	
}

int	ft_cd(char **arg, t_env **env)
{
	if (check_nb_arg(arg, 0) > 2)
	{
		printf("bash: cd: trop d'arguments\n");
		return (0);
	}
	if (arg[1] != NULL)
	{
		arg[1] = edit_arg(arg[1], *env);
		if (arg[1] == NULL)
			return (0);
		if (arg[1][0] == '\0')
			return (1);
		if (ft_strncmp(arg[1], "-", 2) == 0)	
		{
			if (process_cd(env, "OLDPWD", 0) == 0)
				return (0);
			return (1);
		}
		
	}
	if (arg[1] == NULL || (arg[1] != NULL && ft_strncmp(arg[1], "--", 3) == 0))
	{
		if (process_cd(env, "HOME", 0) == 0)
			return (0);
		return (1);
	}
	else
	{
		if (process_cd(env, arg[1], 1) == 0)
		{
			printf("bash: %s: %s: Aucun fichier ou dossier de ce type\n", arg[0], arg[1]);
			return (0);
		}
	}
	return (1);
}

int	check_value_arg(char *str)
{
	int	i;

	i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

unsigned long long	long_long_atoi(const char *str)
{
	int i;
	unsigned long long res;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res);
}
int	ft_exit(char **arg, t_env **env)
{
	unsigned long long	val;

	if (arg[1] == NULL)
	{
		printf("exit\n");
		(*env)->return_value = 0;
		(*env)->exit = 1;
		return (1);
	}
	if (arg[1] != NULL)
	{
		arg[1] = edit_arg(arg[1], *env);
		if (arg[1] == NULL)
			return (0);
		val = long_long_atoi(arg[1]);
		if (check_value_arg(arg[1]) == 0 || (val > 9223372036854775807
		&& ft_strncmp(arg[1], "-9223372036854775808", 21) != 0))
		{
			printf("exit\nbash: exit: %s : argument numérique nécessaire\n", arg[1]);
			(*env)->return_value = 2;
			(*env)->exit = 1;
			return (0);
		}
	}
	if (check_nb_arg(arg, 0) > 2)
	{
		printf("%s\nbash: exit: trop d'arguments\n", arg[0]);
		(*env)->return_value = 1;
		return (0);
	}
	val = ft_atoi(arg[1]) % 256;
	(*env)->return_value = val;
	printf("exit\n");
	(*env)->exit = 1;
	return (1);
}
