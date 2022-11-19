# cub3d
Made by:            t-bouma and svos
Program languages:  C

Cub3d is a team schoolproject for Codam Collage.
The idea was to make a raycasting game engine inspired on Wolfenstein 3d.

How it works:
After downloading use the command "make" to compile the code into a executable.
execute cube with a map file like "./cube map.cub". THe map file should have .cub extention.

Once started you can move with WASD and mouse or arrow keys.

Mapfile requierments:
The file should hav 7 elements:
NO, EA, SO, WE, F, C, and a map
the windrirections should have a testure.png file. recomended pixels is 1024x1024.
F = Floor. It has a rgb color code.
C = Ceilling It has a rgb color code.
map is a represennation of the world the player can move in. It has '1' for walls, '0' for walkable squares. and "N,S,W,E" for startposiotion and initial view angle.

Example map file:

NO ./path_to_the_north_texture.png
SO ./path_to_the_south_texture.png
WE ./path_to_the_west_texture.png
EA ./path_to_the_east_texture.png
F 220,100,0
C 225,30,0

111111
100001
100001
1N0001
111111


