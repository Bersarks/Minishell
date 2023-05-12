#include "get_next_line.h"

char	*ft_read_all_line(int fd, char *lstr)
{
	int		read_byte;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_byte = 1;
	while (!gnl_strchr(lstr, '\n') && read_byte != 0)
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_byte] = '\0';
		lstr = gnl_strjoin(lstr, buff);
	}
	free(buff);
	return (lstr);
}

char	*get_next_line(int fd)
{
	static char	*lstr[4096];
	char		*read_l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	lstr[fd] = ft_read_all_line(fd, lstr[fd]);
	if (!lstr[fd])
		return (NULL);
	read_l = ft_line_read(lstr[fd]);
	lstr[fd] = ft_update(lstr[fd]);
	return (read_l);
}
