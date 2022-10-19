/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:35:36 by tbouma            #+#    #+#             */
/*   Updated: 2022/02/06 13:30:36 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	char	character;

	if (s == NULL)
		return (NULL);
	i = 0;
	character = (char)c;
	ptr = (char *)s;
	if (character == '\0')
		return (ptr + ft_strlen(s));
	while (ptr[i])
	{
		if (ptr[i] == character)
			return (ptr + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	len_src;
	size_t	i;

	i = 0;
	len_src = ft_strlen(src);
	if (dest_size == 0)
		return (len_src);
	while (dest_size > 1 + i && src[i])
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	dest[i] = '\0';
	return (len_src);
}

char	*ft_strdup(const char *s1, int len_s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc((len_s1 + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (len_s1 > i)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[len_s1] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_join;
	int		len_s1;
	int		len_s2;

	if (s1 == NULL)
	{
		str = ft_strdup(s2, ft_strlen(s2));
		return (str);
	}
	if (s2 == NULL)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_join = len_s2 + len_s1;
	str = (char *) malloc((len_join + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len_s1 + 1);
	ft_strlcpy(str + len_s1, s2, len_s2 + 1);
	return (str);
}
