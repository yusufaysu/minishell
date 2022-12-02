/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:32:10 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/11 14:50:32 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*fill_path_helper(char *path_line, int rot, int path_len)
{
	char	*path;
	int		i;
	int		j;
	int		path_num;

	path = malloc(sizeof(char) * (path_len + 1));
	i = 4;
	j = 0;
	path_num = 0;
	while (++i < (int)ft_strlen(path_line))
	{
		if (rot == path_num && path_line[i] != ':')
			path[j++] = path_line[i];
		else if (path_line[i] == ':')
			path_num++;
		if (path_num > rot)
			break ;
	}
	path[j] = '\0';
	return (path);
}

char	*fill_path(char	*path_line, int rot)
{
	int	i;
	int	path_num;
	int	path_len;

	path_num = 0;
	path_len = 0;
	i = 4;
	while (++i < (int)ft_strlen(path_line))
	{
		if (rot == path_num && path_line[i] != ':')
			path_len++;
		else if (path_line[i] == ':')
			path_num++;
		if (path_num > rot)
			break ;
	}
	return (fill_path_helper(path_line, rot, path_len));
}
