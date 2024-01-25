/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:51:18 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/25 23:47:13 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	ft_putstr(char *str, int fd)
{
	if (!str)
	{
		ft_putstr("Error: ft_putstr(NULL)\n", 2);
		exit(1);
	}
	while (*str)
		write(fd, str++, 1);
}

void	print_and_exit(char *msg)
{
	ft_putstr(msg, 2);
	exit(1);
}

void	f()
{
	system("leaks cub3D");
}

void	free_data(t_info data)
{
	free(data.no);
	free(data.so);
	free(data.we);
	free(data.ea);
	free2d(data.map);
}

void	printData(t_info data)
{
	printf("######### - MAP DATA - #########\n\n");
	printf("NO %s\n", data.no);
	printf("SO %s\n", data.so);
	printf("WE %s\n", data.we);
	printf("EA %s\n", data.ea);
	printf("\n");
	printf("C %d,%d,%d\n", data.c.r, data.c.g, data.c.b);
	printf("F %d,%d,%d\n\n", data.f.r, data.f.g, data.f.b);
	for (int i = 0; data.map[i]; i++)
		printf("|%s|\n", data.map[i]);
	printf("\n################################\n");
}

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

const int TILE_SIZE = 32 * 2;
const int HEIGHT = TILE_SIZE * 10;
const int WIDTH = TILE_SIZE * 16;
const int NUM_RAYS = WIDTH;
void	my_mlx_pixel_put(t_info *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_circle(t_info *data, int x, int y, int radius, int color)
{
    int i, j;

    for (i = -radius; i <= radius; i++)
    {
        for (j = -radius; j <= radius; j++)
        {
            if (i * i + j * j <= radius * radius)
            {
                int pixel_x = x + i;
                int pixel_y = y + j;

                if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
                    my_mlx_pixel_put(data, pixel_x, pixel_y, color);
            }
        }
    }
}

void draw_line_bresenham(t_info *data, int x1, int y1, int x2, int y2, int color)
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
            my_mlx_pixel_put(data, x1, y1, color);

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


void draw_2d_map(t_info *data)
{
    int x, y;

    int player_x_screen = WIDTH / 2;  // Center of the screen
    int player_y_screen = HEIGHT / 2; // Center of the screen

    int map_center_x = data->cols * TILE_SIZE / 2;
    int map_center_y = data->rows * TILE_SIZE / 2;

    y = 0;
    while (data->rows * TILE_SIZE > y)
    {
        x = 0;
        while (data->cols * TILE_SIZE > x)
        {
            // Calculate screen coordinates for each pixel on the map
            int screen_x = x - map_center_x + player_x_screen;
            int screen_y = y - map_center_y + player_y_screen;

            // Check if the pixel is within the screen bounds
            if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
            {
				
                // Calculate map coordinates for each pixel on the screen
                int map_x = data->player.x + (screen_x - player_x_screen);
                int map_y = data->player.y + (screen_y - player_y_screen);

				

                // Check if the map coordinates are within bounds
                if (map_x > 0 && map_y > 0 && map_x / TILE_SIZE >= 0 && map_x / TILE_SIZE < data->cols &&
                    map_y / TILE_SIZE >= 0 && map_y / TILE_SIZE < data->rows &&
                    data->map[map_y / TILE_SIZE][map_x / TILE_SIZE] == '1')
                    my_mlx_pixel_put(data, screen_x, screen_y, 0x0000CED1);
				if (map_x % TILE_SIZE == 0 || map_y % TILE_SIZE == 0)
					my_mlx_pixel_put(data, screen_x, screen_y, 0x00FFFFFF);
            }
            x++;
        }
        y++;
    }
    draw_circle(data, WIDTH / 2, HEIGHT / 2, 5, 0x00FF0000); // Draw the player at the center
	int x2 = WIDTH / 2 + cos(data->player.angle) * 50;
	int y2 = HEIGHT / 2 + sin(data->player.angle) * 50;
    draw_line_bresenham(data, WIDTH / 2, HEIGHT / 2, x2, y2, 0x00FF0000); // Draw the player's direction
}






    // int player_x_screen = WIDTH / 2;  // Center of the screen
    // int player_y_screen = HEIGHT / 2; // Center of the screen

    // int map_offset_x = data->player.x - player_x_screen;
    // int map_offset_y = data->player.y - player_y_screen;

int	key_press(int key_press, t_info *data)
{
	if (key_press == 53)
		exit(0);
	// A == 0, D == 2, W == 13, S == 1
	if (key_press == 13 && data->map[(int)(data->player.y + sin(data->player.angle) * 15) / TILE_SIZE][(int)(data->player.x + cos(data->player.angle) * 15) / TILE_SIZE] != '1')
	{
		data->player.x += cos(data->player.angle) * 10;
		data->player.y += sin(data->player.angle) * 10;
	}
	if (key_press == 1 && data->map[(int)(data->player.y - sin(data->player.angle) * 15) / TILE_SIZE][(int)(data->player.x - cos(data->player.angle) * 15) / TILE_SIZE] != '1')
	{
		data->player.x -= cos(data->player.angle) * 10;
		data->player.y -= sin(data->player.angle) * 10;
	}
	if (key_press == 0 && data->map[(int)(data->player.y + cos(data->player.angle) * 15) / TILE_SIZE][(int)(data->player.x - sin(data->player.angle) * 15) / TILE_SIZE] != '1')
	{
		data->player.x -= sin(data->player.angle) * 10;
		data->player.y += cos(data->player.angle) * 10;
	}
	if (key_press == 2 && data->map[(int)(data->player.y - cos(data->player.angle) * 15) / TILE_SIZE][(int)(data->player.x + sin(data->player.angle) * 15) / TILE_SIZE] != '1')
	{
		data->player.x += sin(data->player.angle) * 10;
		data->player.y -= cos(data->player.angle) * 10;
	}
	if (key_press == 123)
		data->player.angle -= 0.1;
	if (key_press == 124)
		data->player.angle += 0.1;
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw_2d_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

void	rander(t_info *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		print_and_exit("Error: mlx_init()\n");
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->win)
		print_and_exit("Error: mlx_new_window()\n");

	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		print_and_exit("Error: mlx_new_image()\n");
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	
	draw_2d_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	
	
	mlx_hook(data->win, 2, 0, key_press, data);

	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_info	data;

	// atexit(f);

	if (ac != 2)
		print_and_exit("ErrorUsage: ./cub3D <map.cub>\n");
	parsing(&data, av[1]);
	printData(data);

	rander(&data);
	
	free_data(data);
}
