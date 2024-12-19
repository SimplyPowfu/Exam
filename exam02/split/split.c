#include<stdlib.h>

int	ft_count_wrld(const char *s, char c)
{
	int	wrld = 0;
	int i = 0;
	while (s[i])
	{
		if (s[i] != c && s[i+1] == c || s[i+1] == '\0')
			wrld++;
		i++;
	}
	return wrld;
}

void ft_strlcpy(char *dest, const char *str, int size)
{
	int i = 0;
	while (i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

char *ft_strndup(const char *s, int n)
{
	char *ptr;

	ptr = malloc(n + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, n + 1);
	return ptr;
}
static void	ft_remove(char **tab, int wrld)
{
	while (wrld >= 0)
		free(tab[wrld--]);
}
char **ft_split(const char *s, char c)
{
	char	**tab;
	int		wrld;
	int		start;
	int		end;

	tab = (char **)malloc(sizeof(char *) * (ft_count_wrld(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	wrld = 0;
	start = 0;
	end = 0;
	while (wrld < ft_count_wrld(s,c))
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != c && s[end] != '\0')
			end++;
		tab[wrld] = ft_strndup(&s[start], end - start);
		if (!tab[wrld])
			return (ft_remove(tab, wrld), NULL);
		wrld++;
	}
	tab[wrld] = NULL;
	return tab;
}
#include <stdio.h>
int main()
{
	char str1[] = "ciao fra come va?";
    char **split1 = ft_split(str1, ' ');
	int i = 0;
    while (split1[i] != NULL)
	{
        printf("%s\n", split1[i]);
        i++;
    }
}