/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:15:48 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/19 11:00:00 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(t_list *lst, t_list *new_list, t_list *tmp,
		void (*del)(void *))
{
	while (new_list != NULL)
	{
		tmp = new_list->next;
		(*del)(new_list->content);
		free(new_list);
		new_list = tmp;
	}
	lst = NULL;
	return (NULL);
}

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;
	t_list	*res;

	new_list = NULL;
	while (lst != NULL)
	{
		if (!(tmp = ft_lstnew((*f)(lst->content))))
			return (ft_free(lst, new_list, tmp, del));
		if (new_list == NULL)
		{
			new_list = tmp;
			res = new_list;
			new_list->next = NULL;
		}
		else
		{
			new_list->next = tmp;
			tmp->next = NULL;
			new_list = new_list->next;
		}
		lst = lst->next;
	}
	return (res);
}
