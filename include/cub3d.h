/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:45:44 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/22 21:09:15 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

// # include "get_next_line.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

//	struct data
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	t_color	c;
	t_color	f;

	char	**map;
}	t_data;

//	printers functions
void	ft_putstr(char *str, int fd);
void	print_and_exit(char *msg);

//	parsing functions
void	check_file_name(char *filename);
void	parsing(t_data *data, char *filename);

#endif