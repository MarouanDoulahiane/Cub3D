/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 06:44:45 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/04 20:58:03 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	_inside_map(t_env *e, int x, int y)
{
	int	tile_x;
	int	tile_y;

	tile_x = x / SIZE;
	tile_y = y / SIZE;
	if (!(e->s_x >= 0 && e->s_x < SIZE * 6
			&& e->s_y >= HEIGHT - SIZE * 3 && e->s_y < HEIGHT))
		return ;
	if (x > 0 && y > 0 && tile_x >= 0 && tile_y >= 0
		&& tile_x < e->cols
		&& tile_y < e->rows
		&& e->map[tile_y][tile_x] == '1')
		mlx_put_pixel(e->img, e->s_x, e->s_y, get_rgba(10, 50, 150, 255));
	else
		mlx_put_pixel(e->img, e->s_x, e->s_y, get_rgba(200, 255, 255, 255));
}

void	draw_circle(t_env *e, int radius)
{
	int	i;
	int	j;

	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= radius * radius)
				mlx_put_pixel(e->img, SIZE * 3 + i,
					(HEIGHT - SIZE - SIZE / 2) + j, get_rgba(255, 0, 0, 255));
			j++;
		}
		i++;
	}
}

void	move_angle(t_env *e)
{
	if (mlx_is_key_down(e->mlx, MLX_KEY_LEFT))
	{
		e->angle -= 0.1;
		e->angle = normalize_angle(e->angle);
	}
	if (mlx_is_key_down(e->mlx, MLX_KEY_RIGHT))
	{
		e->angle += 0.1;
		e->angle = normalize_angle(e->angle);
	}
}

void	movement(void *param)
{
	t_env	*e;

	e = (t_env *)param;
	if (mlx_is_key_down(e->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(e->mlx);
		exit(0);
	}
	if (mlx_is_key_down(e->mlx, MLX_KEY_W))
		move_up(e);
	if (mlx_is_key_down(e->mlx, MLX_KEY_S))
		move_down(e);
	if (mlx_is_key_down(e->mlx, MLX_KEY_A))
		move_left(e);
	if (mlx_is_key_down(e->mlx, MLX_KEY_D))
		move_right(e);
	move_angle(e);
	draw_mini_map(e);
}

void	rendering(t_env *e)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	e->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!e->mlx)
		print_error("mlx_init failed");
	e->p_x = SIZE * 3;
	e->p_y = HEIGHT - SIZE - SIZE / 2;
	e->m_x = e->cols * SIZE / 2;
	e->m_y = e->rows * SIZE / 2;
	draw_mini_map(e);
	mlx_loop_hook(e->mlx, movement, (void *)e);
	mlx_loop(e->mlx);
	mlx_terminate(e->mlx);
}
