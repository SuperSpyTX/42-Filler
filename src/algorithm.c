/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 19:48:19 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 21:28:56 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** I had a name for this algorithm....
** I'm calling it 'Strobe'
*/

int							is_gud(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->rows || y < 0 || y >= game->map->columns)
		return (0);
	else if (game->map->grid[x][y] == game->opponent.piece)
		return (0);
	else if (game->map->grid[x][y] == game->mine.piece
			|| game->map->grid[x][y] == game->mine.piece_last)
		return (2);
	return (1);
}

t_foundpiece				*check_piece(t_game *game, int x, int y)
{
	t_foundpiece			*piece;
	int						idx;
	int						res;

	piece = (t_foundpiece*)ft_memalloc(sizeof(t_foundpiece));
	if (!piece)
		return (0);
	piece->loc.x = x;
	piece->loc.y = y;
	idx = 0;
	while (game->token[idx] != INT_MIN)
	{
		res = is_gud(game, (x + game->token[idx]), (y + game->token[idx + 1]));
		if (res == 0)
		{
			free(piece);
			return (0);
		}
		else if (res == 2)
			piece->intersects += 1;
		idx += 2;
	}
	if (piece->intersects != 1)
		ft_memdel((void**)&piece);
	return (piece);
}

t_foundpiece				*get_piece(t_game *game, int curx,
								int cury, int value)
{
	t_foundpiece			*ohgoodwillpls;

	while (curx >= 0 && curx < game->map->rows)
	{
		while (cury >= get_min_y(game, cury, 1) && cury < game->map->columns)
		{
			ohgoodwillpls = check_piece(game, curx, cury);
			if (ohgoodwillpls)
				return (ohgoodwillpls);
			cury += value;
		}
		cury = cury < 0 ? game->map->columns - 1 : 0;
		curx += value;
	}
	return (0);
}

t_foundpiece				*get_effective_piece(t_game *game,
								t_location loc, int value)
{
	t_foundpiece			*current;
	t_location				next;
	t_foundpiece			*new;

	current = get_piece(game, loc.x, loc.y, value);
	if (!current)
		return (0);
	next.x = current->loc.x;
	next.y = current->loc.y + value;
	new = get_effective_piece(game, next, value);
	if (!new && current)
		return (current);
	else if (!new)
		return (0);
	if (get_distance(current->loc, game->opponent_last_piece)
			<= get_distance(new->loc, game->opponent_last_piece))
	{
		free((game->mine.piece == 'X' ? new : current));
		return ((game->mine.piece == 'X' ? current : new));
	}
	(new ? free(new) : 0);
	return (current);
}

t_foundpiece				*select_algorithm(t_game *game, t_location loc)
{
	t_foundpiece			*found;

	found = 0;
	if (game->mine.piece == 'g')
	{
		found = get_effective_piece(game, loc, 1);
		if (!found)
			found = get_effective_piece(game, loc, -1);
	}
	else
	{
		found = get_effective_piece(game, loc, -1);
		if (!found)
			found = get_effective_piece(game, loc, 1);
	}
	return (found);
}
