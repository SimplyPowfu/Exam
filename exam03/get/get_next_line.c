#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4 //commentare quando pushi

void	ft_bzero(char *s, int n)
{
	int	i = -1;

	while (++i < n)
		*(s + i) = '\0';
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return (s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	char		*r;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	r = str;
	while (s1 && *s1)
	{
		*str = *s1;
		s1++;
		str++;
	}
	while (s2 && *s2)
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
		return (0);
	tmp = ft_strjoin(*str, buffer);
	free (*str);
	*str = tmp;
	return (bytes_read);
}

static void	get_result(char **str, char **result)
{
	int		i = -1;
	int		len;
	char	*diff;

	diff = ft_strchr(*str, '\n');
	len = ft_strlen(*str) - ft_strlen(diff) + 2;
	*result = malloc(len);
	while (++i < len - 1)
		(*result)[i] = (*str)[i];
	(*result)[i] = '\0';
}

static void	del_string(char **str)
{
	char	*tmp;
	int	i;
	int	j;

	if (!ft_strchr(*str, '\n'))
	{
		free(*str);
		*str = NULL;
		return ;
	}
	tmp = malloc((ft_strlen(ft_strchr(*str, '\n'))) * sizeof(char));
	i = 0;
	j = ft_strlen(*str) - ft_strlen(ft_strchr(*str, '\n')) + 1;
	while (j < ft_strlen(*str))
		tmp[i++] = (*str)[j++];
	tmp[i] = '\0';
	free(*str);
	*str = tmp;
	if (!str)
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
	if (bytes_read == -1 || ft_strlen(string) == 0)
		return (NULL);
	get_result(&string, &result);
	del_string(&string);
	return (result);
}
