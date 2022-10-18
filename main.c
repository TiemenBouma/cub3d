#include "MLX42/MLX42.h"

int main(void)
{
	MLX42_Init();
	MLX42_Start();
	while(1)
	{
		MLX42_Update();
	}
}