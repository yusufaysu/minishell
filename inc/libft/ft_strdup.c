/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:50:34 by yaysu             #+#    #+#             */
/*   Updated: 2022/01/12 14:55:34 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	void	*new;

	len = ft_strlen(s) + 1;
	new = malloc (len);
	if (new == NULL)
		return (NULL);
	return ((char *) ft_memcpy (new, s, len));
}
