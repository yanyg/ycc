/*
 * socket.h -- wrapper of socket
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

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <ycc/compiler.h>

__BEGIN_DECLS

static inline void
ipv4_filladdr(struct sockaddr_in *sa, in_addr_t addr, unsigned short port,
	      int domain)
{
	sa->sin_port = htons(port);
	sa->sin_family = domain;
	sa->sin_addr.s_addr = addr;
	memset(sa->sin_zero, 0, sizeof(sa->sin_zero));
}

static inline void
ipv4_filladdr_string(struct sockaddr_in *sa, const char *ip,
		     unsigned short port, int domain)
{
	return ipv4_filladdr(sa, inet_addr(ip), port, domain);
}

int ipv4_bind(int domain, int type, const struct sockaddr_in *sa);
int ipv4_listen(int domain, int type,
		const struct sockaddr_in *sa, int backlog);
int ipv4_connect_time(int domain, int type,
		      const struct sockaddr_in *sa, int timeout);

ssize_t recvn(int fd, void *buf, size_t n, int flags);
ssize_t sendn(int fd, const void *buf, size_t n, int flags);
ssize_t recv_time(int fd, void *buf, size_t n, int flags, int timeout);
ssize_t send_time(int fd, const void *buf, size_t n, int flags, int timeout);
ssize_t recvn_time(int fd, void *buf, size_t n, int flags, int timeout);
ssize_t sendn_time(int fd, const void *buf, size_t n, int flags, int timeout);

ssize_t
recvfrom_time(int fd, void *buf, size_t n, int flags,
	      struct sockaddr *src_addr, socklen_t *addrlen, int timeout);
ssize_t
sendto_time(int fd, const void *buf, size_t n, int flags,
	    const struct sockaddr *dest_addr, socklen_t addrlen, int timeout);

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

static inline ssize_t
recvfrom_EINTR(int fd, void *buf, size_t n, int flags,
	       struct sockaddr *src_addr, socklen_t *addrlen)
{
	ssize_t r;

	do {
		r = recvfrom(fd, buf, n, flags, src_addr, addrlen);
	} while (-1 == r && EINTR == errno);

	return r;
}

static inline ssize_t
sendto_EINTR(int fd, const void *buf, size_t n, int flags,
	     const struct sockaddr *dest_addr, socklen_t addrlen)
{
	ssize_t r;

	do {
		r = sendto(fd, buf, n, flags, dest_addr, addrlen);
	} while (-1 == r && EINTR == errno);

	return r;
}

__END_DECLS

#endif
