/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:39:03 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/02/04 18:39:17 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	fill_type(char type[6][3])
{
	ft_strncpy(type[0], "NO", 2);
	ft_strncpy(type[1], "SO", 2);
	ft_strncpy(type[2], "WE", 2);
	ft_strncpy(type[3], "EA", 2);
	ft_strncpy(type[4], "C", 1);
	ft_strncpy(type[5], "F", 1);
}

int	find_type(char type[6][3], char *str)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(type[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}
