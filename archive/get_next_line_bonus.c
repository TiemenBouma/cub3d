/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:35:41 by tbouma            #+#    #+#             */
/*   Updated: 2022/02/09 14:13:32 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>
#include <limits.h>

static char	*make_remainder(char **string)
{
	char	*temp;

	temp = ft_strchr(*string, '\n');
	temp++;
	temp = ft_strdup(temp, ft_strlen(temp));
	if (temp == NULL)
		return (NULL);
	free(*string);
	*string = temp;
	return (*string);
}

static char	*make_string(char **string, char *buff)
{
	char	*temp;

	temp = ft_strjoin(*string, buff);
	if (temp == NULL)
		return (NULL);
	if (*string != NULL)
		free(*string);
	*string = temp;
	return (*string);
}

static char	*check_remainder_string(int fd, char *buff,
		char **string)
{
	char	*temp;

	if (buff[0] != '\0')
		*string = make_string(string, buff);
	if (*string == NULL)
		return (NULL);
	if (ft_strchr(*string, '\n'))
	{
		temp = ft_strdup(*string, ft_strchr(*string, '\n') - *string + 1);
		if (temp == NULL)
			return (NULL);
		*string = make_remainder(string);
		if (*string == NULL)
			return (NULL);
		if (ft_strlen(*string) == 0)
		{
			free(*string);
			*string = NULL;
		}
		return (temp);
	}
	return (get_next_line(fd));
}

char	*get_next_line(int fd)
{
	static char	*string[OPEN_MAX];
	char		buff[BUFFER_SIZE + 1];
	int			len_read;
	char		*temp;

	len_read = 1;
	if (!(ft_strchr(string[fd], '\n')))
	{
		len_read = read(fd, buff, BUFFER_SIZE);
		if (fd < 0 || len_read < 0)
			return (NULL);
		buff[len_read] = '\0';
	}
	else
		buff[0] = '\0';
	if (len_read == 0)
	{
		temp = string[fd];
		string[fd] = NULL;
		return (temp);
	}
	return (check_remainder_string(fd, buff, &string[fd]));
}
