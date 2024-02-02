/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 06:44:45 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/02 22:23:21 by mdoulahi         ###   ########.fr       */
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
// e->map[y / SIZE][x / SIZE] != '1' && e->map[y / SIZE][x / SIZE] != ' ' &&  (e->map[e->y / SIZE][x / SIZE] != '1' && e->map[y / SIZE][e->x / SIZE] != '1')
bool	can_move(t_env *e, int x, int y)
{
	if (e->map[y / SIZE][x / SIZE] != '1' && e->map[y / SIZE][x / SIZE] != ' ' &&  (e->map[e->y / SIZE][x / SIZE] != '1' && e->map[y / SIZE][e->x / SIZE] != '1'))
		return (true);
	return (false);
}


void	move_up(t_env *e)
{
	int	x;
	int	y;
	
	x = e->x + cos(e->angle) * 5;
	y = e->y + sin(e->angle) * 5;
	if (can_move(e, x, y))
	{
		e->x = x;
		e->y = y;
	}
}

void	move_down(t_env *e)
{
	int	x;
	int	y;
	
	x = e->x - cos(e->angle) * 5;
	y = e->y - sin(e->angle) * 5;
	if (can_move(e, x, y))
	{
		e->x = x;
		e->y = y;
	}
}

void	move_right(t_env *e)
{
	int	x;
	int	y;
	
	x = e->x - sin(e->angle) * 5;
	y = e->y + cos(e->angle) * 5;
	if (can_move(e, x, y))
	{
		e->x = x;
		e->y = y;
	}
}

void	move_left(t_env *e)
{
	int	x;
	int	y;
	
	x = e->x + sin(e->angle) * 5;
	y = e->y - cos(e->angle) * 5;
	if (can_move(e, x, y))
	{
		e->x = x;
		e->y = y;
	}
}

void	movement(void *param)
{
	t_env	*e;
	int		x;
	int		y;

	x = -1;
	y = -1;
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
	if (x == -1 && y == -1)
	{
		draw_mini_map(e);
		return ;
	}
	if (e->map[y / SIZE][x / SIZE] != '1' && e->map[y / SIZE][x / SIZE] != ' ' &&  (e->map[e->y / SIZE][x / SIZE] != '1' && e->map[y / SIZE][e->x / SIZE] != '1'))
	{
		e->x = x;
		e->y = y;
	}
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
