/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 15:43:23 by jkrause           #+#    #+#             */
/*   Updated: 2017/11/05 06:43:57 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Grid Positioning System
*/

void					grid_init(t_grid *grid)
{
	int					i;
	int					j;

	i = -1;
	while (++i < grid->rows)
	{
		grid->grid[i] = grid->buffer + (i * (grid->columns + 1));
		j = -1;
		while (++j < grid->columns)
			grid->grid[i][j] = '.';
		grid->grid[i][j] = '\n';
	}
	grid->buffer[(grid->rows * grid->columns + 1) + grid->columns - 2] = '\0';
}

t_grid					*grid_new(int x, int y)
{
	t_grid				*new;

	new = (t_grid*)ft_memalloc(sizeof(t_grid));
	new->buffer = (char*)ft_memalloc(sizeof(char) * ((x + 1) * (y + 1)));
	new->grid = (char**)ft_memalloc(sizeof(char*) * x);
	new->rows = x;
	new->columns = y;
	grid_init(new);
	return (new);
}

int						last_place_or_first(t_game *game, int curx, int cury)
{
	if (game->opponent_last_piece.x != -1 && game->mine.piece != 'X')
		return (0);
	return (game->map->grid[curx][cury] == '.');
}

int						parse_line(char *line, int curx, t_game *game)
{
	int					cury;

	cury = -1;
	while (++cury < game->map->columns)
	{
		if (line[cury] != 'O' && line[cury] != 'X' && line[cury] != '.')
			return (0);
		if (last_place_or_first(game, curx, cury) && line[cury] == game->opponent.piece)
		{
			game->opponent_last_piece.x = curx;
			game->opponent_last_piece.y = cury;
		}
		else if (game->first_round && line[cury] == game->mine.piece)
		{
			game->last_placed_piece.x = curx;
			game->last_placed_piece.y = cury;
		}
		game->map->grid[curx][cury] = line[cury];
	}
	return (1);
}

t_grid					*grid_fill(int fd, t_game *game)
{
	t_grid				*grid;
	int					curx;
	char				*line;

	grid = game->map;
	line = 0;
	curx = 0;
	while (get_next_line(fd, &line))
	{
		if (!parse_line(line + 4, curx++, game))
		{
			free(line);
			return (0);
		}
		free(line);
		if (curx >= game->map->rows)
			break ;
	}
	return (grid);
}
