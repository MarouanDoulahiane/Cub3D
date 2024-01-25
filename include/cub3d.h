/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:45:44 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/25 20:00:44 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "get_next_line.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>

//	struct data
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	char	dir;
	double	angle;
}	t_player;

typedef struct s_info
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	t_color	c;
	t_color	f;

	char	**map;
	int		rows;
	int		cols;
	t_player	player;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_info;

//	printers functions
void	ft_putstr(char *str, int fd);
void	print_and_exit(char *msg);

//	parsing functions
void	check_file_name(char *filename);
void	parsing(t_info *data, char *filename);

// 	utils functions
void	free2d(char **lines);

#endif