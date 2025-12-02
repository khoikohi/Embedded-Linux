CC = gcc
CFLAGS = -Wall -Wextra

# Targets
ALL_TARGETS = server_tcp client_tcp \
              server_udp client_udp \
              us_s us_c \
              ud_s ud_c

all: $(ALL_TARGETS)

# ---- TCP ----
server_tcp: server_tcp.c
	$(CC) $(CFLAGS) server_tcp.c -o server_tcp

client_tcp: client_tcp.c
	$(CC) $(CFLAGS) client_tcp.c -o client_tcp

# ---- UDP ----
server_udp: server_udp.c
	$(CC) $(CFLAGS) server_udp.c -o server_udp

client_udp: client_udp.c
	$(CC) $(CFLAGS) client_udp.c -o client_udp

# ---- UNIX STREAM ----
us_s: server_unix_stream.c
	$(CC) $(CFLAGS) server_unix_stream.c -o us_s

us_c: client_unix_stream.c
	$(CC) $(CFLAGS) client_unix_stream.c -o us_c

# ---- UNIX DATAGRAM ----
ud_s: server_unix_dgram.c
	$(CC) $(CFLAGS) server_unix_dgram.c -o ud_s

ud_c: client_unix_dgram.c
	$(CC) $(CFLAGS) client_unix_dgram.c -o ud_c

# Clean
clean:
	rm -f $(ALL_TARGETS)

.PHONY: all clean
