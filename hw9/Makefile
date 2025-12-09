CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lrt

TARGETS = task_worker task_dispatcher

all: $(TARGETS)

task_worker: task_worker.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

task_dispatcher: task_dispatcher.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGETS)

run_worker:
	./task_worker

run_dispatcher:
	./task_dispatcher 10 "Test message from Makefile"

.PHONY: all clean run_worker run_dispatcher
