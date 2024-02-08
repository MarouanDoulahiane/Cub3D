/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:29 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 03:24:07 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

double	cast_ray_horizontal(t_env *data, double angle)
{
	t_ray	ray;

	angle = normalize_angle(angle);
	init_ray_h(&ray, data, angle);
	while (ray.xhit >= 0 && ray.xhit < data->cols * SIZE && ray.yhit >= 0
		&& ray.yhit < data->rows * SIZE)
	{
		if (data->map[(long)(ray.yhit - ray.facing_up) / SIZE] \
			[(long)ray.xhit / SIZE] == '1')
			break ;
		ray.xhit += ray.x_step;
		ray.yhit += ray.y_step;
	}
	data->x_hit = ray.xhit;
	data->y_hit = ray.yhit;
	return (sqrt(pow(ray.xhit - data->x, 2) + pow(ray.yhit - data->y, 2)));
}

double	cast_ray_vertical(t_env *data, double angle, double destance_h)
{
	t_ray	ray;

	angle = normalize_angle(angle);
	init_ray_v(&ray, data, angle);
	while (ray.xhit >= 0 && ray.xhit < data->cols * SIZE
		&& ray.yhit >= 0 && ray.yhit < data->rows * SIZE)
	{
		if (data->map[(long)ray.yhit / SIZE] \
			[(long)(ray.xhit - ray.facing_left) / SIZE] == '1')
			break ;
		ray.xhit += ray.x_step;
		ray.yhit += ray.y_step;
	}
	if (destance_h > sqrt(pow(ray.xhit - data->x, 2) \
		+ pow(ray.yhit - data->y, 2)))
	{
		data->x_hit = ray.xhit;
		data->y_hit = ray.yhit;
	}
	return (sqrt(pow(ray.xhit - data->x, 2) + pow(ray.yhit - data->y, 2)));
}

int	find_direction(double angle, bool isvertical)
{
	if (!isvertical)
	{
		if (angle >= 0 && angle < M_PI)
			return (SOUTH);
		return (NORTH);
	}
	else
	{
		if (angle >= M_PI / 2 && angle < 3 * M_PI / 2)
			return (WEST);
	}
	return (EAST);
}

void	draw_player(t_env *e)
{
	double	angle;
	bool	isvertical;
	int		i;

	i = -1;
	angle = e->angle - (60 * M_PI / 180) / 2;
	while (++i < WIDTH)
	{
		angle = normalize_angle(angle);
		e->x_hit = 0;
		e->y_hit = 0;
		e->distance_h = cast_ray_horizontal(e, angle);
		e->distance_v = cast_ray_vertical(e, angle, e->distance_h);
		isvertical = e->distance_h > e->distance_v;
		if (e->distance_v > e->distance_h)
		{
			e->distance_v = e->distance_h;
			isvertical = false;
		}
		e->distance_v *= cos(angle - e->angle);
		e->direction = find_direction(angle, isvertical);
		e->wall_height = HEIGHT * SIZE / e->distance_v;
		rendering_wall(e, i, isvertical);
		angle += (60 * M_PI / 180) / WIDTH;
	}
}

void	draw_mini_map(t_env *e)
{
	mlx_delete_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(e->mlx, e->img, 0, 0);
	draw_player(e);
}
