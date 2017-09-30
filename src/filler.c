/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 21:10:36 by jkrause           #+#    #+#             */
/*   Updated: 2017/09/30 11:06:19 by jkrause          ###   ########.fr       */
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
	// Parse shit!
	while (game_loop(game))
	{
		ft_printf("LOOP!\n");
		read(0, 0, 0);
	}
	ft_printf("Broke out of the loop\n");
	(void)argc;
	(void)argv;
	return (0);
}

