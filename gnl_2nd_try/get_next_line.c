#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_hasnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_cleanbuffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && i < BUFFER_SIZE)
		i++;
	if (buffer[i] == '\n')
		i++;
	while (i < BUFFER_SIZE)
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	while (j < BUFFER_SIZE)
	{
		buffer[j] = '\0';
		j++;
	}
}

char	*ft_treat_line(char *toret, int bytesread)
{
	if (ft_strlen(toret) && bytesread != -1)
		return (toret);
	free(toret);
	return (NULL);
}

int	ft_is_empty(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] == 0 && i < BUFFER_SIZE)
		i++;
	if (i == BUFFER_SIZE)
		return (1);
	return (0);
}

char	*alocpy(char *tocpy)
{
	int	i;
	char	*toret;
	
	i = 0;
	toret = malloc(ft_strlen(tocpy) + 1);
	while (tocpy[i] != '\0')
	{
		toret[i] = tocpy[i];
		i++;
	}
	toret[i] = '\0';
	return (toret);
}

char	*strjoinchr(char *oldtoret, char c)
{
	int	i;
	char	*toret;
	
	i = 0;
	toret = malloc(ft_strlen(oldtoret) + 2);
	while (oldtoret[i] != '\0')
	{
		toret[i] = oldtoret[i];
		i++;
	}
	toret[i] = c;
	toret[i + 1] = '\0';
	free(oldtoret);
	return (toret);
}

char	*get_line(char *oldtoret, char *buffer)
{
	int	i=0;
	char	*toret;
	
	toret = alocpy(oldtoret);
	while (buffer[i - 1] != '\n' && buffer[i])
	{
		toret = strjoinchr(toret, buffer[i]);
		i++;
	}
	free(oldtoret);
	return (toret);
}

char	*ft_read_line(int fd, char *toret)
{
	static char	buffer[BUFFER_SIZE];
	int			bytesread;

	bytesread = 0;
	while (buffer[bytesread] != '\0' && bytesread < BUFFER_SIZE)
		bytesread++;
	while (ft_hasnl(toret) == 0)
	{
		if (ft_is_empty(buffer))
			bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread <= 0)
			break ;
		toret = get_line(toret, buffer);
		if (!toret)
			return (NULL);
		ft_cleanbuffer(buffer);
	}
	return (ft_treat_line(toret, bytesread));
}

char	*get_next_line(int fd)
{
	char	*toret;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	toret = malloc(1);
	if (!toret)
		return (0);
	toret[0] = '\0';
	return (ft_read_line(fd, toret));
}

/*int main()
{
	int fd = open("get_next_line.h", 0);
	char	*line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
}*/
