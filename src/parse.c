/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:53:41 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 00:48:10 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void					*get_player_number(int fd, char *line)
{
	intmax_t					num;

	num = 0;
	if (ft_strstr(line, "$$$ exec p"))
	{
		num = line[10] - '0';
		if (num != 1 && num != 2)
			return (0);
		return ((void*)num);
	}
	(void)fd;
	return (0);
}

void					*generate_map(int fd, char *line)
{
	t_grid						*grid;
	int							x;
	int							y;

	(void)fd;
	grid = 0;
	if (ft_strstr(line, "Plateau "))
	{
		x = ft_atoi(line + 8);
		if (!x)
			return (0);
		y = ft_atoi(line + msize(x) + 8);
		if (!y)
			return (0);
		return (grid_new(x, y));
	}
	return (0);
}
