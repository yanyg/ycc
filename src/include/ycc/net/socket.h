/*
 * socket.c -- adapter of socket
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

#ifndef __YC_NET_SOCKET_H_
#define __YC_NET_SOCKET_H_

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <ycc/compiler.h>
#include <ycc/net/socket.h>

__BEGIN_DECLS

ssize_t recvn(int fd, void *buf, size_t n, int flags);
ssize_t sendn(int fd, const void *buf, size_t n, int flags);
ssize_t recvn_time(int fd, void *buf, size_t n, int flags);
ssize_t sendn_time(int fd, const void *buf, size_t n, int flags);

static inline ssize_t recv_EINTR(int fd, void *buf, size_t n, int flags)
{
	ssize_t r;

	do {
		r = recv(fd, buf, n, flags);
	} while (-1 == r && EINTR == errno);

	return r;
}

static inline ssize_t send_EINTR(int fd, const void *buf, size_t n, int flags)
{
	ssize_t r;

	do {
		r = send(fd, buf, n, flags);
	} while (-1 == r && EINTR == errno);

	return r;
}

__END_DECLS

#endif
