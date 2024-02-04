/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:21:47 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/04 18:38:50 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	get_size(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

void	parse_texture(char **line, t_env *e)
{
	int	fd;

	if (get_size(line) != 2)
		print_error("invalid file");
	fd = open(line[1], O_RDONLY);
	if (fd == -1)
		print_error("invalid file");
	close(fd);
	if (!ft_strcmp("NO", line[0]))
		e->no = _strdup(line[1]);
	else if (!ft_strcmp("SO", line[0]))
		e->so = _strdup(line[1]);
	else if (!ft_strcmp("WE", line[0]))
		e->we = _strdup(line[1]);
	else if (!ft_strcmp("EA", line[0]))
		e->ea = _strdup(line[1]);
	else
		print_error("invalid file");
}

int	count_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

bool	valid_color(char *rgb)
{
	int	i;

	i = 0;
	if (rgb[i] == '+')
		i++;
	while (rgb[i])
	{
		if ((rgb[i] < '0' || rgb[i] > '9') && rgb[i] != ',')
			return (false);
		i++;
	}
	return (true);
}

void	parse_color(char **line, t_env *e)
{
	int		i;
	int		color;
	char	**rgb;

	if (get_size(line) != 2)
		print_error("invalid file");
	i = -1;
	if (count_comma(line[1]) != 2)
		print_error("invalid file");
	if (!valid_color(line[1]))
		print_error("invalid file");
	rgb = ft_split(line[1], ',');
	if (get_size(rgb) != 3)
		print_error("invalid file");
	i = 0;
	color = get_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	if (!ft_strcmp("C", line[0]))
		e->ceiling = color;
	else if (!ft_strcmp("F", line[0]))
		e->floor = color;
	free_split(rgb);
}
