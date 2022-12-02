/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:48:19 by yaysu             #+#    #+#             */
/*   Updated: 2022/01/12 14:48:21 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*i;
	unsigned char	*j;

	i = (unsigned char *)dst;
	j = (unsigned char *)src;
	if (i < j)
	{
		while (len--)
			*i++ = *j++;
	}
	else
	{
		i += len;
		j += len;
		while (len--)
			*--i = *--j;
	}
	return (dst);
}
