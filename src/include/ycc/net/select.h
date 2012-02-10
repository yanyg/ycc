/*
 * select.h -- synchronous I/O multiplexing
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

#ifndef __YC_NET_SELECT_H_
#define __YC_NET_SELECT_H_

#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <ycc/compiler.h>

__BEGIN_DECLS

static inline int
select_EINTR(int nfds,
	     fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
	     struct timeval *timeout)
{
	int r;

	do {
		r = select(nfds, readfds, writefds, exceptfds, timeout);
	} while (-1 == r && EINTR == errno);

	return r;
}

#define SELECT_READ	0
#define SELECT_WRITE	1
#define SELECT_EXCEPT	2
int select_fd(int fd, struct timeval *timeout, int type);
static inline int select_fd_rd(int fd, struct timeval *timeout)
{
	return select_fd(fd, timeout, SELECT_READ);
}
static inline int select_fd_wr(int fd, struct timeval *timeout)
{
	return select_fd(fd, timeout, SELECT_WRITE);
}

__END_DECLS

#endif
