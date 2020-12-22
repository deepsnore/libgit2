/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#include "common.h"
#include "../posix.h"

#define HANDLE_EINTR(result, x)						\
	({								\
		do {							\
			result = (x);					\
		} while (result == -1 && errno == EINTR);		\
		result;							\
	})

ssize_t p_pread(git_file fd, void *data, size_t size, git_off_t offset)
{
	ssize_t nb = 0;

	if (!git__is_ssizet(size)) {
		errno = EINVAL;
		return -1;
	}

	if (HANDLE_EINTR(nb, pread(fd, (char *)data, size, offset)) < 0) {
		return -1;
	}
	
	return nb;
}

ssize_t p_pwrite(git_file fd, const void *data, size_t size, git_off_t offset)
{
	ssize_t nb = 0;

	if (!git__is_ssizet(size)) {
		errno = EINVAL;
		return -1;
	}

	if (HANDLE_EINTR(nb, pwrite(fd, (char *)data, size, offset)) < 0) {
		return -1;
	}

	return nb;
}
