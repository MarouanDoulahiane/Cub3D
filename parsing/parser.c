/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:41:31 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/02 16:16:25 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	print_error(char *str)
{
	printf("%sError\n%s%s\n", RED, str, RESET);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	parse_file_name(char *filename)
{
	char	*ext;
	int		fd;

	if (_strlen(filename) < 4)
		print_error("invalid file name");
	ext = filename + _strlen(filename) - 4;
	if (ft_strcmp(ext, ".cub") != 0)
		print_error("invalid file extension");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("invalid file");
	close(fd);
}

char	**read_file(char *filename)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("invalid file");
	tmp = get_next_line(fd);
	line = _strdup("");
	while (tmp)
	{
		if (tmp[0] == '\n')
			tmp = ft_strjoin(tmp, " \n");
		line = ft_strjoin(line, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	lines = ft_split(line, '\n');
	free(line);
	close(fd);
	return (lines);
}

void	fill_type(char type[6][3])
{
	ft_strncpy(type[0], "NO", 2);
	ft_strncpy(type[1], "SO", 2);
	ft_strncpy(type[2], "WE", 2);
	ft_strncpy(type[3], "EA", 2);
	ft_strncpy(type[4], "C", 1);
	ft_strncpy(type[5], "F", 1);
}

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

void	parse_resolution(char **line, t_env *e)
{
	(void)e;
	(void)line;
}

void	fill_func(void (*parse[3])(char **, t_env *))
{
	parse[0] = parse_texture;
	parse[1] = parse_color;
	parse[2] = parse_resolution;
}

int	find_type(char type[6][3], char *str)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(type[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

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
		print_error("invalid file");
	if (find_type(type, temp[0]) == -1)
		print_error("invalid file");
	if (find_all[find_type(type, temp[0])] == true)
		print_error("invalid file");
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
		print_error("invalid file");
}

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

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

double	get_angle(char c)
{
	double	angle;

	if (c == 'E')
		angle = 0;
	else if (c == 'N')
		angle = 3 * M_PI / 2;
	else if (c == 'W')
		angle = M_PI;
	else
		angle = M_PI / 2;
	return (angle);
}

void	parse_map_is_valid(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	while (e->map[++i])
	{
		j = -1;
		if (is_white_space(e->map[i]))
			print_error("invalid file");
		while (e->map[i][++j])
		{
			if (!is_valid_map_char(e->map[i][j]))
				print_error("invalid file");
			if (is_player(e->map[i][j]))
			{
				if (e->x != -1 || e->y != -1)
					print_error("invalid file");
				e->x = j * SIZE + SIZE / 2;
				e->y = i * SIZE + SIZE / 2;
				e->angle = get_angle(e->map[i][j]);
			}
		}
	}
	if (e->x == -1 || e->y == -1)
		print_error("invalid file");
}

bool	is_not_wall(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == '0');
}

void	parse_map_is_closed(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	while (e->map[i])
	{
		j = 0;
		while (e->map[i][j])
		{
			if (is_not_wall(e->map[i][j]))
			{
				if (i == 0 || j == 0 || !e->map[i + 1] || !e->map[i][j + 1])
					print_error("invalid file");
				if (e->map[i - 1][j] == ' ' || e->map[i][j - 1] == ' '
					|| e->map[i + 1][j] == ' ' || e->map[i][j + 1] == ' ')
					print_error("invalid file");
			}
			j++;
		}
		i++;
	}
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

void	parse_file(char *filename, t_env *e)
{
	char	**lines;

	parse_file_name(filename);
	lines = read_file(filename);
	e->x = -1;
	e->y = -1;
	parse_file_lines(lines, e);
	parse_map(lines, e);
	free_split(lines);
	e->rows = get_size(e->map);
	e->cols = _strlen(e->map[0]);
	e->mini_x = SIZE * 3;
	e->mini_y = HEIGHT - SIZE - SIZE / 2;
}
