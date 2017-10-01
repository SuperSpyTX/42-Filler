/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 21:10:36 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/30 23:44:48 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int					main(int argc, char **argv)
{
	t_game					*game;

	game = game_new(0);
	if (!game)
	{
		ft_printf("Error in standard input\n");
		return (0);
	}
	open(ft_strjoin("debug_", (game->mine.piece == 'O' ? "1" : "2")), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWOTH);
	if (game->mine.piece == 'O')
		dprintf(3, "Player 1 Debug:\n");
	else
		dprintf(3, "Player 2 Debug:\n");
	// Parse shit!
	while (game_loop(game))
		;
	//ft_printf("Broke out of the loop\n");
	(void)argc;
	(void)argv;
	return (0);
}

