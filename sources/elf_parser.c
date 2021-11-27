#include "ft_nm.h"

static void	elf_debug_identifier(struct nm_file *file)
{
	unsigned char	*header_id;
	
	header_id = (unsigned char *)&file->header.ident;
	printf("Magic : %x|%c|%c|%c\n",
		header_id[0], header_id[1],
		header_id[2], header_id[3]);
	if (ft_strncmp((char *)header_id, ELFMAG, SELFMAG) != 0)
	{
		printf("NOT ELF FILE\n");
		return;
	}
	printf("EI_CLASS : %d %s\n", header_id[EI_CLASS],
		header_id[EI_CLASS] == 1 ? "32bit" : "64bit");
	printf("EI_DATA : %d\n", header_id[EI_DATA]);
	printf("EI_VERSION : %d\n", header_id[EI_VERSION]);
	printf("EI_OSABI : %d\n", header_id[EI_OSABI]);
	printf("EI_PAD : %d\n", header_id[EI_PAD]);
}

static int	elf_verify_header_id(struct nm_file *file)
{
	struct	s_elf_id	header_id;

	header_id = file->header.ident;
	if (ft_strncmp((char *)header_id.magic, ELFMAG, SELFMAG) != 0)
		return (ERROR_NOT_ELF);
	if (header_id.class > 2 || header_id.class < 1)
		return (set_error("Only ELF32 and ELF64 are supported",
			ERROR_NOT_SUPPORTED));
	if (header_id.encoding > 2 || header_id.encoding < 1)
		return (set_error("Encoding not supported",
			ERROR_NOT_SUPPORTED));
	if (header_id.version != EV_CURRENT)
		return (set_error("ELF version not supported",
			ERROR_NOT_SUPPORTED));
	file->arch = header_id.class;
// Not verifying OSABI
// Not verifyind ABI version
	return (NO_ERROR);
}

int	elf_parse_header(struct nm_file *file)
{
	int err;

	if ((err = elf_copy_from_mem(&file->header.ident, EI_NIDENT, file)))
		return (err);
	if ((err = elf_verify_header_id(file)))
		return (err);
//	elf_debug_identifier(file);
	if ((err = elf_parse_header_after_id(file)))
		return (err);
	return (NO_ERROR);
}
