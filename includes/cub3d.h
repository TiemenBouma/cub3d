#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define SCREEN_X 2000
#define SCREEN_Y 1000
#define PI 3.141592653589793
#define XRES 100
#define YRES 100
#define X 0
#define Y 1
#define	JUNC 2
//#define XMAPRES 13
//#define YMAPRES 6

typedef float rad;

typedef struct s_put_line
{
	mlx_image_t 	*img;
	mlx_texture_t	*texture;
	double			scale;
	//u_int32_t		color;
	int				vert_line;
	int			texture_line;
	int				middle;
	int				bpp;
	int				orginal_y;

} t_put_line;

typedef	struct s_axis
{
	float	x;
	float	y;
}	t_axis;

typedef struct s_ray
{
	int		line_x;
	double	dist;
	double	scale;
	char	wall_ori;
	rad		rayangle;
	t_axis	end_pos;
}	t_ray;

typedef struct s_pov
{
	t_axis	pos;
	rad		facing; //RAD
	rad		fov; //RAD
	t_ray	*rays;// awalys the screen width
}	t_pov;

typedef struct s_cube
{
	int		window_x;
	int		window_y;
	// int		res_x;
	// int		res_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	//char	*s;
	int		floor_rgb[3];
	int		ceilling_rgb[3];

	mlx_image_t	*g_img_floor;
	mlx_image_t	*g_img_ceilling;
	mlx_image_t	*g_img_wall_no;
	mlx_image_t	*g_img_wall_ea;
	mlx_image_t	*g_img_wall_so;
	mlx_image_t	*g_img_wall_we;
	mlx_image_t	*g_img_DEMO;

	mlx_texture_t	*texture_no_wall;
	mlx_texture_t	*texture_ea_wall;
	mlx_texture_t	*texture_so_wall;
	mlx_texture_t	*texture_we_wall;
	mlx_texture_t	*texture_DEMO;

	char	**map;
	char	**cpy_map;
	int		map_width;
	int		map_length;
	int		player_count;
	int		player_x;
	int		player_y;
}	t_cube;

typedef struct s_file
{
	int		file_fd;
	char	*file_name;
	int		start_line_map;
}	t_file;

typedef struct s_vars
{
	int				gamecycle;
	t_cube			*cube;
	mlx_t			*mlx;
	t_file			*file;
	t_pov			*pov;
}	t_vars;

//PARSING
int	open_cub_file(t_file *file);
int	parsing(t_cube *cube, t_file *file);
int	parse_map_element(t_cube *cube, t_file *file);

//PARSING VALIDATE MAP
void validate_map(t_cube *cube);

//UTILS
void	*ft_memset32(void *str, int32_t c, int32_t len);
int get_rgba(int r, int g, int b, int a);
int	error_msg_exit(char * msg, int exit_code);
char	*get_line(t_file *file);
int	free_double_ptr(char **ptr);

//MLX LOOP
int	game_loop_mlx(t_vars *vars);

//INIT MLX
mlx_t	*init_mlx_stuff(t_cube *cube);

//INIT STRUCTS
void	init_structs(t_vars *vars, char **argv);

//TESTING
void printmap(char **map);
int demo_scaling(mlx_t *mlx, t_cube *cube);


//RAYCASTING
void	find_playpos(t_cube *cube, t_pov *pov);
void	cast_rays(t_cube *cube, char **map, t_pov *pov);
float	ft_fmod(float f, bool exclude_zero);
float	round_rad(rad rad);
int	print_line(t_cube *cube, t_ray *ray);
//int	print_line(t_cube *cube, t_ray *ray, u_int32_t projected_slice_height);

//Raycastigng checks
//char	find_wall_ori(t_axis ray, char **map, rad angle);
char	find_wall_ori(t_cube *cube, t_axis ray, char **map, rad angle);
bool	check_if_hit(t_cube *cube, t_axis ray, rad angle, char **map);
//bool	check_if_hit(t_axis ray, rad angle, char **map);


#endif
