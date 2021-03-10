/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:57:55 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/19 11:30:02 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *list;

	list = NULL;
	while (lst && *lst)
	{
		list = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = list;
	}
}
