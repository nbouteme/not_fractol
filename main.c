#include "gfx.h"
#include "mlx.h"
#include <complex.h>
#include <tgmath.h>
#include "key_defs.h"
#include <stdlib.h>

typedef struct	s_fracparams
{
	float x;
	float y;
	int it;
	float ix;
	float iy;
}				t_fracparams;

typedef int (*t_dfrac)(t_fracparams);

int julia(t_fracparams params)
{
	float complex c;
	float complex z;
	int i;

	z = params.x + params.y * I;
	c = -0.7 + params.ix + ((0.27015 + params.iy) * I);
	i = -1;
	while (++i < params.it && cabsf(z) < 2.0)
		z *= z, z += c;
	return (i);
}

int mandel(t_fracparams params)
{
	float complex c;
	float complex z;
	int i;

	c = params.x + params.y * I;
	z = params.ix + params.iy * I;
	i = -1;
	while (++i < params.it && cabsf(z) < 2.0)
		z *= z, z += c;
	return (i);
}

#include <stdio.h>

static int selected = 0;
static int n = 130;
static float offset[2] = {-0.5, -0.5};
static float zoom = 2;

int i_to_rgb(int x)
{
    return (x * 2654435761) & 0x00FFFFFF;
}

void draw_fractal(t_graphics *g)
{
	const t_dfrac fractals[] = { &mandel, &julia };
	int x;
	int y;
	int i;
	
	x = -1;
	while(++x < 420 && (y = -1))
		while (++y < 420)
		{			
			i = fractals[selected]((t_fracparams)
					   {
						   1.5 * (x - 210) / (zoom * 210) + offset[0],
							   (float)(y - 210) / (zoom * 201) + offset[1],
//						   (float)x / 420 * zoom + offset[0],
//							   (float)y / 420 * zoom + offset[1],
							   n,
							   (float)get_mouse_pos().w / 420,
							   (float)get_mouse_pos().h / 420
							   });
			g->color = i < n ? i_to_rgb(i) : 0;
			draw_point(g, (t_point){x, y});
		}
}

void handle_input(t_display *d)
{
	if (is_key_pressed(ESCAPE))
		exit(42);
	if (is_key_pressed(UP))
		offset[1] -= (1.0 / 420) / zoom;
	if (is_key_pressed(DOWN))
		offset[1] += (1.0 / 420) / zoom;
	if (is_key_pressed(LEFT))
		offset[0] -= (1.0 / 420) / zoom;
	if (is_key_pressed(RIGHT))
		offset[0] += (1.0 / 420) / zoom;
	if (is_key_pressed(KP_ADD))
		++n;
	if (is_key_pressed('p'))
		zoom *= 1.05;
	if (is_key_pressed('o'))
		zoom /= 1.05;
	if (is_key_pressed('m'))
		selected = 0;
	if (is_key_pressed('j'))
		selected = 1;
	if (is_key_pressed(KP_SUBTRACT))
		n = n > 2 ? n - 1 : n;
	d->paint(d->g);
	present(d->g);
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_display *d;

	d = new_display();
	d->paint = draw_fractal;
	d->input = handle_input;
	run_display(d);
	
    return 0;
}
