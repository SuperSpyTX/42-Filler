/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:38:22 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 20:58:02 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Too lazy to export to a libft function,
** so I'm going to do this instead.
*/

int						msize(int n)
{
	int					c;

	c = 0;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		c++;
	}
	return (c + 1);
}

int						get_min_y(t_game *game, int c, int y)
{
	if (game->token[1] > c)
		return (-game->token[1]);
	(void)y;
	return (0);
}

int						get_distance(t_location a, t_location b)
{
	int					diffx;
	int					diffy;

	diffx = (a.x - b.x);
	diffy = (a.y - b.y);
	diffx = (diffx < 0 ? diffx * -1 : diffx);
	diffy = (diffy < 0 ? diffy * -1 : diffy);
	return (diffx + diffy);
}

t_location				scan_map_forward(t_grid *grid,
							t_location loc, t_piece match)
{
	t_location			curloc;

	curloc = loc;
	while (curloc.x < grid->rows)
	{
		while (curloc.y < grid->columns)
		{
			if (grid->grid[curloc.x][curloc.y] == match.piece)
				return (curloc);
			curloc.y++;
		}
		curloc.y = 0;
		curloc.x++;
	}
	return (curloc);
}

t_location				scan_map_backward(t_grid *grid,
							t_location loc, t_piece match)
{
	t_location			curloc;

	curloc = loc;
	while (curloc.x >= 0)
	{
		while (curloc.y >= 0)
		{
			if (grid->grid[curloc.x][curloc.y] == match.piece)
				return (curloc);
			curloc.y--;
		}
		curloc.y = grid->columns - 1;
		curloc.x--;
	}
	return (curloc);
}
