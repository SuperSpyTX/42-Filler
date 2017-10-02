/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 23:39:21 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 16:07:34 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int						*iterate_token(int fd, int x, int y)
{
	int					*tokenoff;
	int					curx;
	int					cury;
	int					arrindex;
	char				*line;

	line = 0;
	curx = -1;
	cury = -1;
	arrindex = 0;
	tokenoff = (int*)ft_memalloc(sizeof(int*) * 2 * ((x * y)));
	while (++curx < x && get_next_line(fd, &line) == 1)
	{
		dprintf(3, "ITL: %s\n", line);
		cury = -1;
		while (++cury < y)
			if (line[cury] == '*')
			{
				tokenoff[arrindex++] = curx;
				tokenoff[arrindex++] = cury;
			}
		free(line);
	}
	tokenoff[arrindex++] = INT_MIN;
	return (tokenoff);
}

void					*token_parse(int fd, char *line)
{
	int					x;
	int					y;

	dprintf(3, "TOKLINE: \"%s\"\n", line);
	if (ft_strstr(line, "Piece "))
	{
		x = ft_atoi(line + 6);
		if (!x)
			return (0);
		y = ft_atoi(line + 6 + msize(x));
		if (!y)
			return (0);
		return (iterate_token(fd, x, y));
	}
	return (0);
}
