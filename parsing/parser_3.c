/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:19:23 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 03:36:32 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool	is_empty(char *str)
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

void	parse_data(char **temp, t_env *e, bool find_all[7])
{
	char	type[6][3];
	int		i;

	i = 0;
	if (is_empty(temp[0]))
		return ;
	fill_type(type);
	if (get_size(temp) != 2)
		print_error("Error\ninvalid file");
	if (find_type(type, temp[0]) == -1)
		print_error("Error\ninvalid file");
	if (find_all[find_type(type, temp[0])] == true)
		print_error("Error\ninvalid file");
	if (find_type(type, temp[0]) < 4)
		parse_texture(temp, e);
	else if (find_type(type, temp[0]) < 6)
		parse_color(temp, e);
	find_all[find_type(type, temp[0])] = true;
}

bool	rich_start_map(char *line)
{
	int		i;
	bool	flag;

	i = 0;
	if (!line)
		return (false);
	flag = false;
	while (line[i])
	{
		if (line[i] == '1')
			flag = true;
		if (line[i] != ' ' && line[i] != '1')
			return (false);
		i++;
	}
	return (flag);
}

bool	are_all_true(bool find_all[7])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (find_all[i] == false)
			return (false);
		i++;
	}
	return (true);
}

void	parse_file_lines(char **lines, t_env *e)
{
	bool	find_all[6];
	char	**temp;
	int		i;

	i = -1;
	ft_bzero(find_all, 6);
	(void)e;
	while (lines[++i])
	{
		temp = ft_split(lines[i], ' ');
		if (!temp[0])
		{
			free_split(temp);
			continue ;
		}
		if (rich_start_map(lines[i]))
		{
			free_split(temp);
			break ;
		}
		parse_data(temp, e, find_all);
		free_split(temp);
	}
	if (!are_all_true(find_all) || !rich_start_map(lines[i]))
		print_error("Error\ninvalid file");
}
