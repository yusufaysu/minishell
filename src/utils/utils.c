/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:43:15 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/22 12:22:38 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_string_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**copy_str_array(char **arr)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (get_string_arr_len(arr) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < get_string_arr_len(arr))
		new[i] = ft_strdup(arr[i]);
	new[i] = 0;
	return (new);
}

int	print_error(char *str, t_data *data, int exit_status, int free_level)
{
	write(STDERR_FILENO, "Error: ", 8);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	g_exit_status = exit_status;
	free_on_error(data, free_level);
	return (0);
}

int	ft_strncmpf(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (i < (int)n)
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*get_env(char *env, t_data *data)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < get_string_arr_len(data->envp))
	{
		if (ft_strncmpf(data->envp[i], env, ft_strlen(env)) == 0
			&& data->envp[i][ft_strlen(env)] == '=')
		{
			str = malloc(sizeof(char)
					* (ft_strlen(data->envp[i]) - ft_strlen(env)));
			j = ft_strlen(env) + 1;
			k = 0;
			while (data->envp[i][j] != '\0')
				str[k++] = data->envp[i][j++];
			str[k] = '\0';
			return (str);
		}
	}
	return (NULL);
}
