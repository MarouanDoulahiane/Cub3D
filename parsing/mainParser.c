/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainParser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:01:32 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/23 17:13:38 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_file_name(char *filename)
{
	char	*extantion;
	int		fd;

	if (!(ft_strlen(filename) > 4))
		print_and_exit("Error: filename non valid!\n");
	extantion = ft_strstr(filename, ".cub");
	if (!extantion)
		print_and_exit("Error: filename non valid!\n");
	if (!(ft_strlen(extantion) == 4))
		print_and_exit("Error: filename non valid!\n");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_and_exit("Error: filename non valid!\n");
	close(fd);
}

char	**get_lines(char *filename)
{
	char	**lines;
	char	*file;
	char	*temp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_and_exit("Error: open() failed!\n");
	temp = get_next_line(fd);
	file = _strdup("");
	while (temp)
	{
		temp = ft_strjoin(temp, " ");
		file = ft_strjoin(file, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	lines = ft_split(file, '\n');
	free(file);
	return (lines);
}

void	free2d(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	init_false(bool *array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		array[i] = false;
		i++;
	}
}

void	parse_paths(t_info *data, char **temp)
{
	int	size;
	int	fd;

	size = 0;
	while (temp[size])	
		size++;
	if (size != 2)
		print_and_exit("Error: map non valid!\n");
	fd = open(temp[1], O_RDONLY);
	if (fd == -1)
		print_and_exit("Error: map non valid!\n");
	if (!ft_strcmp(temp[0], "NO"))
		data->no = _strdup(temp[1]);
	else if (!ft_strcmp(temp[0], "SO"))
		data->so = _strdup(temp[1]);
	else if (!ft_strcmp(temp[0], "WE"))
		data->we = _strdup(temp[1]);
	else if (!ft_strcmp(temp[0], "EA"))
		data->ea = _strdup(temp[1]);
	close(fd);
}

size_t	count_comma(char *str)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	return (counter);
}
bool	are_digit(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	j = i;
	while (str[j] == '0')
		j++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (i - j > 10)
		return (false);
	return (true);
}

void	copy_rgb(t_info *data, char *color, t_color rgb)
{
	if (!ft_strcmp(color, "C"))
	{
		data->c.r = rgb.r;
		data->c.g = rgb.g;
		data->c.b = rgb.b;
	}
	else
	{
		data->f.r = rgb.r;
		data->f.g = rgb.g;
		data->f.b = rgb.b;
	}
}

int	get_color_value(char *color)
{
	long	value;

	value = ft_atol(color);
	if (value > 255 || value < 0)	
		print_and_exit("Error: map non valid!\n");
	return ((int)value);
}

void	parse_colors(t_info *data, char **temp)
{
	char	**colors;
	int		size;
	t_color	rgb;

	size = 0;
	while (temp[size])
		size++;
	if (size != 2)
		print_and_exit("Error: map non valid!\n");
	if (count_comma(temp[1]) != 2)
		print_and_exit("Error: map non valid!\n");
	colors = ft_split(temp[1], ',');
	if (!colors)
		print_and_exit("Error: map non valid!\n");
	size = 0;
	while (colors[size])
	{
		if (!are_digit(colors[size]))
			print_and_exit("Error: map non valid!\n");
		if (size == 0)
			rgb.r = get_color_value(colors[size]);
		else if (size == 1)
			rgb.g = get_color_value(colors[size]);
		else if (size == 2)
			rgb.b = get_color_value(colors[size]);
		size++;
	}
	free2d(colors);
	copy_rgb(data, temp[0], rgb);
}

bool	is_only_one(char *str)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (str[i])
	{
		if (str[i] == '1')
			flag = true;
		if (str[i] != ' ' && str[i] != '1')
			return (false);
		i++;
	}
	return flag;
}

bool	are_only_one(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (!is_only_one(temp[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	if_all_true(bool *steps, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (!steps[i])
			return (false);
		i++;
	}
	return (true);	
}

void	check_file_data(t_info *data, char **lines)
{
	bool	steps[7];
	char	**temp;
	int		i;

	i = 0;
	init_false(steps, sizeof(steps));
	while (lines[i])
	{
		temp = ft_split(lines[i], ' ');
		if (!temp[0])
		{
			i++;
			free2d(temp);
			continue;  
		}
		if (!ft_strcmp(temp[0], "NO") && !steps[0])
		{
			parse_paths(data, temp);
			steps[0] = true;
		}
		else if (!ft_strcmp(temp[0], "SO") && !steps[1])
		{
			parse_paths(data, temp);
			steps[1] = true;
		}
		else if (!ft_strcmp(temp[0], "WE") && !steps[2])
		{
			parse_paths(data, temp);
			steps[2] = true;
		}
		else if (!ft_strcmp(temp[0], "EA") && !steps[3])
		{
			parse_paths(data, temp);
			steps[3] = true;
		}
		else if (!ft_strcmp(temp[0], "C") && !steps[4])
		{
			parse_colors(data, temp);
			steps[4] = true;
		}
		else if (!ft_strcmp(temp[0], "F") && !steps[5])
		{
			parse_colors(data, temp);
			steps[5] = true;
		}
		else if (are_only_one(temp))
		{
			steps[6] = true;
			free2d(temp);
			break ;
		}
		else
			print_and_exit("Error: map non valid!\n");
		free2d(temp);
		i++;
	}
	if (!if_all_true(steps, sizeof(steps)))
		print_and_exit("Error: map non valid!\n");
}

bool	have_valid_member(char *str)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (str[i])
	{
		if (str[i] == '1')
			flag = true;
		if (str[i] != ' ' && str[i] != '0' &&
			str[i] != '1' && str[i] != 'N' &&
			str[i] != 'S' && str[i] != 'W' &&
			str[i] !=  'E')
			return (false);
		i++;
	}
	return (flag);	
}

size_t	get_size(char **lines)
{
	size_t	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

size_t	get_max_len(char **lines)
{
	int		i;
	size_t	max;

	i = 0;
	max = 0;
	while (lines[i])
	{
		if (max < _strlen(lines[i]))
			max = _strlen(lines[i]);
		i++;
	}
	return (max);
}

void	_strcpy(char *dest, char *src, int max)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < max)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
}

char	**generate_rectangle_map(char **lines)
{
	char	**map;
	size_t	wl;
	size_t	max;
	size_t	i;

	i = 0;
	wl = get_size(lines);
	map = malloc(sizeof(char *) * (wl + 1));
	if (!map)
		print_and_exit("Error: malloc() failed\n");
	max = get_max_len(lines);
	while (i < wl)
	{
		map[i] = ft_calloc(max + 1, 1);
		if (!map[i])
			print_and_exit("Error: malloc() failed\n");
		_strcpy(map[i], lines[i], max);
		i++;
	}
	map[i] = NULL;
	return map;
}

bool	are_member(char c)
{
	return (c == '0' || c == 'N' ||
			c == 'S' || c == 'W' ||
			c == 'E');
}

void	is_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			
			if (are_member(map[i][j]))
				if (i <= 0 || j <= 0 || !map[i + 1] || !map[i][j + 1]
					|| map[i - 1][j] == ' ' || map[i][j - 1] == ' '
					|| map[i + 1][j] == ' ' || map[i][j + 1] == ' ')
					print_and_exit("Error: map non valid!\n");
			j++;
		}
		i++;
	}
}

void	check_map(t_info *data, char **lines)
{
	int	i;
	int	index;
(void)data;
	i = 0;
	while (lines[i] && !is_only_one(lines[i]))
		i++;
	index = i;
	while (lines[i])
	{
		if(!have_valid_member(lines[i]))
			print_and_exit("Error: map non valid!\n");
		i++;
	}
	data->map = generate_rectangle_map(lines + index);
	is_closed(data->map);
}

void	parsing(t_info *data, char *filename)
{
	char	**lines;

	(void)data;
	check_file_name(filename);
	lines = get_lines(filename);
	check_file_data(data, lines);
	check_map(data, lines);
	free2d(lines);
}
