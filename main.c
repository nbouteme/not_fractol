/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 04:41:09 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/01 05:45:28 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"
#include <complex.h>
#include <tgmath.h>
#include "key_defs.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

typedef struct	s_fracparams
{
	float	ix;
	float	iy;
}				t_fracparams;

typedef void	(*t_dfrac)(t_display *, t_fracparams);

static int selected = 0;
static int n = 30;
static float offset[2] = {-0.5, -0.5};
static float zoom = 2;

#define COMPLEX float complex

int i_to_rgb(int x)
{
	return (x * 2654435761) & 0x00FFFFFF;
}

#include <stdio.h>
#include "lsys.h"
#include "vmath.h"

t_dlist *transform_dcs(t_dlist *elem, t_mat3 m)
{
	t_drawcall *v;
	t_drawcall ret;
	t_cvec3 t;

	v = elem->content;
	t = mat3_m_vec3(m, &(float[]) {v->from.w, v->from.h, 1.0});
	ret.from.w = (*t)[0];
	ret.from.h = (*t)[1];
	mat3_m_vec3(m, &(float[]) {v->to.w, v->to.h, 1.0});
	ret.to.w = (*t)[0];
	ret.to.h = (*t)[1];
	return (ftext_lstnewelem(&ret, sizeof(ret)));
}

void pl(t_dlist *e)
{
	t_drawcall *v = e->content;
	printf("[%d, %d] -> [%d, %d]\n", v->from.w, v->from.h,
		   v->to.w, v->to.h);
}

void print_cmdlist(t_dlisthead *dcs)
{
	ftext_lstiter(dcs, (void*)&pl);
}

static void draw_list(t_dlisthead *dcs, t_display *d)
{
	t_dlist *s;
	t_dlist *e;

	s = dcs->next;
	e = dcs->next->prev;
	clear_graphics(d->g);
	while (s != e)
	{
		draw_line(d->g,
				  ((t_drawcall*)s->content)->from,
				  ((t_drawcall*)s->content)->to);
		s = s->next;
	}
	present(d->g);
	mlx_do_sync(d->conn);
	usleep(16000);
}

void	custom(t_display *d, t_fracparams params)
{
	static t_dlisthead *dcs = 0;
	static int oldn = 0;
	char *r;
	t_dlisthead *tdcs;

	(void)params;
	d->g->color = 0x00FFFFFF;
	if (oldn != n)
	{
		oldn = n;
		free(dcs);
		r = get_command_string(d->system, n / 10 + 1);
		dcs = make_draw_list(d->system, r);
		free(r);
	}
	tdcs = ftext_lstmapup(dcs, (void*)&transform_dcs, &(float[3][3])
						  {
							  {zoom / 42, 0, -offset[0] * 21},
							  {0, zoom / 42, -offset[1] * 21},
							  {0, 0, 1}
						  });
	draw_list(tdcs, d);
	ftext_lstdel(&tdcs, 0);
}

void	julia(t_display *d, t_fracparams params)
{
	COMPLEX c;
	COMPLEX z;
	int		x;
	int		y;
	int		i;

	x = -1;
	while (++x < 420 && (y = -1))
		while (++y < 420)
		{
			z = ((float)(x - 210) / (zoom * 210) + offset[0]) +
				((float)(y - 210) / (zoom * 211) + offset[1]) * I;
			c = -0.7 + params.ix + ((0.27015 + params.iy) * I);
			i = -1;
			while (++i < n && cabsf(z) < 2.0)
			{
				z *= z;
				z += c;
			}
			d->g->color = i < n ? i_to_rgb(i) : 0;
			draw_point(d->g, (t_point){x, y});
		}
}

void mandel(t_display *d, t_fracparams params)
{
	COMPLEX c;
	COMPLEX z;
	int		x;
	int		y;
	int		i;

	x = -1;
	while (++x < 420 && (y = -1))
		while (++y < 420)
		{
			c = ((float)(x - 210) / (zoom * 210) + offset[0]) + ((float)(y - 210) / (zoom * 210) + offset[1]) * I;
			z = params.ix + params.iy * I;
			i = -1;
			while (++i < n && cabsf(z) < 2.0)
			{
				z *= z;
				z += c;
			}
			d->g->color = i < n ? i_to_rgb(i) : 0;
			draw_point(d->g, (t_point){x, y});
		}
}

void draw_fractal(t_display *d)
{
	const t_dfrac	fractals[] = { &mandel, &julia, &custom };

	fractals[selected](d, (t_fracparams)
	{
		(float)get_mouse_pos().w / 420,
		(float)get_mouse_pos().h / 420
	});
}

void handle_input(t_display *d)
{
	if (is_key_pressed(ESCAPE))
		exit(42);
	offset[1] -= is_key_pressed(UP) ? (42.0 / 420) / zoom : 0;
	offset[1] += is_key_pressed(DOWN) ? (42.0 / 420) / zoom : 0;
	offset[0] -= is_key_pressed(LEFT) ? (42.0 / 420) / zoom : 0;
	offset[0] += is_key_pressed(RIGHT) ? (42.0 / 420) / zoom : 0;
	n += is_key_pressed(KP_ADD);
	n -= n > 2 ? is_key_pressed(KP_SUBTRACT) : 0;
	zoom *= is_key_pressed('p') ? 1.05 : 1.0;
	zoom /= is_key_pressed('o') ? 1.05 : 1.0;
	if (is_key_pressed('m'))
		selected = 0;
	if (is_key_pressed('j'))
		selected = 1;
	if (d->system && is_key_pressed('c'))
	{
		n = 3;
		selected = 2;
	}
	d->paint(d);
	present(d->g);
}

static int contains(const char *rhs, char **args)
{
	while (*args)
		if (ft_strcmp(rhs, *args) == 0)
			return (1);
		else
			++args;
	return (0);
}

void print_help(void)
{
	ft_putstr(
		"Usage: ./fractol [-h | lsystemfile]\n" "O/P: Zoom in/out\n"
		"Arrows: Move the camera\n" "+/-: Increase/Decrease the number"
		"of iterations\n" "m: Displays the mandelbrot fractal\n" "j:"
		"Displays the julia fractal\n" "c: displays the custom fractal,"
		"as defined by the file " "given as an argument to this"
		"program\n" "Camera movements may not be available in custom"
		"mode" "lsystemfile should be the path to a valid lsystem"
		"description\n" "A valid file is a file whose first line is an"
		"axiom, " "and subsequent lines are rules\n");
	exit(1);
}

#define B_SIZE 256

/*
** file    := Axiome <sep> Angle <Sep> Regle [Regles...]
** Axiome  := Symbole [Symboles...]
** Angle   := Entier en degres
** Regle   := Symbole = Symbole [Symboles...]
** Symbole := x -> (is_upper(x) || x == '-' || x == '+') == true
** sep     := '\n'
*/

int is_symbol(char c)
{
	return (ft_isupper(c) || c == '-' || c == '+');
}

char *parse_axiom(char **file);

t_lrule *parse_rule(char **file)
{
	t_lrule *r;

	r = malloc(sizeof(*r));
	if (!is_symbol(*file[0]))
		assert(0);
	if (1[*file] != '=')
		assert(0);
	r->symbol = *file[0];
	*file += 2;
	r->expansion = parse_axiom(file);
	*file -= 2;
	return (r);
}

char *parse_axiom(char **file)
{
	char *s;

	s = *file;
	while (*s)
		if (!is_symbol(*s))
			assert(0);
		else
			++s;
	return (ft_strdup(*file));
}

float parse_angle(char **file)
{
	char *s;

	s = *file;
	while (*s)
		if (!ft_isdigit(*s))
			assert(0);
		else
			++s;
	return ((float)ft_atoi(*file) * (M_PI / 180.0));
}

t_lsys *parse_lsys(char **file)
{
	t_lsys *ret;

	ret = new_system();
	ret->axiom = parse_axiom(file++);
	ret->angle = parse_angle(file++);
	add_ruledir(ret, parse_rule(file++));
	while (*file)
		add_ruledir(ret, parse_rule(file++));
	return (ret);
}

int		check_input(char *s)
{
	const char *auth = "\n=1234567890ABCDEFGHIJJKLMNOPQRSTUVWXYZ+-";

	while (*s)
		if (ft_strindexof(auth, *s) == -1)
			return (0);
		else
			++s;
	return (1);
}

char	*readfile(int fd, int (*check)(char *))
{
	char	*buf;
	char	*tmp;
	char	*ret;
	int		n;

	ret = ft_strnew(1);
	buf = ft_strnew(B_SIZE + 1);
	while ((n = read(fd, buf, B_SIZE)) > 0)
	{
		if (!check(buf))
			return (0);
		tmp = ret;
		ft_bzero(buf + n, B_SIZE - n);
		ret = ft_strjoin(ret, buf);
		free(tmp);
	}
	free(buf);
	return (ret);
}

static void init_lsys(t_display *d, char *fn)
{
	int fd;
	char *f;
	char **array;

	fd = open(fn, O_RDONLY);
	if (fd == -1)
		print_help();
	f = readfile(fd, &check_input);
	if (!f)
		assert(0);
	array = ft_strsplit(f, '\n');
	d->system = parse_lsys(array);
}

int main(int argc, char *argv[])
{
	t_display *d;

	if (argc > 2 || contains("-h", argv))
		print_help();
	d = new_display();
	if (argc == 2)
		init_lsys(d, argv[1]);
	d->paint = draw_fractal;
	d->input = handle_input;
	run_display(d);
	return (0);
}
