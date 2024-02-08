/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 03:11:54 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/07 03:12:20 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_direction(t_env *e, unsigned int **text)
{
	if (e->direction == 0)
	{
		*text = e->textno;
		e->text_w = e->width_no;
		e->text_h = e->height_no;
	}
	else if (e->direction == 1)
	{
		*text = e->textso;
		e->text_w = e->width_so;
		e->text_h = e->height_so;
	}
	else if (e->direction == 2)
	{
		*text = e->textea;
		e->text_w = e->width_ea;
		e->text_h = e->height_ea;
	}
	else
	{
		*text = e->textwe;
		e->text_w = e->width_we;
		e->text_h = e->height_we;
	}
}

void	rendering_wall_helper(t_env *e, t_render_vars *var)
{
	if (var->isvertical)
		e->offsetx = (e->y_hit / SIZE - (int)e->y_hit / SIZE) * e->text_w;
	else
		e->offsetx = (e->x_hit / SIZE - (int)e->x_hit / SIZE) * e->text_w;
	e->y_result = (HEIGHT / 2) - (e->wall_height / 2);
	while (var->i < HEIGHT)
	{
		if (var->i < var->start)
			mlx_put_pixel(e->img, var->col, var->i, e->ceiling);
		else if (var->i >= var->start && var->i < var->start + e->wall_height)
		{
			if (HEIGHT < e->wall_height)
				e->offsety = (var->y - e->y_result)
					* (e->text_h / e->wall_height);
			else
				e->offsety = var->y * (e->text_h / e->wall_height);
			if (var->i >= 0 && var->i < WIDTH)
				mlx_put_pixel(e->img, var->col, var->i,
					var->text[(int)((e->text_w * e->offsety) + e->offsetx)]);
			var->y++;
		}
		else
			mlx_put_pixel(e->img, var->col, var->i, e->floor);
		var->i++;
	}
}

void	rendering_wall(t_env *e, int col, bool isvertical)
{
	t_render_vars	var;

	var.start = (HEIGHT - e->wall_height) / 2;
	var.i = 0;
	var.isvertical = isvertical;
	var.col = col;
	var.y = 0;
	init_direction(e, &var.text);
	rendering_wall_helper(e, &var);
}
