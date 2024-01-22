/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainParser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:01:32 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/22 21:09:27 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_file_name(char *filename)
{
	char	*extantion;
	int		fd;

	if (!(ft_strlen(filename) > 4))
		print_and_exit("Error: filename non valid!\n");
	extantion = ft_strstr(filename, ".cub");
	if (!extantion)
		print_and_exit("Error: filename non valid!\n");
	if (!(ft_strlen(extantion) == 4))
		print_and_exit("Error: filename non valid!\n");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_and_exit("Error: filename non valid!\n");
	close(fd);
}

void	parsing(t_data *data, char *filename)
{
	(void)data;
	check_file_name(filename);
}
