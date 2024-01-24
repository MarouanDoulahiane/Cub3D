/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:59:58 by mdoulahi          #+#    #+#             */
/*   Updated: 2024/01/22 21:40:34 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	s_len;

	s_len = _strlen(s);
	i = 0;
	while (i <= s_len)
	{
		if (s[s_len - i] == (char)c)
			return ((char *)&s[s_len - i]);
		i++;
	}
	return (NULL);
}
