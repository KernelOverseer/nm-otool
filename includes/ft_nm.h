#ifndef FT_NM_H
# define FT_NM_H
# include "libft.h"
# include "ttslist.h"
# include <stdio.h> // FOR DEBUG
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <linux/elf.h>
# define TYPE_ANY 0xFF
# define BIND_ANY 0xFF

enum e_errors{
	WARNING_ALLOCATION_FAILED = -1,
	NO_ERROR,
	ERROR_NO_ACCESS,
	ERROR_NOT_REGULAR_FILE,
	ERROR_CANNOT_MMAP,
	ERROR_INCOMPLETE_COPY,
	ERROR_NOT_ELF,
	ERROR_NOT_SUPPORTED,
	ERROR_ALLOCATION_FAILED
};

struct  s_symbol_type_checker
{
	char	*name;
	int	type;
	int	bind;
	char	letter;
};

extern struct s_symbol_type_checker	symbol_type_checker[];

struct	s_elf_id{
	unsigned char	magic[SELFMAG];
	unsigned char	class;
	unsigned char	encoding;
	unsigned char	version;
	unsigned char	osabi;
	unsigned char	abi_version;
	unsigned char	pad;
	unsigned char	nindent[EI_NIDENT - EI_PAD];
};

union	u_elf_hdr{
	struct s_elf_id		ident;
	struct elf32_hdr	elf32;
	struct elf64_hdr	elf64;
};

union	u_elf_sym{
	struct elf32_sym	elf32;
	struct elf32_sym	elf64;
};

struct	nm_sym{
	unsigned long long	value;
	char			*section;
	char			*name;
	unsigned char		type;
	unsigned char		bind;
	char			letter;
};

struct	nm_symbol{
	union u_elf_sym		*sym_ref;
	struct nm_sym		symbol;
};

struct	nm_file{
	union u_elf_hdr	header;

	unsigned char	arch;
	off_t		offset;
	struct stat	stat;
	void		*mem;
	t_list_head	symbols;
};

int	get_file_info(char *filename, struct nm_file *file);
int	clear_file_private_mapping(void **mapp, size_t file_size);

/*
**	Elf Parsing
*/

int	elf_parse_header_after_id(struct nm_file *file);
int	elf_parse_header(struct nm_file *file);
int	elf_copy_from_mem(void *dest, size_t len, struct nm_file *file);
int	elf_move_from_mem(void *dest, size_t len, struct nm_file *file);
int	elf_copy_from_offset(void *dest, size_t off, size_t len,
						struct nm_file *file);

/*
**	Error Management
*/

char	*get_error(void);
int	set_error(const char *error, int error_code);
# endif
