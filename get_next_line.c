/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:11 by hakader           #+#    #+#             */
/*   Updated: 2025/01/06 16:45:48 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_charlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_handle(char **full_buff, int index)
{
	char	*line;
	char	*temp;

	line = ft_substr(*full_buff, 0, index + 1);
	temp = ft_substr(*full_buff, index + 1,
			ft_strlen(*full_buff) - index - 1);
	ft_free(full_buff);
	*full_buff = temp;
	return (line);
}

char	*get_line(int fd, char **full_buff)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_charlen(*full_buff) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
				return (free(buffer), ft_free(full_buff), NULL);
			break ;
		}
		buffer[bytes_read] = '\0';
		*full_buff = ft_strjoin(*full_buff, buffer);
	}
	return (free(buffer), *full_buff);
}

char	*get_next_line(int fd)
{
	static char	*full_buff;
	int			index;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!get_line(fd, &full_buff))
		return (NULL);
	if (!full_buff || *full_buff == '\0')
	{
		if (full_buff && *full_buff == '\0')
			ft_free(&full_buff);
		return (NULL);
	}
	index = ft_charlen(full_buff);
	if (index >= 0)
		return (ft_handle(&full_buff, index));
	line = ft_strdup(full_buff);
	return (ft_free(&full_buff), line);
}
// #include <stdio.h>
// int main()
// {
//     int fd;
//     char *ptr;

//     fd = open("text.txt", O_RDWR);
//     while ((ptr = get_next_line(fd)))
//     {
//         printf("%s", ptr);
//         free(ptr);
//     }
// 	close(fd);
//     return (0);
// }