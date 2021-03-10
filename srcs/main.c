/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:21:52 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/10 18:50:44 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env)
{
	int	i;

	i = -1;
	while (env->var_env[++i])
		free(env->var_env[i]);
	free(env->var_env);
}

t_env	copy_env(char **envp)
{
	size_t	i;
	t_env	env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env.size = ++i;
	env.var_env = malloc(sizeof(char*) * i);
	if (env.var_env == NULL)
		return (env);
	i = 0;
	while (i < env.size - 1)
	{
		env.var_env[i] = ft_strdup(envp[i]);
		if (env.var_env[i] == NULL)
		{
			printf("Erreur lors de la copie\n");
			clear_env(&env);
			return (env);
		}
		i++;
	}
	env.var_env[i] = NULL;
//	for (i = 0; i < env.size; i++)
//		printf("env.var_env[%zu] = %s\n envp[%zu] = %s\n", i, env.var_env[i], i, envp[i]);
	return (env);
}

int	is_escaped(char *line, int i)
{
	int	nb_backslash;

	nb_backslash = 0;
	if (line[i] != '\\')
		return (1);
	else
	{
		while (line[i] == '\\' && i-- >= 0)
			nb_backslash++;
	}
	if (nb_backslash % 2 == 0)
		return (1);
	return (0);
}

/* vérifie qu'il y a bien des caractères avant le ';' ou le '|' */
int	before_char(char *line, int i)
{
	while (--i >= 0)
	{
		if (line[i] != ' ')
			return (1);
	}
	return (0);
}

/* vérifie qu'un ';' n'est pas suivis pas un ';' */
int	after_semicolon(char *line, int i)
{
	if (line[++i] == '\0')
		return (1);
	if (line[i] == ';')
		return (0);
	if (line[i] == ' ')
	{
		while (line[i] == ' ' && line[i] != '\0')
			i++;
		if (line[i] == ';')
			return (0);
	}
	return (1);
}

/* compare s1 et s2 et vérifie que s1 est bien suivie du signe '=' car
 les variables d'env sont ainsi prototypées */
int	ft_my_strncmp(char *s1, char *s2, size_t n)
{
	while (*s1 == *s2 && *s1 && n)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return (((unsigned char)*s1) - ((unsigned char)*s2));
	if ((*s1) != '=')
		return (1);
	return (0);
}

/* permet de récupérer la valeur de la var et de l'enregistrer dans tmp */
int	save_value(char **tmp, char *env)
{
	int	count;
	int	i;
	int	index;

	i = 0;
	while (env[i] != '=')
		i++;
	index = i + 1;
	count = 0;
	while (env[++i] != '\0')
		count++;
	*tmp = ft_substr(env, index, count);
	*tmp = ft_strjoin("\"", *tmp);
	*tmp = ft_strjoin(*tmp, "\"");
	if (*tmp == NULL)
		return (0);
	return (1);
}

/* ajoute la fin de la line à la nouvelle line */
char	*add_str(char *str, char *line, int pos)
{
	char	*tmp;
	int	size_line;
	int	size_str;
	int	i;

	size_line = ft_strlen(line) - pos;
	size_str = ft_strlen(str);
	tmp = malloc(sizeof(char) * (size_str + size_line + 1));
	if (tmp == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != '\0')
		tmp[i] = str[i];
	while (i < (size_str + size_line))
		tmp[i++] = line[pos++];
	tmp[i] = '\0';
	return (tmp);
}

/* permet de ré-écrire line avec l'échange de la valeur de $var par sa value */
int	swap_var_env(char **tmp, char **line, int pos, int size_var)
{
	int	size_tmp;
	char	*str;

	size_tmp = ft_strlen(*tmp);
	str = ft_substr(*line, 0, pos);
	str = ft_strjoin(str, *tmp);
	str = add_str(str, *line, size_var + pos + 1);
	free(*line);
	*line = str;
	return (1);
}

/* recherche si la var d'env contenue dans tmp existe si oui on récupère la valeur*/
int	search_var_env(char **tmp, t_env *env, int size_tmp)
{
	int	i;

	i = 0;
	while (env->var_env[i] != NULL)
	{
		if (ft_my_strncmp(env->var_env[i], *tmp, size_tmp) == 0)
		{
			printf("env->var_env[%d] = %s\n", i, env->var_env[i]);
			free(*tmp);
			*tmp = NULL;
			if (save_value(tmp, env->var_env[i]) == 0)
				return (-1);
			printf("after save_value tmp = %s\n", *tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

/* processus qui permet de compter, d'enregistrer et de remplacer les $var par leur valeur si existe */
int	replace_variable(char **line, int *i, t_env *env, int quote)
{
	char	*tmp;
	int	index;
	int	pos_dollar;
	int	size_var;
	int	j;
	int	ret;
	int	size_tmp;

	index = *i;
	pos_dollar = index;
	tmp = NULL;
	size_var = 0;
	while ((*line)[++*i] != '\0' && (ft_isalnum((*line)[*i]) == 1
	|| (*line)[*i] == '_'))
		size_var++;
	if (((*line)[*i] == '"' && quote == 0) || (*line)[*i] == '\'' || (*line)[*i] == '`' ||
	(*line)[*i] == '|' || ((*line)[*i] == '\\' && (*line)[*i + 1] == '\0'))
	{
		printf("Erreur n°1\n");
		return (0);
	}
	if ((*line)[*i] == '(' || (*line)[*i] == ')' || (*line)[*i] == '<'
	|| (*line)[*i] == '>')
	{
		printf("bash: erreur de syntaxe près du symbole inattendu « %c »\n", (*line)[*i]);
		return (0);
	}
	tmp = malloc(sizeof(char) * (size_var + 1));
	if (tmp == NULL)
		return (-1);
	j = 0;
	while (++index < *i)
		tmp[j++] = (*line)[index];
	tmp[j] = '\0';
	ret = search_var_env(&tmp, env, size_var);
	size_tmp = ft_strlen(tmp);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		printf("Pas de variable existante\n");
		printf("line = %s\n", *line);
		return (0);
	}
	if (ret == 1)
	{
		printf("Variable trouvée et échangée\n");
		swap_var_env(&tmp, line, pos_dollar, size_var);
		printf("after swap_var_env line = %s\n", *line);
		
	}
printf("tmp = %s et line = %s\n", tmp, *line);
	if (tmp != NULL)
		free(tmp);
	*i = *i + size_tmp - size_var - 1;
	return (1);
}

int	check_dollar(char **line, int index, int *i, t_env *env)
{
	int	size_tot;

	size_tot = 0;
	while ((*line)[index] != '"' && is_escaped(*line, index - 1) == 1)
	{
		if ((*line)[index] == '$')
		{
			*i = index;
			if (replace_variable(line, i, env, 1) < 0)
				return (0);
			index = *i;
			index--;
		}
		index++;
	}
	return (1);
}

/* permet ve vérifier que l'on retrouve bien une " fermante */
int	check_double_quotes(char **line, int *i, t_env *env)
{
	int	index;

	++*i;
	index = *i;
	while (((*line)[*i] != '"' || ((*line)[*i] == '"' &&
		is_escaped(*line, *i - 1) == 0)) && (*line)[*i] != '\0')
		(*i)++;
	if ((*line)[*i] == '\0')
	{
		printf("> ERROR\n");
		return (0);
	}
	if ((*line)[*i] == '"' && is_escaped(*line, *i - 1) == 1)
		printf("OK pour \"\n\n");
	if (check_dollar(line, index, i, env) == 0)
		return (0);
	return (1);
}

/* permet de vérifier que l'on retrouve bien le ' fermante */
int	check_simple_quote(char *line, int *i)
{
	++*i;
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '\0' || (line[*i] == '\'' && is_escaped(line, *i - 1) == 0))
	{
		printf("> ERROR\n");
		return (0);
	}
	if (line[*i] == '\'' && is_escaped(line, *i - 1) == 1)
		printf("OK pour \'\n\n");
	return (1);
}

int	analysis_line(char **line, t_env *env)
{
	int	i;
	int	nb_cmd;

	i = 0;
	nb_cmd = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '"' && is_escaped(*line, i - 1) == 1 &&
		(check_double_quotes(line, &i, env) == 0))
			return (0);
		else if ((*line)[i] == '\'' && is_escaped(*line, i - 1) == 1 &&
		(check_simple_quote(*line, &i) == 0))
			return (0);
		else if ((*line)[i] == ';' && is_escaped(*line, i - 1) == 1)
		{
			if ((before_char(*line, i) == 0) || (after_semicolon(*line, i) == 0))
			{
				printf("Erreur de syntaxe près du symbole inattendu « ; »\n");
				return (0);
			}
			nb_cmd++;
		}
		else if ((*line)[i] == '|' && before_char(*line, i) == 0)
		{
			printf("Erreur de syntaxe près du symbole inattendu « | »\n");
			return (0);	
		}
		else if ((*line)[i] == '#' && (*line)[i - 1] == ' ' &&
		is_escaped(*line, i - 2) == 1)
				*line = ft_substr(*line, 0, i);
		else if ((*line)[i] == '$' && is_escaped(*line, i - 1) == 1 &&
		(*line)[i + 1] != '\0' && (*line)[i + 1] != ' ')
		{
			replace_variable(line, &i, env, 0);
			--i;
		}
		i++;
	}
	if (ft_strlen(*line) != 0)
		nb_cmd++;
	printf("nb_cmd = %d\n", nb_cmd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
(void)argc;
(void)argv;
	char	*line;
	int	ret;
	int	exit;
	t_env	env;

	env = copy_env(envp);				/* on copie las variables d'environnement dans env */
	if (env.var_env[0] == NULL)			/* si la copie échoue on arrête */
		return (EXIT_FAILURE);
	exit = 1;
	ret = 0;
	line = NULL;
	while (exit == 1)
	{
		write(0, "$> ", 3);			/* affichage du prompt */
		ret = get_next_line(0, &line, 0);	/* lecture de l'entrée du user */
		if (ret == -1)
			printf("Error\n");
		if (analysis_line(&line, &env) == 0)	/* analyse de l'entrée */
		{
			free(line);			/* si erreur on nettoie tous les malloc */
			clear_env(&env);
			get_next_line(0, &line, 1);
			return (EXIT_FAILURE);
		}
		free(line);
	}		
	return 0;
}
