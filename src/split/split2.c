/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:42:06 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/20 14:38:33 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_the_array(char *str, t_bool quote[2], char ***array)
{
	int		i;
	int		index;

	i = 0;
	index = -1;
	while (i <= (int)ft_strlen(str) && str[0] != '\0')
	{
		if (str[i] == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (str[i] == '"' && !quote[0])
			quote[1] = !quote[1];
		if (str[i] != ' ' && index < 0)
			index = i;
		else if ((str[i] == ' ' || i == (int)ft_strlen(str))
			&& index >= 0 && !quote[0] && !quote[1])
		{
			*array = add_to_array(*array, str, index, i);
			index = -1;
		}
		i++;
	}
}

char	*set_exit_status(char *str, int *ind)
{
	char	*new_str;
	char	*exit_stat;
	int		i;
	int		j;
	int		k;

	exit_stat = ft_itoa(g_exit_status);
	new_str = malloc(sizeof(char)
			* (ft_strlen(str) - 1 + ft_strlen(exit_stat)));
	i = -1;
	k = 0;
	while (++i < *ind)
		new_str[i] = str[k++];
	j = -1;
	while (++j < (int)ft_strlen(exit_stat))
		new_str[i++] = exit_stat[j];
	while (str[k + 2] != '\0')
	{
		new_str[i++] = str[k + 2];
		k++;
	}
	new_str[i] = '\0';
	free(str);
	free(exit_stat);
	return (new_str);
}

char	*set_env_var_digit(char *str, int *ind)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	i = -1;
	while (++i < *ind)
		new_str[i] = str[i];
	while (str[i + 2] != '\0')
	{
		new_str[i] = str[i + 2];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*set_env_var(char *str, int *ind, t_data *data)
{
	char	*env_value;
	int		key_len;
	char	*key;

	key_len = 0;
	while (str[*ind + 1 + key_len] == '_'
		|| ft_isalnum(str[*ind + 1 + key_len]))
		key_len++;
	key = ft_substr(str, *ind + 1, key_len);
	env_value = get_env(key, data);
	free(key);
	if (!env_value)
		env_value = ft_strdup("");
	return (set_env_var2(str, ind, env_value, key_len));
}

char	*set_env_var2(char *str, int *ind, char *env_value, int key_len)
{
	char	*new_str;
	int		i;
	int		j;
	int		k;

	new_str = malloc(sizeof(char) * (ft_strlen(str)
				- key_len + ft_strlen(env_value)));
	i = -1;
	j = 0;
	while (++i < *ind)
		new_str[i] = str[j++];
	k = 0;
	while (k < (int)ft_strlen(env_value))
		new_str[i++] = env_value[k++];
	j += key_len + 1;
	while (str[j] != '\0')
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	free(str);
	(*ind) += ft_strlen(env_value) - 1;
	free(env_value);
	return (new_str);
}
