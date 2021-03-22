/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 11:02:53 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/12 11:30:07 by adupuy           ###   ########.fr       */
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
	size_t		i;
	t_env	env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env.size = ++i;
	env.var_env = malloc(sizeof(char *) * i);
	if (env.var_env == NULL)
		return (env);
	i = -1;
	while (++i < env.size - 1)
	{
		env.var_env[i] = ft_strdup(envp[i]);
		if (env.var_env[i] == NULL)
		{
			printf("Erreur lors de la copie de 'envp'\n");
			clear_env(&env);
			return (env);
		}
	}
	env.var_env[i] = NULL;
//	for(i = 0; i < env.size; i++)
//		printf("env.var_env[%zu] = %s\n       envp[%zu] = %s\n\n", i, env.var_env[i], i, envp[i]);
	return (env);
}