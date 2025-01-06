/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:11 by hakader           #+#    #+#             */
/*   Updated: 2025/01/06 11:58:14 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
			free(buffer);
			if (bytes_read < 0)
				ft_free(full_buff);
			return (*full_buff);
		}
		buffer[bytes_read] = '\0';
		*full_buff = ft_strjoin(*full_buff, buffer);
	}
	free(buffer);
	return (*full_buff);
}

char	*get_next_line(int fd)
{
	static char	*full_buff[1024];
	int			index;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!get_line(fd, &full_buff[fd]))
		return (NULL);
	if (!full_buff[fd] || *full_buff[fd] == '\0')
	{
		if (full_buff[fd] && *full_buff[fd] == '\0')
			ft_free(&full_buff[fd]);
		return (NULL);
	}
	index = ft_charlen(full_buff[fd]);
	if (index >= 0)
		return (ft_handle(&full_buff[fd], index));
	line = ft_strdup(full_buff[fd]);
	return (ft_free(&full_buff[fd]), line);
}
// #include <stdio.h>
// int main() {
// 	int fd1, fd2;
// 	char *line1, *line2;

// 	fd1 = open("text.txt", O_RDWR);
// 	fd2 = open("txt.txt", O_RDWR);
// 	if (fd1 < 0 || fd2 < 0)
// 		return (1);
// 	while (1)
// 	{
// 		line1 = get_next_line(fd1);
// 		if (!line1)
// 			break;
// 		printf("%s", line1);
// 		free(line1);

// 		line2 = get_next_line(fd2);
// 		if (!line2)
// 			break;
// 		printf("%s", line2);
// 		free(line2);
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }