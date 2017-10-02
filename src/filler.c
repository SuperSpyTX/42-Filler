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
	while (game_loop(game))
		;
	(void)argc;
	(void)argv;
	return (0);
}
