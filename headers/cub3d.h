/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:36:34 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/02 17:07:24 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WHITE "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PINK "\033[35m"
# define CYAN "\033[36m"
# define GREY "\033[37m"
# define RESET "\033[0m"

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>

# define SIZE 64
# define WIDTH 1280
# define HEIGHT 640

typedef struct s_env
{
	int			x;
	int			y;
	double		angle;
	char		**map;
	int			rows;
	int			cols;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceiling;
	double		mini_x;
	double		mini_y;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			p_x;
	int			p_y;
	int			m_x;
	int			m_y;
	int			s_x;
	int			s_y;
	int			map_x;
	int			map_y;
	bool		facing_down;
	bool		facing_left;
	bool		facing_right;
	bool		facing_up;
}				t_env;

typedef struct s_ray
{
	double		xintercept;
	double		yintercept;
	double		x_step;
	double		y_step;
	bool		facing_down;
	bool		facing_left;
	bool		facing_right;
	bool		facing_up;
	double		xhit;
	double		yhit;
	double		distance;
}				t_ray;

// ------------------ parser ------------------
void	parse_file(char *filename, t_env *e);
void	print_error(char *str);
int		get_rgba(int r, int g, int b, int a);

// ------------------ renderer ------------------
void	rendering(t_env *e);
void	draw_mini_map(t_env *e);
void	draw_player(t_env *e);
void	draw_circle(t_env *e, int radius);
void	draw_grep_map(t_env *e);
void	_inside_map(t_env *e, int x, int y);

// ------------------ tools ------------------
double	normalize_angle(double angle);
void	init_ray_h(t_ray *ray, t_env *data, double angle);
void	init_ray_v(t_ray *ray, t_env *data, double angle);

// ------------------ drawer ------------------
double	normalize_angle(double angle);
void	init_ray_h(t_ray *ray, t_env *e, double angle);
void	init_ray_v(t_ray *ray, t_env *e, double angle);
void	draw_grep_map(t_env *e);

#endif