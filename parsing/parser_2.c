/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:16:32 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/04 18:17:24 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

size_t	max_len(char **lines)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (lines[i])
	{
		if (len < _strlen(lines[i]))
			len = _strlen(lines[i]);
		i++;
	}
	return (len);
}

char	*fill_max_line_len(char **lines, char *str)
{
	size_t		i;
	size_t		len;
	char		*res;

	i = 0;
	len = max_len(lines);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		print_error("malloc error");
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	while (i < len)
	{
		res[i] = ' ';
		i++;
	}
	res[i] = '\0';
	return (res);
}

bool	is_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_map_char(char c)
{
	return (c == ' ' || c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void	parse_map(char **lines, t_env *e)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		if (rich_start_map(lines[i]))
			break ;
		i++;
	}
	e->map = malloc(sizeof(char *) * (get_size(lines) - i + 1));
	j = 0;
	while (lines[j + i])
	{
		e->map[j] = fill_max_line_len(lines + i, lines[j + i]);
		j++;
	}
	e->map[j] = NULL;
	parse_map_is_valid(e);
	parse_map_is_closed(e);
}
