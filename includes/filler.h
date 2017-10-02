/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 21:10:52 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 19:40:54 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft.h"

/*
** Standard structs
*/

typedef struct			s_location
{
	int					x;
	int					y;
}						t_location;

typedef struct			s_piece
{
	char				piece;
	char				piece_last;
}						t_piece;

typedef struct			s_grid
{
	char				*buffer;
	char				**grid;
	int					rows;
	int					columns;
}						t_grid;

typedef struct			s_game
{
	t_grid				*map;
	int					*token;
	int					first_round;
	int					game_won;
	t_piece				opponent;
	t_piece				mine;
	t_location			opponent_last_piece;
	t_location			last_placed_piece;
}						t_game;

/*
** Inherited structs
*/

typedef struct			s_foundpiece
{
	t_location			loc;
	int					intersects;
}						t_foundpiece;

/*
** Exported function prototypes.
*/

int						msize(int n);
t_grid					*grid_new(int x, int y);
t_game					*game_new(int fd);
int						game_loop(t_game *game);
int						get_distance(t_location a, t_location b);
int						get_min_y(t_game *game, int c, int y);
t_location				scan_map_forward(t_grid *grid,
							t_location loc, t_piece match);
t_location				scan_map_backward(t_grid *grid,
							t_location loc, t_piece match);

t_foundpiece			*select_algorithm(t_game *game, t_location loc);

/*
** Parsers.
*/
void					*get_player_number(int fd, char *line);
void					*generate_map(int fd, char *line);
void					*token_parse(int fd, char *line);
t_grid					*grid_fill(int fd, t_game *game);
#endif
