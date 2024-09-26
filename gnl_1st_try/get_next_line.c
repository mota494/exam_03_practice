#include "get_next_line.h"
#include <string.h>

int	has_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	find_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == BUFFER_SIZE)
		return (0);
	else
		return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*strjoinchr(char *oldstr, char c)
{
	char *newstr;
	int	i = 0;

	newstr = malloc(ft_strlen(oldstr) + 2);
	while (oldstr[i])
	{
		newstr[i] = oldstr[i];
		i++;
	}
	newstr[i] = c;
	newstr[i + 1] = '\0';
	free(oldstr);
	return (newstr);
}

char	*alocpy(char *tocpy)
{
	char	*newstr;
	int	i=0;

	newstr = malloc(ft_strlen(tocpy) + 1);
	while (tocpy[i])
	{
		newstr[i] = tocpy[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*get_line(char *oldline, char *buffer, int *passed)
{
	int	i;
	char	*toret;

	i = 0;
	toret = alocpy(oldline);
	while (buffer[i - 1] != '\n' && buffer[i])
	{
		toret = strjoinchr(toret, buffer[i]);
		i++;
		*passed += 1;
	}
	free(oldline);
	return (toret);
}

void	clean_buffer(char *buffer, int passed)
{
	int	i = 0;

	while (buffer[i + passed])
	{
		buffer[i] = buffer[i+passed];
		i++;
	}
	buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char	*line;
	int	tored;
	int	passed = 0;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = malloc(1);
	line[0] = '\0';
	if (buffer[0] != '\0')
	{
		line = get_line(line, buffer,&passed);
		clean_buffer(buffer, passed);
	}
	while (has_nl(line) == 0)
	{
		passed = 0;
		tored = read(fd, buffer, BUFFER_SIZE);
		if (tored == -1)
			break ;
		line = get_line(line, buffer, &passed);
		clean_buffer(buffer, passed);
	}
	return (line);
}

int main()
{
	int fd = open("get_next_line.h", O_RDONLY);
	char	*line;
	int	i = 11;

	while (i > 0)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i--;
	}
	free(line);
}
