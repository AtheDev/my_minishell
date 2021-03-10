/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:12:39 by adupuy            #+#    #+#             */
/*   Updated: 2021/03/07 18:12:35 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_line(int fd, char **line, int close)
{
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	static char	*str;
	int			count;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (-1);
	if (close == 1)
	{
		free(str);
		return (1);
	}
	ret = 1;
	while ((ret > 0) && ((count = ft_is_end_line(str)) == 0))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (!(str = ft_my_strjoin(str, buf)))
			return (-1);
	}
	ret = ft_new_line(&str, line, ret, count);
	return (ret);
}
