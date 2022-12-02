/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:24:04 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/20 14:38:33 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**set_new_arr(char **arr, char *s)
{
	int		i;
	char	**new_arr;

	new_arr = malloc(sizeof(char *) * (get_string_arr_len(arr) + 2));
	i = -1;
	while (++i < get_string_arr_len(arr))
		new_arr[i] = arr[i];
	new_arr[i++] = s;
	new_arr[i] = 0;
	free(arr);
	return (new_arr);
}

int	count_quotes(const char *str, int st, int fn)
{
	int		i;
	t_bool	quote[2];

	quote[0] = FALSE;
	quote[1] = FALSE;
	i = 0;
	while (st < fn)
	{
		if (str[st] == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (str[st] == '"' && !quote[0])
			quote[1] = !quote[1];
		if ((str[st] == '"' && !quote[0]) || (str[st] == '\'' && !quote[1]))
			i++;
		st++;
	}
	return (i);
}

char	**add_to_array(char **arr, const char *str, int st, int fn)
{
	char	*s;
	int		i;
	t_bool	quote[2];

	quote[0] = FALSE;
	quote[1] = FALSE;
	i = 0;
	s = malloc((fn - st + 1 - count_quotes(str, st, fn)) * sizeof(char));
	while (st < fn)
	{
		if (str[st] == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (str[st] == '"' && !quote[0])
			quote[1] = !quote[1];
		if (!(str[st] == '"' && !quote[0]) && !(str[st] == '\'' && !quote[1]))
			s[i++] = str[st];
		st++;
	}
	s[i] = '\0';
	return (set_new_arr(arr, s));
}
