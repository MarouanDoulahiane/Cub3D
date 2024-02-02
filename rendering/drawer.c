/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:29 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/02 16:34:47 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	rendering_wall(t_env *e, double distance,
		int col, bool isvertical)
{
	double	ratio;
	int		wall_height;
	int		start;
	int		end;
	int		i;
	int		color;

	ratio = SIZE / distance;
	wall_height = HEIGHT * ratio;
	start = (HEIGHT - wall_height) / 2;
	if (start < 0)
		start = 0;
	end = start + wall_height;
	if (end > HEIGHT)
		end = HEIGHT;
	i = 0;
	while (i < HEIGHT)
	{
		if (i < start)
			mlx_put_pixel(e->img, col, i, e->ceiling);
		else if (i >= start && i < end)
		{
			color = get_rgba(255, 0, 0, 255);
			if (isvertical)
				color = get_rgba(0, 255, 0, 255);
			mlx_put_pixel(e->img, col, i, color);
		}
		else
			mlx_put_pixel(e->img, col, i, e->floor);
		i++;
	}
}

double	cast_ray_horizontal(t_env *data, double angle)
{
	t_ray	ray;

	angle = normalize_angle(angle);
	init_ray_h(&ray, data, angle);
	while (ray.xhit >= 0 && ray.xhit < data->cols * SIZE && ray.yhit >= 0
		&& ray.yhit < data->rows * SIZE)
	{
		if (data->map[(long)ray.yhit / SIZE][(long)ray.xhit / SIZE] == '1')
			break ;
		ray.xhit += ray.x_step;
		ray.yhit += ray.y_step;
	}
	return (sqrt(pow(ray.xhit - data->x, 2) + pow(ray.yhit - data->y, 2)));
}

double	cast_ray_vertical(t_env *data, double angle)
{
	t_ray	ray;

	angle = normalize_angle(angle);
	init_ray_v(&ray, data, angle);
	while (ray.xhit >= 0 && ray.xhit < data->cols * SIZE
		&& ray.yhit >= 0 && ray.yhit < data->rows * SIZE)
	{
		if (data->map[(long)ray.yhit / SIZE][(long)ray.xhit / SIZE] == '1')
			break ;
		ray.xhit += ray.x_step;
		ray.yhit += ray.y_step;
	}
	return (sqrt(pow(ray.xhit - data->x, 2) + pow(ray.yhit - data->y, 2)));
}

void	draw_player(t_env *e)
{
	double	angle;
	double	distance_h;
	double	distance_v;
	bool	isvertical;
	int		i;

	i = 0;
	angle = e->angle - (60 * M_PI / 180) / 2;
	while (i < WIDTH)
	{
		distance_h = cast_ray_horizontal(e, angle);
		distance_v = cast_ray_vertical(e, angle);
		isvertical = distance_h > distance_v;
		if (distance_v > distance_h)
		{
			distance_v = distance_h;
			isvertical = false;
		}
		distance_v *= cos(angle - e->angle);
		rendering_wall(e, distance_v, i, isvertical);
		angle += (60 * M_PI / 180) / WIDTH;
		i++;
	}
}

void	draw_mini_map(t_env *e)
{
	int	x;
	int	y;

	y = 0;
	mlx_delete_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(e->mlx, e->img, 0, 0);
	draw_player(e);
	while (y < e->rows * SIZE)
	{
		x = 0;
		while (x < e->cols * SIZE)
		{
			e->s_x = x - e->m_x + e->p_x;
			e->s_y = y - e->m_y + e->p_y;
			e->map_x = e->x + e->s_x - e->p_x;
			e->map_y = e->y + e->s_y - e->p_y;
			_inside_map(e, e->map_x, e->map_y);
			x++;
		}
		y++;
	}
	draw_circle(e, 5);
	draw_grep_map(e);
}
