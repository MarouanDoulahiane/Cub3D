/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:36:34 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 03:24:05 by mdoulahi         ###   ########.fr       */
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
# include "../MLX42/MLX42.h"
# include <math.h>

# define SIZE 64
# define WIDTH 1280
# define HEIGHT 640

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_env
{
	double			text_w;
	double			text_h;
	unsigned int	*textno;
	unsigned int	*textso;
	unsigned int	*textwe;
	unsigned int	*textea;
	int				offsetx;
	int				offsety;
	int				x;
	int				y;
	double			angle;
	char			**map;
	int				rows;
	int				cols;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				floor;
	int				ceiling;
	double			mini_x;
	double			mini_y;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				p_x;
	int				p_y;
	int				m_x;
	int				m_y;
	int				s_x;
	int				s_y;
	int				map_x;
	int				map_y;
	bool			facing_down;
	bool			facing_left;
	bool			facing_right;
	bool			facing_up;
	double			x_hit;
	double			y_hit;
	int				width_no;
	int				height_no;
	int				width_so;
	int				height_so;
	int				width_we;
	int				height_we;
	int				width_ea;
	int				height_ea;
	int				direction;
	int				wall_height;
	double			y_result;
	double			distance_h;
	double			distance_v;
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

typedef struct s_render_vars
{
	int				start;
	int				y;
	int				i;
	unsigned int	*text;
	int				col;
	bool			isvertical;
}	t_render_vars;

// ------------------ parser ------------------
void	parse_file(char *filename, t_env *e);
void	print_error(char *str);
int		get_rgba(int r, int g, int b, int a);
void	parse_map_is_closed(t_env *e);
void	parse_map_is_valid(t_env *e);
bool	is_white_space(char *str);
bool	is_valid_map_char(char c);
void	parse_map(char **lines, t_env *e);
bool	rich_start_map(char *line);
int		get_size(char **temp);
void	parse_file_lines(char **lines, t_env *e);
void	fill_type(char type[6][3]);
int		find_type(char type[6][3], char *str);
void	parse_texture(char **line, t_env *e);
void	parse_color(char **line, t_env *e);
void	free_split(char **str);

// ------------------ renderer ------------------
void	rendering(t_env *e);
void	draw_mini_map(t_env *e);
void	draw_player(t_env *e);
void	move_up(t_env *e);
void	move_down(t_env *e);
void	move_right(t_env *e);
void	move_left(t_env *e);
void	rendering_wall(t_env *e, int col, bool isvertical);

// ------------------ tools ------------------
double	normalize_angle(double angle);
void	init_ray_h(t_ray *ray, t_env *data, double angle);
void	init_ray_v(t_ray *ray, t_env *data, double angle);
bool	can_move(t_env *e, int x, int y);

// ------------------ drawer ------------------
double	normalize_angle(double angle);
void	init_ray_h(t_ray *ray, t_env *e, double angle);
void	init_ray_v(t_ray *ray, t_env *e, double angle);

#endif