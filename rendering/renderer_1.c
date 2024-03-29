/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:02:30 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 03:31:22 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool	can_move(t_env *e, int x, int y)
{
	if (e->map[y / SIZE][x / SIZE] != '1'
		&& e->map[y / SIZE][x / SIZE] != ' '
		&& (e->map[e->y / SIZE][x / SIZE] != '1'
		&& e->map[y / SIZE][e->x / SIZE] != '1'))
		return (true);
	return (false);
}

void	move_up(t_env *e)
{
	int	x;
	int	y;

	x = e->x + cos(e->angle) * 10;
	y = e->y + sin(e->angle) * 10;
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

	x = e->x - cos(e->angle) * 10;
	y = e->y - sin(e->angle) * 10;
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

	x = e->x - cos(e->angle + M_PI_2) * 10;
	y = e->y - sin(e->angle + M_PI_2) * 10;
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

	x = e->x + cos(e->angle + M_PI_2) * 10;
	y = e->y + sin(e->angle + M_PI_2) * 10;
	if (can_move(e, x, y))
	{
		e->x = x;
		e->y = y;
	}
}
