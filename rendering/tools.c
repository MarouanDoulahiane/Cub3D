/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:35:29 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/04 19:56:04 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

double	normalize_angle(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	init_ray_h(t_ray *ray, t_env *e, double angle)
{
	ray->facing_down = angle > 0 && angle < M_PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	ray->facing_left = !ray->facing_right;
	ray->yintercept = (int)(e->y / SIZE) * SIZE;
	if (ray->facing_down)
		ray->yintercept += SIZE;
	ray->xintercept = e->x + (ray->yintercept - e->y) / tan(angle);
	ray->y_step = SIZE;
	if (ray->facing_up)
		ray->y_step *= -1;
	ray->x_step = SIZE / tan(angle);
	if (ray->facing_left && ray->x_step > 0)
		ray->x_step *= -1;
	if (ray->facing_right && ray->x_step < 0)
		ray->x_step *= -1;
	if (ray->facing_up)
		ray->yintercept--;
	ray->xhit = ray->xintercept;
	ray->yhit = ray->yintercept;
	if (ray->facing_down)
		ray->yhit++;
}

void	init_ray_v(t_ray *ray, t_env *e, double angle)
{
	ray->facing_down = angle > 0 && angle < M_PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	ray->facing_left = !ray->facing_right;
	ray->xintercept = (int)(e->x / SIZE) * SIZE;
	if (ray->facing_right)
		ray->xintercept += SIZE;
	ray->yintercept = e->y + (ray->xintercept - e->x) * tan(angle);
	ray->x_step = SIZE;
	if (ray->facing_left)
		ray->x_step *= -1;
	ray->y_step = SIZE * tan(angle);
	if (ray->facing_up && ray->y_step > 0)
		ray->y_step *= -1;
	if (ray->facing_down && ray->y_step < 0)
		ray->y_step *= -1;
	if (ray->facing_left)
		ray->xintercept--;
	ray->yhit = ray->yintercept;
	ray->xhit = ray->xintercept;
	if (ray->facing_right)
		ray->xhit++;
}

void	draw_grep_map(t_env *e)
{
	int	x;
	int	y;

	x = 0;
	while (x < SIZE * 6)
	{
		y = HEIGHT - SIZE * 3;
		while (y < HEIGHT)
		{
			if (x == 0 || x == SIZE * 6 - 1
				|| y == HEIGHT - SIZE * 3 || y == HEIGHT - 1)
				mlx_put_pixel(e->img, x, y, get_rgba(255, 255, 255, 255));
			y++;
		}
		x++;
	}
}
