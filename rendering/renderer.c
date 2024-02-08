/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 06:44:45 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 03:37:05 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
	e->angle = normalize_angle(e->angle);
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
	e->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!e->mlx)
		print_error("Error\nmlx_init failed");
	e->p_x = SIZE * 3;
	e->p_y = HEIGHT - SIZE - SIZE / 2;
	e->m_x = e->cols * SIZE / 2;
	e->m_y = e->rows * SIZE / 2;
	draw_mini_map(e);
	mlx_loop_hook(e->mlx, movement, (void *)e);
	mlx_loop(e->mlx);
	mlx_terminate(e->mlx);
}
