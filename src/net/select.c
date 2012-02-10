/*
 * select.c -- synchronous I/O multiplexing
 *
 * Copyright (C) 2012-2013 yanyg (cppgp@qq.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING, if not see
 * <http://www.gnu.org/licenses/>.
 */

#include <ycc/net/select.h>

int select_fd(int fd, struct timeval *timeout, int type)
{
	fd_set fs, *pfs[3] = {NULL};

	FD_ZERO(&fs);
	FD_SET(fd, &fs);
	pfs[type] = &fs;

	return select_EINTR(fd+1, pfs[0], pfs[1], pfs[2], timeout);
}

/* eof */
