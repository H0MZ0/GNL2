/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: h0mz0 <h0mz0@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:11 by hakader           #+#    #+#             */
/*   Updated: 2025/01/03 22:19:41 by h0mz0            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     check_new_line_buffer(char *str)
{
        int     i;

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

char    *process_line(char **full_buff, int new_line_index)
{
        char    *line;
        char    *temp;

        line = ft_substr(*full_buff, 0, new_line_index + 1);
        temp = ft_substr(*full_buff, new_line_index + 1,
                        ft_strlen(*full_buff) - new_line_index - 1);
        free(*full_buff);
        *full_buff = temp;
        return (line);
}

char    *read_and_join(int fd, char **full_buff)
{
        char    *buffer;
        ssize_t bytes_read;

        buffer = (char *)malloc(BUFFER_SIZE + 1);
        if (!buffer)
                return (NULL);
        while (check_new_line_buffer(*full_buff) == -1)
        {
                bytes_read = read(fd, buffer, BUFFER_SIZE);
                if (bytes_read <= 0)
                {
                        if (bytes_read < 0)
                                return (free(buffer),free(*full_buff),NULL);
                        break ;
                }
                buffer[bytes_read] = '\0';
                *full_buff = ft_strjoin(*full_buff, buffer);
        }
        free(buffer);
        buffer = NULL;
        return (*full_buff);
}

char    *get_next_line(int fd)
{
        static char     *full_buff;
        int                     new_line_index;
        char            *line;

        if (fd < 0 || BUFFER_SIZE <= 0)
                return (NULL);
        if (read_and_join(fd, &full_buff) <= 0)
                return (NULL);
        if (!full_buff || *full_buff == '\0')
        {
                if (full_buff && *full_buff == '\0')
                        free(full_buff);
                return (NULL);
        }
        new_line_index = check_new_line_buffer(full_buff);
        if (new_line_index >= 0)
                return (process_line(&full_buff, new_line_index));
        else
        {
                line = strdup(full_buff);
                free(full_buff);
                full_buff = NULL;
                return (line);
        }
        return (NULL);
}

#include <stdio.h>
int main()
{
   int fd;
   char *ptr;
   fd = open("get_next_line.c", O_RDWR);
   if(fd == -1)
        {
      return (0);
        }  
        while ((ptr = get_next_line(fd))){
         printf("%s",ptr);
         free(ptr);
         }
   }