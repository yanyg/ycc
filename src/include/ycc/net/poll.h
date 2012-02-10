/*
 * poll.h -- wrapper of system poll
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

#ifndef __YC_NET_POLL_H_
#define __YC_NET_POLL_H_

#include <errno.h>
#include <poll.h>

#include <ycc/compiler.h>

__BEGIN_DECLS

static inline int poll_EINTR(struct pollfd *fds, nfds_t nfds, int timeout)
{
	int r;

	do {
		r = poll(fds, nfds, timeout);
	} while(-1 == r && EINTR == errno);

	return r;
}

static inline int poll_fd(int fd, short events, int timeout)
{
	struct pollfd fds[1] = { { fd, events, } };

	return poll_EINTR(fds, 1, timeout);
}

__END_DECLS

#endif
