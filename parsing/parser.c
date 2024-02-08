/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:41:31 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 03:59:48 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	print_error(char *str)
{
	printf("%s%s%s\n", RED, str, RESET);
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
		print_error("Error\ninvalid file name");
	ext = filename + _strlen(filename) - 4;
	if (ft_strcmp(ext, ".cub") != 0)
		print_error("Error\ninvalid file extension");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("Error\ninvalid file");
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
		print_error("Error\ninvalid file");
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
