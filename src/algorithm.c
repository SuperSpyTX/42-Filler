/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 19:48:19 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 03:12:12 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_foundpiece				*check_piece(t_game *game, int x, int y)
{
	t_foundpiece			*piece;
	int						empty;
	int						idx;

	piece = (t_foundpiece*)ft_memalloc(sizeof(t_foundpiece));
	if (!piece)
		return (0);
	piece->loc.x = x;
	piece->loc.y = y;
	idx = 0;
	empty = 0;
	while (game->token[idx] != INT_MIN)
	{
		//dprintf(3, "CHECKING PIECE (%d %d) AT (%d %d)\n", x, y, x + game->token[idx], y + game->token[idx + 1]);
		if ((x + game->token[idx]) < 0 || (x + game->token[idx]) >= game->map->rows
				|| (y + game->token[idx + 1]) < 0 || (y + game->token[idx + 1]) >= game->map->columns)
		{
			free(piece);
			return (0);
		}
		else if (game->map->grid[x + game->token[idx]][y + game->token[idx + 1]] == game->mine.piece)
			piece->intersects += 1;
		else if (game->map->grid[x + game->token[idx]][y + game->token[idx + 1]] == game->opponent.piece)
		{
			free(piece);
			return (0);
		}
		else if (game->map->grid[x + game->token[idx]][y + game->token[idx + 1]] == '.')
			empty = 1;
		idx += 2;
	}
	dprintf(3, "EMPTY? %d\n", empty);
	if (piece->intersects == 0 || !empty)
		ft_memdel((void**)&piece);
	else
		dprintf(3, "SELECTED!\n");
	return (piece);
}

t_foundpiece				*get_piece(t_game *game, int curx, int cury, int value)
{
	t_foundpiece			*ohgoodwillpls;

	while (curx >= 0 && curx < game->map->rows)
	{
		while (cury >= -game->map->columns && cury < game->map->columns)
		{
			if (curx >= 0 && cury >= 0 && value == -1)
				dprintf(3, "BACKWARDS: X: %d Y: %d GRID: %c\n", curx, cury, game->map->grid[curx][cury]);
			if (curx >= 0 && cury >= 0 && value == 1)
				dprintf(3, "FORWARDS: X: %d Y: %d GRID: %c\n", curx, cury, game->map->grid[curx][cury]);
			ohgoodwillpls = check_piece(game, curx, cury);
			if (ohgoodwillpls)
				return (ohgoodwillpls);
			free(ohgoodwillpls);
			cury += value;
		}
		cury = cury < 0 ? game->map->columns - 1 : 0;
		curx += value;
	}
	return (0);
}

t_foundpiece				*get_effective_piece(t_game *game, t_location loc, int value)
{
	t_foundpiece			*current;
	t_foundpiece			*new;

	current = get_piece(game, loc.x, loc.y, value);
	if (!current)
		return (0);
	dprintf(3, "Status of current (%d): %d %d\n", current->intersects, current->loc.x, current->loc.y);
	if (current->intersects == 1)
		return (current);
	new = get_effective_piece(game, location_mod(current->loc, value), value);
	if (!new && current)
		return (current);
	else if (!new)
		return (0);
	dprintf(3, "Status of new (%d): %d %d\n", new->intersects, new->loc.x, new->loc.y);
	if (current->intersects > new->intersects)
	{
		free(current);
		return (new);
	}
	(new ? free(new) : 0);
	return (current);

}

t_foundpiece				*select_algorithm(t_game *game, t_location loc, int value)
{
	t_foundpiece			*found;
	t_foundpiece			*found2;

	found = 0;
	dprintf(3, "ALGO SELECT WITH %d\n", value);
	if (game->opponent_last_piece.x != -1)
	{
		found = get_effective_piece(game, loc, -1);
		if (!found)
			found = get_effective_piece(game, loc, 1);
		else if (found->intersects > 1)
		{
			found2 = get_effective_piece(game, loc, 1);
			if (found2 && found2->intersects <= found->intersects && found2->intersects > 0)
			{
				dprintf(3, "SELECTED FORWARDS OVER BACKWARDS - %d %d\n", found->intersects, found2->intersects);
				free(found);
				return (found2);
			}
			else
				free(found2);
			dprintf(3, "SELECTED BACKWARDS OVER FORWARDS - %d %d\n", found->intersects, found2->intersects);
		}
	}
	return (found);
}
