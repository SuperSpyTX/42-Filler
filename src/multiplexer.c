/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 21:35:36 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/30 11:10:41 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_foundpiece				*place_piece(t_game *game)
{
	t_location				a;
	t_location				b;
	t_foundpiece			*matchb;
	t_foundpiece			*matcha;
	int						dist;

	if (game->first_round)
		return (select_algorithm(game, game->last_placed_piece, -1));
	a = scan_map_backward(game->map, game->opponent_last_piece, game->mine);
	b = scan_map_forward(game->map, game->opponent_last_piece, game->mine);
	dist = (get_distance(a, game->opponent_last_piece) -
			get_distance(b, game->opponent_last_piece));
	matcha = select_algorithm(game, a, -1);
	matchb = select_algorithm(game, b, 1);
	ft_printf("%d %d\n", matcha, matchb);
	if (!matcha)
		return (matchb);
	else if (!matchb)
		return (matcha);
	else if (matcha->intersects < matchb->intersects)
	{
		free(matchb);
		return (matcha);
	}
	free(matcha);
	return (matchb);
}

int							game_loop(t_game *game)
{
	int						tries;
	t_foundpiece			*match;

	tries = 0;
	game->opponent_last_piece.x = -1;
	game->opponent_last_piece.y = -1;
	while (tries < 10 && !grid_fill(0, game))
		tries++;
	ft_printf("X: %d Y: %d\n", game->map->rows, game->map->columns);
	game->token = (int*)expand_get_next_line_until(0, token_parse);
	if (game->token == 0)
		return (0);
	match = place_piece(game);
	if (!match)
		return (0);
	ft_printf("%d %d\n", match->loc.x, match->loc.y);
	free(match);
	//ft_printf("X: %d Y: %d\n", game->map->rows, game->map->columns);
	//ft_printf("X: %d Y: %d\n", match->loc.x, match->loc.y);
	//if (game->opponent_last_piece.x != -1)
	return (1);
}
