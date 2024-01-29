/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 02:36:34 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/29 04:45:04 by mdoulahi         ###   ########.fr       */
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
# define WIDTH (SIZE * 20)
# define HEIGHT (SIZE * 10)

typedef struct s_env
{
	int		x;
	int		y;
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
	double			mini_x;
	double			mini_y;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_env;

typedef struct s_ray
{
	double		xintercept;
	double		yintercept;
	double		x_step;
	double		y_step;
	double		dir_x;
	double		dir_y;
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
void	printError(char *str);

// ------------------ renderer ------------------
void	rendering(t_env *e);

#endif