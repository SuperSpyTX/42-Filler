/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 21:35:36 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 21:29:53 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_foundpiece				*place_piece(t_game *game)
{
	t_location				a;
	t_location				b;
	t_foundpiece			*matchb;
	t_foundpiece			*matcha;

	if (game->opponent_last_piece.x == -1)
		return (select_algorithm(game, game->last_placed_piece));
	a = scan_map_backward(game->map, game->opponent_last_piece, game->mine);
	b = scan_map_forward(game->map, game->opponent_last_piece, game->mine);
	matcha = select_algorithm(game, a);
	if (matcha && matcha->intersects == 1)
		return (matcha);
	matchb = select_algorithm(game, b);
	if (!matcha)
		return (matchb);
	else if (!matchb)
		return (matcha);
	else if (get_distance(matcha->loc, game->opponent_last_piece)
			<= get_distance(matchb->loc, game->opponent_last_piece))
	{
		free(game->mine.piece == 'X' ? matcha : matchb);
		return (game->mine.piece == 'X' ? matchb : matcha);
	}
	(matchb ? free(matchb) : 0);
	return (matchb);
}

int							game_loop(t_game *game)
{
	int						tries;
	t_foundpiece			*match;

	tries = 0;
	while (tries < 10 && !grid_fill(0, game))
		tries++;
	if (tries >= 10)
		return (0);
	game->token = (int*)expand_get_next_line_until(0, token_parse);
	if (game->token == 0)
		return (0);
	match = place_piece(game);
	if (!match)
		return (0);
	ft_printf("%d %d\n", match->loc.x, match->loc.y);
	free(match);
	return (1);
}
