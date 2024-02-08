/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:33:03 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 04:15:02 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

unsigned int	*init_text(char *path, t_env *e)
{
	mlx_texture_t	*text;
	unsigned int	*data;
	int				i;
	int				j;

	i = 0;
	j = 0;
	text = mlx_load_png(path);
	if (!text)
		print_error("Error\ntexture not found");
	e->text_h = text->height;
	e->text_w = text->width;
	data = (unsigned int *)malloc(text->width * text->height * sizeof(int));
	if (!data)
		print_error("Error\nmalloc error");
	while ((unsigned int)j < text->width * text->height)
	{
		data[j] = get_rgba(text->pixels[i], text->pixels[i + 1],
				text->pixels[i + 2], text->pixels[i + 3]);
		i += 4;
		j++;
	}
	mlx_delete_texture(text);
	return (data);
}

void	init_sizes(t_env *e)
{
	mlx_texture_t	*text;

	text = mlx_load_png(e->no);
	e->height_no = text->height;
	e->width_no = text->width;
	mlx_delete_texture(text);
	text = mlx_load_png(e->so);
	e->height_so = text->height;
	e->width_so = text->width;
	mlx_delete_texture(text);
	text = mlx_load_png(e->ea);
	e->height_ea = text->height;
	e->width_ea = text->width;
	mlx_delete_texture(text);
	text = mlx_load_png(e->we);
	e->height_we = text->height;
	e->width_we = text->width;
	mlx_delete_texture(text);
}

void	read_text(t_env *e)
{
	e->textno = init_text(e->no, e);
	e->textso = init_text(e->so, e);
	e->textea = init_text(e->ea, e);
	e->textwe = init_text(e->we, e);
	init_sizes(e);
}

int	main(int ac, char **av)
{
	t_env	e;

	if (ac != 2)
	{
		printf("%sError\nusage ./cub3d <filename>\n%s", RED, RESET);
		exit(1);
	}
	parse_file(av[1], &e);
	read_text(&e);
	rendering(&e);
	exit(0);
}
