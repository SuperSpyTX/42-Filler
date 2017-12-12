/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:20:41 by jkrause           #+#    #+#             */
/*   Updated: 2017/11/17 13:57:00 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_piece					create_piece(int pnum)
{
	t_piece					piece_var;

	if (pnum == 1)
	{
		piece_var.piece = 'O';
		piece_var.piece_last = 'o';
	}
	else if (pnum == 2)
	{
		piece_var.piece = 'X';
		piece_var.piece_last = 'x';
	}
	else
		piece_var.piece = ' ';
	return (piece_var);
}

t_game					*game_new(int fd)
{
	t_game					*game;
	int						pnum;
	t_grid					*grid;

	pnum = (int)expand_get_next_line_until(fd, get_player_number);
	if (!pnum)
		return (0);
	grid = (t_grid*)expand_get_next_line_until(fd, generate_map);
	if (!grid)
	{
		free(grid);
		return (0);
	}
	game = (t_game*)ft_memalloc(sizeof(t_game));
	if (!game)
	{
		free(grid);
		return (0);
	}
	game->mine = create_piece(pnum);
	game->opponent = (pnum == 1 ? create_piece(2) : create_piece(1));
	game->map = grid;
	game->first_round = 1;
	game->num_pieces = 0;
	return (game);
}
