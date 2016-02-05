/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:36:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 02:09:26 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <libft/std.h>

# define SIGN(x) ((x > 0) ? 1 : ((x < 0)? -1 : 0))
# define ABS(x) ((x < 0)? -(x) : (x))

struct s_display;

typedef struct				s_point
{
	int						w;
	int						h;
}							t_point;

typedef struct				s_graphics
{
	void					*int_img;
	int						*fb;
	struct s_display		*d;
	t_point					dim;
	unsigned				color;
}							t_graphics;

enum						e_rel
{
	IN = 0x00000000,
	LEFT = 0x00000001,
	RIGHT = 0x00000100,
	TOP = 0x00010000,
	BOT = 0x01000000
};

void						draw_point_bare(t_graphics *g, t_point pos);
void						draw_point(t_graphics *g, t_point pos);
t_graphics					*new_graphics(struct s_display *d);
unsigned					get_pixel(t_graphics *g, t_point pos);
void						present(t_graphics *g);
void						clear_graphics(t_graphics *g);
void						draw_line(t_graphics *g, t_point a, t_point b);
void						draw_line_bare(t_graphics *g, t_point a, t_point b);

#endif
