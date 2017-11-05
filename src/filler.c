/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 21:10:36 by jkrause           #+#    #+#             */
/*   Updated: 2017/11/05 06:45:23 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <ncurses.h>

int					main(int argc, char **argv)
{
	t_game					*game;
	int						visualizer;

	game = game_new(0);
	if (!game)
	{
		ft_printf("Error in standard input\n");
		return (0);
	}
	game->opponent_num_pieces = 0;
	visualizer = 0;
	if (argc == 2 && ft_strequ(argv[1], "-v"))
	{
		visualizer_init();
		visualizer = 1;
	}
	while (game_loop(game))
	{
		if (visualizer)
			visualize(game);
	}
	(void)argc;
	(void)argv;
	endwin();
	return (0);
}
