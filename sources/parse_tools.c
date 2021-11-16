#include "ft_nm.h"

int	elf_copy_from_offset(void *dest, size_t off, size_t len, struct nm_file *file)
{
	if (off + len > (size_t)file->stat.st_size)
		return (ERROR_INCOMPLETE_COPY);
	ft_memcpy(dest, file->mem + off, len);
	return (NO_ERROR);	
}

int	elf_copy_from_mem(void *dest, size_t len, struct nm_file *file)
{
	if ((size_t)file->offset + len > (size_t)file->stat.st_size)
		return (ERROR_INCOMPLETE_COPY);
	ft_memcpy(dest, file->mem + file->offset, len);
	return (NO_ERROR);
}

int	elf_move_from_mem(void *dest, size_t len, struct nm_file *file)
{
	int ret;

	ret = elf_copy_from_mem(dest, len, file);
	if (ret == NO_ERROR)
		file->offset += len;
	return (ret);
}
