#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/include/MLX42/MLX42.h"

typedef struct s_cube
{
	int		window_x;
	int		window_y;
	int		res_x;
	int		res_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	//char	*s;
	int		floor_rgb[3];
	int		ceilling_rgb[3];

	mlx_image_t	*g_img_floor;
	mlx_image_t	*g_img_ceilling;
	mlx_image_t	*g_img_demo;
	mlx_image_t	*g_img_wall_demo;

	mlx_texture_t	*texture_no_wall;
	mlx_texture_t	*texture_ea_wall;
	mlx_texture_t	*texture_so_wall;
	mlx_texture_t	*texture_we_wall;

	char	**map;
}	t_cube;

typedef struct s_file
{
	int		file_fd;
	char	*file_name;
}	t_file;

typedef struct s_vars
{
	t_cube			*cube;
	mlx_t			*mlx;
	t_file			*file;
	char			**argv;
}	t_vars;

//Parsing
int	parsing(t_vars *vars);

//UTILS
void	*ft_memset32(void *str, int32_t c, int32_t len);
int get_rgba(int r, int g, int b, int a);

//MLX LOOP
int	game_loop_mlx(t_vars *vars);

//INIT MLX
int	init_struct(t_vars *vars);

#endif
