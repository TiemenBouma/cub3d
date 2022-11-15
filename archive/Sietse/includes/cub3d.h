#ifndef CUB3D_H
# define CUB3D_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.141592653589793
#define XRES 100
#define YRES 100
#define X 0
#define Y 1
#define	JUNC 2
#define XMAPRES 12
#define YMAPRES 5

typedef	struct s_axis
{
	float	x;
	float	y;
}	t_axis;

typedef struct s_pov
{
	t_axis	pos;
	float	facing;
	float	rayangle;
	float	fov;
	t_axis	ray;
} 	t_pov;

// prototypes for tester
bool	check_if_hit(t_axis ray, float angle, char **map);








#endif
