#include "ft_nm.h"

static int	verify_file_and_get_stat(int fd, struct stat *file_stat)
{
	if (fstat(fd, file_stat) )
		return (ERROR_NO_ACCESS);
	if ((file_stat->st_mode & S_IFMT) != S_IFREG)
		return (ERROR_NOT_REGULAR_FILE);
	return (NO_ERROR);
}

static void	*get_file_private_mapping(int fd)
{
	struct stat	file_stat;
	void		*map;

	if (verify_file_and_get_stat(fd, &file_stat) != NO_ERROR)
		return (NULL);
	map = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		return (NULL);
	return (map);
}

int	clear_file_private_mapping(void **mapp, size_t file_size)
{
	int res;

	if (!*mapp)
		return (0);
	res = munmap(*mapp, file_size);
	if (res == 0)
		*mapp = NULL;
	return (res);
}

int	get_file_info(char *filename, struct nm_file *file)
{
	int	fd;
	int	ret;

	ret = NO_ERROR;
	ft_bzero(file, sizeof(struct nm_file));
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ERROR_NO_ACCESS);
	ret = verify_file_and_get_stat(fd, &(file->stat));
	if (ret == NO_ERROR)
		file->mem = get_file_private_mapping(fd);
	close(fd);
	if (ret != NO_ERROR)
		return (ret);
	else if (file->mem == NULL)
		return (ERROR_CANNOT_MMAP);
	return (NO_ERROR);
}
