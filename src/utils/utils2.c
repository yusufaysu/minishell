/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:00:49 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/04 13:43:06 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoinf(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

void	init_int_array(int *arr, int len, int val)
{
	int	i;

	i = 0;
	while (i < len)
	{
		arr[i] = val;
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s1[i] != s2[i])
		return (-1);
	return (0);
}

int	ft_strcont(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	sort_2d_str_array(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (++i < get_string_arr_len(arr))
	{
		if (i < 1)
			continue ;
		j = 0;
		while (arr[i][j] != '\0' && arr[i - 1][j] != '\0')
		{
			if (arr[i][j] < arr[i - 1][j])
			{
				tmp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = tmp;
				i -= 2;
				break ;
			}
			else if (arr[i][j] > arr[i - 1][j])
				break ;
			j++;
		}
	}
}
