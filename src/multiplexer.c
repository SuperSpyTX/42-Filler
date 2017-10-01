/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 21:35:36 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 01:59:30 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_foundpiece				*place_piece(t_game *game)
{
	t_location				a;
	t_location				b;
	t_foundpiece			*matchb;
	t_foundpiece			*matcha;
	//int						dist;

	if (game->opponent_last_piece.x == -1)
		return (select_algorithm(game, game->last_placed_piece, -1));
	a = scan_map_backward(game->map, game->opponent_last_piece, game->mine);
	b = scan_map_forward(game->map, game->opponent_last_piece, game->mine);
	dprintf(3, "BX: %d BY: %d\n", b.x, b.y);
	dprintf(3, "AX: %d AY: %d\n", a.x, a.y);
	dprintf(3, "Scan complete\n");
	//dist = (get_distance(a, game->opponent_last_piece)-
	//		get_distance(b, game->opponent_last_piece));
	dprintf(3, "Got A\n");
	matcha = select_algorithm(game, a, -1);
	if (matcha && matcha->intersects == 1)
		return (matcha);
	matchb = select_algorithm(game, b, 1);
	dprintf(3, "MA: %d MB: %d\n", matcha, matchb);
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
	int						*ntoken;
	static int				lastplace;
	t_location				olastplace;
	t_foundpiece			*match;

	tries = 0;
	//game->opponent_last_piece.x = -1;
	//game->opponent_last_piece.y = -1;
	dprintf(3, "LAST PLACE TAG: %d\n", lastplace);
	olastplace = game->opponent_last_piece;
	while (tries < 10 && !grid_fill(0, game))
		tries++;
	if (tries >= 10)
		return (0);
	dprintf(3, "GRID:\n%s\n", game->map->buffer);
	dprintf(3, "Grid filled, checking if OLP was properly checked...\n");
	if (game->opponent_last_piece.x == -1)
	{
		dprintf(3, "No last placed piece!\n");
		return (0);
	}
	dprintf(3, "GL: X: %d Y: %d\n", game->map->rows, game->map->columns);
	game->token = (int*)expand_get_next_line_until(0, token_parse);
	dprintf(3, "Game token == %d\n", game->token);
	if (game->token == 0)
		return (0);
	match = place_piece(game);
	dprintf(3, "Game match: %d\n", match);
	if (!match)
		return (0);
	dprintf(3, "PLACE AT: %d %d WITH %d INTERSECTS\n", match->loc.x, match->loc.y, match->intersects);
	ft_printf("%d %d\n", match->loc.x, match->loc.y);
	game->map->grid[match->loc.x][match->loc.y] = game->mine.piece_last;
	free(match);
	//ft_printf("X: %d Y: %d\n", game->map->rows, game->map->columns);
	//ft_printf("X: %d Y: %d\n", match->loc.x, match->loc.y);
	//if (game->opponent_last_piece.x != -1)
	return (1);
}
