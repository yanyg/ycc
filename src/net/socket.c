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

#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

#include <ycc/net/socket.h>

ssize_t recvn(int fd, void *buf, size_t n, int flags)
{
	size_t l = (size_t)n;
	char *p = (char*)buf;

	do {
		ssize_t r = recv_EINTR(fd, p, l, flags);

		if (r <= 0) {
			if (n == l)
				return r;
			return (ssize_t)(n - l);
		}

		l -= r;
		p += r;
	} while ((ssize_t)l > 0);

	return (ssize_t)n;	/* success */
}

ssize_t sendn(int fd, const void *buf, size_t n, int flags)
{
	size_t l = (size_t)n;
	const char *p = (const char*)buf;

	do {
		ssize_t r = send_EINTR(fd, p, l, flags);

		if (r <= 0) {
			if (n == l)
				return r;

			return (ssize_t)(n - l);
		}

		l -= r;
		p += r;
	} while ((ssize_t)l > 0);

	return (ssize_t)n;
}
