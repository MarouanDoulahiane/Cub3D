/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 06:44:45 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/29 08:43:58 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}


// void	_inside_map(t_info *data, int x, int y)
// {
//     int tile_x = x / TILE_SIZE;
//     int tile_y = y / TILE_SIZE;

//     if (x > 0 && y > 0 && tile_x >= 0 && tile_y >= 0 &&
//         tile_x < data->cols &&
//         tile_y < data->rows &&
//         data->map[tile_y][tile_x] == '1')
//         my_mlx_pixel_put(data, data->s_x, data->s_y, 0x004dfed1);
// 	if (x % TILE_SIZE == 0 || y % TILE_SIZE == 0)
// 		 my_mlx_pixel_put(data, data->s_x, data->s_y, 0x00FFFFFF);
// }

void	_inside_map(t_env *e, int x, int y, int s_x, int s_y)
{
    int tile_x;
	int	tile_y;

	tile_x = x / SIZE;
	tile_y = y / SIZE;
	if (!(s_x >= 0 && s_x < SIZE * 6 &&
				s_y >= HEIGHT - SIZE * 3 && s_y < HEIGHT))
		return ;
    if (x > 0 && y > 0 && tile_x >= 0 && tile_y >= 0 &&
        tile_x < e->cols &&
        tile_y < e->rows &&
        e->map[tile_y][tile_x] == '1')
        mlx_put_pixel(e->img, s_x, s_y, get_rgba(10, 50, 150, 255));
	else 
		mlx_put_pixel(e->img, s_x, s_y, get_rgba(200, 255, 255, 255));

}


void	draw_grep_map(t_env *e)
{
	int x;
	int y;

	x = 0;
	while (x < SIZE * 6)
	{
		y = HEIGHT - SIZE * 3;
		while (y < HEIGHT)
		{
			if (x == 0 || x == SIZE * 6 - 1 ||
				y == HEIGHT - SIZE * 3 || y == HEIGHT - 1)
				mlx_put_pixel(e->img, x, y, get_rgba(255, 255, 255, 255));
			y++;
		}
		x++;
	}
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
				mlx_put_pixel(e->img, SIZE * 3 + i,(HEIGHT - SIZE - SIZE / 2) + j, get_rgba(255, 0, 0, 255));
			j++;
		}
		i++;
	}
}



double	normalize_angle(double angle)
{
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void draw_line_bresenham(t_env *data, int x1, int y1, int x2, int y2)
{
    int delta_x = abs(x2 - x1);
    int delta_y = abs(y2 - y1);
    int step_x = (x1 < x2) ? 1 : -1;
    int step_y = (y1 < y2) ? 1 : -1;

    int error = delta_x - delta_y;

    while (x1 != x2 || y1 != y2)
    {
        // Draw the current pixel
        if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
			mlx_put_pixel(data->img, x1, y1, get_rgba(0, 0, 0, 255));

        // Calculate the next pixel position
        int error2 = 2 * error;

        if (error2 > -delta_y)
        {
            error -= delta_y;
            x1 += step_x;
        }

        if (error2 < delta_x)
        {
            error += delta_x;
            y1 += step_y;
        }
    }
}

void	rendering_wall(t_env *e, double ray_cast_distance, int col, bool isVertical)
{
	double wall_height_ratio = SIZE / ray_cast_distance;
	int wall_height = HEIGHT * wall_height_ratio;
	int top_pixel = (HEIGHT - wall_height) / 2;
	top_pixel = top_pixel < 0 ? 0 : top_pixel;
	int bottom_pixel = top_pixel + wall_height;
	bottom_pixel = bottom_pixel > HEIGHT ? HEIGHT : bottom_pixel;
	int y = 0;
	double shading = 1.0 - (ray_cast_distance / (e->cols * SIZE / 3));
	int alpha = 255 * shading;
	if (alpha < 0)
		alpha = 0;
	if (alpha > 255)
		alpha = 255;
	
	while (y < HEIGHT)
	{
		if (y >= top_pixel && y <= bottom_pixel)
		{
			int color = get_rgba(255, 0, 0, alpha);
			if (isVertical)
				color = get_rgba(0, 255, 0, alpha);
			mlx_put_pixel(e->img, col, y, color);
		}
		else
		{
			if (y < top_pixel)
				mlx_put_pixel(e->img, col, y, e->ceiling);
			else
				mlx_put_pixel(e->img, col, y, e->floor);
		}
		y++;
	}
}

void	cast_rays(t_env *data, double angle, int y)
{
	angle = normalize_angle(angle);
	bool facing_down = angle > 0 && angle < M_PI;
	bool facing_up = !facing_down;
	bool facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	bool facing_left = !facing_right;
	
	double	yintercept = (int)(data->y / SIZE) * SIZE;
	yintercept += facing_down ? SIZE : 0;
	double	xintercept = data->x + (yintercept - data->y) / tan(angle);
	
	double	y_step = SIZE;
	y_step *= facing_up ? -1 : 1;
	
	double	x_step = SIZE / tan(angle);
	x_step *= (facing_left && x_step > 0) ? -1 : 1;
	x_step *= (facing_right && x_step < 0) ? -1 : 1;
	
	double	Xhit = xintercept;
	double	Yhit = yintercept;
	
	Yhit += facing_down ? 1 : -1;

	while (Xhit >= 0 && Xhit < data->cols * SIZE && Yhit >= 0 && Yhit < data->rows * SIZE)
	{
		if (data->map[(long)Yhit / SIZE][(long)Xhit / SIZE] == '1')
			break;

		Xhit += x_step;
		Yhit += y_step;
	}
	double	distance = sqrt(pow(Xhit - data->x, 2) + pow(Yhit - data->y, 2));
	// let's draw the vertical line
	xintercept = (int)(data->x / SIZE) * SIZE;
	xintercept += facing_right ? SIZE : 0;
	yintercept = data->y + (xintercept - data->x) * tan(angle);
	x_step = SIZE;
	x_step *= facing_left ? -1 : 1;
	y_step = SIZE * tan(angle);
	y_step *= (facing_up && y_step > 0) ? -1 : 1;
	y_step *= (facing_down && y_step < 0) ? -1 : 1;
	Xhit = xintercept;
	Yhit = yintercept;
	Xhit += facing_right ? 1 : -1;

	while (Xhit >= 0 && Xhit < data->cols * SIZE && Yhit >= 0 && Yhit < data->rows * SIZE)
	{
		if (data->map[(long)Yhit / SIZE][(long)Xhit / SIZE] == '1')
			break;		
		Xhit += x_step;
		Yhit += y_step;
	}
	double temp_distance = sqrt(pow(Xhit - data->x, 2) + pow(Yhit - data->y, 2));
	bool	isVerticalHit = distance > temp_distance;
	if (temp_distance < distance)
		distance = temp_distance;
	distance *= cos(angle - data->angle);
	rendering_wall(data, distance, y, isVerticalHit);
	
	(void)y;
}

void	draw_player(t_env *e)
{
	double angle = e->angle - M_PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		cast_rays(e, angle, i);
		angle += (60 * M_PI / 180) / WIDTH;
		i++;
	}

}

void draw_mini_map(t_env *e)
{
	mlx_delete_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(e->mlx, e->img, 0, 0);
	int	p_x_s = SIZE * 3;
	int	p_y_s = HEIGHT - SIZE - SIZE / 2;
	int m_c_x = e->cols * SIZE / 2;
	int m_c_y = e->rows * SIZE / 2;
	int	x;
	int	y;

	draw_player(e);  
	y = 0;
	while (y < e->rows * SIZE)
	{
		x = 0;
		while (x < e->cols * SIZE)
		{
			int s_x = x - m_c_x + p_x_s;
			int s_y = y - m_c_y + p_y_s;
			int map_x = e->x + s_x - p_x_s;
			int map_y = e->y + s_y - p_y_s;
			_inside_map(e, map_x, map_y, s_x, s_y);

			x++;
		}
		y++;
	}
	draw_circle(e, 5);
	draw_line_bresenham(e, p_x_s, p_y_s, p_x_s + cos(e->angle) * 20, p_y_s + sin(e->angle) * 20);
	draw_grep_map(e);
}

void	movement(mlx_key_data_t keycode, void *param)
{
	t_env	*e;
	int		x;
	int		y;

	x = -1;
	y = -1;
	e = (t_env *)param;
	draw_mini_map(e);
	if (keycode.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(e->mlx);
		exit(0);
	}
	if (keycode.key == MLX_KEY_W)
	{
		x = e->x + cos(e->angle) * 5;
		y = e->y + sin(e->angle) * 5;
		
	}
	else if (keycode.key == MLX_KEY_S)
	{
		x = e->x - cos(e->angle) * 5;
		y = e->y - sin(e->angle) * 5;
	}
	else if (keycode.key == MLX_KEY_A)
	{
		x = e->x + sin(e->angle) * 5;
		y = e->y - cos(e->angle) * 5;
	}
	else if (keycode.key == MLX_KEY_D)
	{
		x = e->x - sin(e->angle) * 5;
		y = e->y + cos(e->angle) * 5;
	}
	else if (keycode.key == MLX_KEY_LEFT)
	{
		e->angle -= 0.1;
		e->angle = normalize_angle(e->angle);
	}
	else if (keycode.key == MLX_KEY_RIGHT)
	{
		e->angle += 0.1;
		e->angle = normalize_angle(e->angle);
	}
	if (x == -1 && y == -1)
		return ;
	if (e->map[y / SIZE][x / SIZE] != '1' && e->map[y / SIZE][x / SIZE] != ' ')
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
		printError("mlx_init failed");
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	if (!e->img)
		printError("mlx_new_image failed");
	if (mlx_image_to_window(e->mlx, e->img, 0, 0) < 0)
		printError("mlx_image_to_window failed");
	draw_mini_map(e);
	// draw grid
	int i = 0;
	while (i < WIDTH)
	{
		int j = 0;
		while (j < HEIGHT)
		{
			if (i % SIZE == 0 || j % SIZE == 0)
				mlx_put_pixel(e->img, i, j, get_rgba(255, 0, 255, 255));
			j++;
		}
		i++;
	}
	
	mlx_key_hook(e->mlx, &movement, (void *)e);
	mlx_loop(e->mlx);
	mlx_terminate(e->mlx);
}
