/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyasar <alyasar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:43:04 by yaysu             #+#    #+#             */
/*   Updated: 2022/10/12 16:20:55 by alyasar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	mark_redir(t_data *data, t_bool tf)
{
	t_bool	*new_redir_mark;
	int		i;

	data->redir_len++;
	new_redir_mark = malloc(sizeof(t_bool) * data->redir_len);
	i = -1;
	while (++i < data->redir_len - 1)
		new_redir_mark[i] = data->redir_mark[i];
	new_redir_mark[i] = tf;
	if (data->redir_len > 1)
		free(data->redir_mark);
	data->redir_mark = new_redir_mark;
}

char	*set_redir_pipe(char *str, int *ind, int token_space, t_data *data)
{
	int		i;
	int		j;
	char	*new_str;
	int		t_space;

	mark_redir(data, FALSE);
	t_space = token_space;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 3));
	i = -1;
	j = 0;
	while (++i < *ind)
		new_str[i] = str[j++];
	new_str[i++] = ' ';
	while (token_space-- > 0)
		new_str[i++] = str[j++];
	new_str[i++] = ' ';
	while (str[j] != '\0')
		new_str[i++] = str[j++];
	new_str[i] = '\0';
	free(str);
	(*ind) += t_space;
	return (new_str);
}

char	*set_metacharacters(char *str, int *ind, t_bool quote[2], t_data *data)
{
	int	token_space;

	token_space = 0;
	if ((str[*ind] == '>' && str[*ind + 1] == '>') || \
			(str[*ind] == '<' && str[*ind + 1] == '<'))
		token_space = 2;
	else if (str[*ind] == '>' || str[*ind] == '<' || str[*ind] == '|')
		token_space = 1;
	if (token_space && !quote[0] && !quote[1])
		return (set_redir_pipe(str, ind, token_space, data));
	else if (token_space)
		mark_redir(data, TRUE);
	else if (str[*ind] == '$' && (ft_isalnum(str[*ind + 1]) || \
			str[*ind + 1] == '_' || str[*ind + 1] == '?') && !quote[0])
	{
		if (str[*ind + 1] == '?')
			return (set_exit_status(str, ind));
		else if (ft_isdigit(str[*ind + 1]))
			return (set_env_var_digit(str, ind));
		else
			return (set_env_var(str, ind, data));
	}
	return (str);
}

char	*restr(char *str, t_data *data)
{
	int		i;
	t_bool	quote[2];

	data->redir_len = 0;
	quote[0] = FALSE;
	quote[1] = FALSE;
	i = 0;
	while (i < (int)ft_strlen(str) && str[0] != '\0')
	{
		if (str[i] == '\'' && !quote[1])
			quote[0] = !quote[0];
		else if (str[i] == '"' && !quote[0])
			quote[1] = !quote[1];
		str = set_metacharacters(str, &i, quote, data);
		i++;
	}
	return (str);
}

char	**split_line(char *str, t_data *data)
{
	char	**array;
	t_bool	quote[2];

	str = restr(str, data);
	quote[0] = FALSE;
	quote[1] = FALSE;
	array = malloc(1 * sizeof(char *));
	array[0] = 0;
	create_the_array(str, quote, &array);
	free(str);
	if (quote[0] || quote[1])
	{
		free_str_array(array);
		return (NULL);
	}
	return (array);
}
