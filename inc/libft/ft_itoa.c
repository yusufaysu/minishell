/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:44:48 by yaysu             #+#    #+#             */
/*   Updated: 2022/01/12 14:44:52 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intnumlen(int num)
{
	int	numlen;

	numlen = 0;
	if (num == 0)
		numlen = 1;
	if (num < 0)
	{
		numlen++;
		num = -1 * num;
	}
	while (num != 0)
	{
		num = num / 10;
		numlen++;
	}
	return (numlen);
}

char	*ft_itoa(int n)
{
	char	*s;
	long	num;
	int		nlen;

	num = (long)n;
	nlen = ft_intnumlen(n);
	s = malloc(nlen + 1);
	if (!s)
		return (NULL);
	s[nlen] = '\0';
	if (num == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num = -num;
	}
	nlen--;
	while (nlen >= 0 && num != 0)
	{
		s[nlen] = num % 10 + '0';
		num = num / 10;
		nlen--;
	}
	return (s);
}
