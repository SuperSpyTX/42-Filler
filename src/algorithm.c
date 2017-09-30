/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 19:48:19 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/29 21:26:50 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_foundpiece				*check_piece(t_game *game, int x, int y)
{
	t_foundpiece			*piece;
	int						idx;

	piece = (t_foundpiece*)ft_memalloc(sizeof(t_foundpiece));
	if (!piece)
		return (0);
	piece->loc.x = x;
	piece->loc.y = y;
	idx = 0;
	while (game->token[idx] != INT_MIN)
	{
		if (game->token[idx] < 0 || game->token[idx] >= game->map->rows
				|| game->token[idx + 1] < 0 || game->token[idx + 1] >= game->map->columns)
		{
			free(piece);
			return (0);
		}
		else if (game->map->grid[game->token[idx]][game->token[idx + 1]] == game->mine.piece
				|| game->map->grid[game->token[idx]][game->token[idx + 1]] == game->mine.piece_last)
			piece->intersects++;
		idx += 2;
	}
	if (piece->intersects == 0)
		ft_memdel((void**)&piece);
	return (piece);
}

t_foundpiece				*get_piece(t_game *game, int curx, int cury, int value)
{
	t_foundpiece			*ohgoodwillpls;

	while (curx > 0 || curx < game->map->rows)
	{
		while (cury >= 0 || cury < game->map->columns)
		{
			if (game->map->grid[curx][cury] == game->mine.piece ||
					game->map->grid[curx][cury] == game->mine.piece_last)
			{
				ohgoodwillpls = check_piece(game, curx, cury);
				if (!ohgoodwillpls)
					continue;
				return (ohgoodwillpls);
			}
			cury += value;
		}
		cury = cury < 0 ? game->map->columns : 0;
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
	if (current->intersects == 1)
		return (current);
	new = get_effective_piece(game, location_mod(current->loc, value), value);
	if (!new && current)
		return (current);
	else if (!new)
		return (0);
	else if (current->intersects > new->intersects)
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

	found = 0;
	if (game->first_round)
	{
		game->first_round = 0;
		found = (t_foundpiece*)ft_memalloc(sizeof(t_foundpiece));
		found->loc = game->last_placed_piece;
	}
	else if (game->opponent_last_piece.x != -1)
		found = get_effective_piece(game, loc, value);
	return (found);
}
