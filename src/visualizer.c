/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 04:14:09 by jkrause           #+#    #+#             */
/*   Updated: 2017/11/05 06:47:01 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <ncurses.h>

void					visualizer_reinit(void)
{
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(4, COLOR_WHITE, COLOR_GREEN);
}

void					select_color(t_game *game, char p)
{
	(void)game;
	if (p == 'O')
		attron(COLOR_PAIR(3));
	else if (p == 'X')
		attron(COLOR_PAIR(2));
	else
		attron(COLOR_PAIR(1));
}

void					visualize(t_game *game)
{
	int				row;
	int				column;

	row = -1;
	column = -1;
	visualizer_reinit();
	while (++row < game->map->rows)
	{
		column = -1;
		while (++column < game->map->columns)
		{
			select_color(game, game->map->grid[row][column]);
			mvprintw(row, column, "%c", game->map->grid[row][column]);
			//usleep(1000);
		}
		//mvprintw(row, column, "\n");
	}
	refresh();
	usleep(10000);
}

void					visualizer_init(void)
{
	newterm(NULL, stderr, stdout);
	start_color();
	noecho();
	curs_set(0);
}
