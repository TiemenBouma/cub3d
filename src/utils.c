#include <stdlib.h>


void	*ft_memset32(void *str, int32_t c, int32_t len)
{
	int32_t	i;
	int32_t	*ptr;

	ptr = (int32_t *)str;
	i = 0;
	while (i < len)
	{
		ptr[i] = (int32_t)c;
		i++;
	}
	return (ptr);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}