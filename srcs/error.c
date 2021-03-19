/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:54:18 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/12 13:55:20 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(int num, char c)
{
	if (num == 1)
		printf("Erreur de syntaxe près du symbole inattendu « %c »\n", c);
	if (num == 2)
	{
		printf("Erreur lors d'une allocation de mémoire\n");
		return (-1);
	}
	if (num == 3)
		printf("Erreur: manque un %c fermant\n", c);
	return (0);	
}

