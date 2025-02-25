/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarbona <ecarbona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:48:36 by ecarbona          #+#    #+#             */
/*   Updated: 2025/02/25 15:18:13 by ecarbona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)s + i) = '\0';
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	char		*r;
	size_t		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	r = str;
	while (s1 && *s1 != '\0')
	{
		*str = *s1;
		s1++;
		str++;
	}
	while (s2 && *s2 != '\0')
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (r);
}

static int	ft_read(int fd, char **str, char *buffer)
{
	int		bytes_read;
	char	*tmp;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0 || buffer == NULL)
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	if (bytes_read == 0)
		return (bytes_read);
	tmp = ft_strjoin(*str, buffer);
	free (*str);
	*str = tmp;
	return (bytes_read);
}

static void	get_result(char **str, char **result)
{
	size_t	i;
	size_t	len;
	char	*diff;

	diff = ft_strchr(*str, '\n');
	len = ft_strlen(*str) - ft_strlen(diff) + 2;
	*result = malloc(len);
	if (!result)
		return ;
	i = 0;
	while (i < len - 1)
	{
		(*result)[i] = (*str)[i];
		i++;
	}
	(*result)[i] = '\0';
}

static void	del_string(char **str)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if (!ft_strchr(*str, '\n'))
	{
		free(*str);
		*str = NULL;
		return ;
	}
	tmp = malloc((ft_strlen(ft_strchr(*str, '\n'))) * sizeof(char));
	if (!tmp)
		return ;
	i = 0;
	j = ft_strlen(*str) - ft_strlen(ft_strchr(*str, '\n')) + 1;
	while (j < ft_strlen(*str))
		tmp[i++] = (*str)[j++];
	tmp[i] = '\0';
	free(*str);
	*str = tmp;
	if (**str == 0)
	{
		free(*str);
		*str = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*string;
	char		*result;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	bytes_read = 1;
	while (ft_strchr(string, '\n') == NULL && bytes_read > 0)
		bytes_read = ft_read(fd, &string, buffer);
	free(buffer);
	if (bytes_read == -1)
		return (NULL);
	if (ft_strlen(string) == 0)
		return (NULL);
	get_result(&string, &result);
	del_string(&string);
	return (result);
}

// int main()
// {
// 	int	fd = open("filefd.txt", O_RDONLY);
// 	char *line;
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// 	close (fd);
// 	return (0);
// }