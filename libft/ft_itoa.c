/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:48:36 by adupuy            #+#    #+#             */
/*   Updated: 2020/11/18 19:30:05 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap(char *s1, char *s2)
{
	char swp;

	swp = *s1;
	*s1 = *s2;
	*s2 = swp;
}

static char	*ft_strrev(char *str)
{
	int len;
	int i;
	int div;

	len = ft_strlen(str);
	i = 0;
	div = len / 2;
	while (i < div)
	{
		ft_swap(&str[i], &str[len - i - 1]);
		i++;
	}
	return (str);
}

static int	ft_size_nb(long long int n)
{
	int	count;

	count = 1;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	if (n < 0)
		count += 1;
	return (count);
}

char		*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				size;
	long long int	nb;

	nb = n;
	size = ft_size_nb(nb);
	if (!(str = ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		nb *= -1;
	i = 0;
	while (nb > 0)
	{
		str[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		str[i] = '-';
	return (ft_strrev(str));
}
