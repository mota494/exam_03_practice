#include "get_next_line.h"

int	hasnl(char *str)
{
	int	i = 0;
	
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i = 0;
	
	while (str[i])
		i++;
	return (i);
}

char	*alocpy(char *str)
{
	char	*toret;
	int	i = 0;
	
	toret = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		toret[i] = str[i];
		i++;
	}
	toret[i] = '\0';
	return (toret);
}

char	*strjoinchr(char *oldtoret, char car)
{
	char	*newtoret;
	int	i = 0;
	
	newtoret = malloc(ft_strlen(oldtoret) + 2);
	while (oldtoret[i])
	{
		newtoret[i] = oldtoret[i];
		i++;
	}
	newtoret[i] = car;
	newtoret[i+1] = '\0';
	free(oldtoret);
	return (newtoret);
}

char	*get_line(char *oldtoret, char *buffer, int *passed)
{
	char *toret;
	int	i = 0;
	
	toret = alocpy(oldtoret);
	while (buffer[i] != '\n' && buffer[i])
	{
		toret = strjoinchr(toret, buffer[i]);
		*passed += 1;
		i++;
	}
	if (buffer[i] == '\n')
	{
		toret = strjoinchr(toret, buffer[i]);
		*passed += 1;
	}
	free(oldtoret);
	return (toret);
}

void	clean_buffer(char *buffer, int toclean)
{
	int	i = 0;
	
	while (buffer[i + toclean])
	{
		buffer[i] = buffer[i + toclean];
		i++;
	}
	buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	char	*toret;
	static	char	buffer[BUFFER_SIZE];
	int	byteread;
	int	passed = 0;
	
	toret = malloc(1);
	toret[0] = '\0';
	if (buffer[0] != '\0')
	{
		toret = get_line(toret, buffer, &passed);
		clean_buffer(buffer, passed);
	}
	while (hasnl(toret) == 0)
	{
		passed = 0;
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread <= 0)
			return (NULL);
		toret = get_line(toret, buffer, &passed);
		buffer[byteread] = '\0';
		clean_buffer(buffer, passed);
	}
	return (toret);
}
