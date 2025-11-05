CC = gcc
CFLAGS = -Wall -Wextra -fPIC

LIB = libstrutils
OBJ = bstrutils.o

all: static shared

# Build Static
static: $(LIB).a main_static

$(LIB).a: $(OBJ)
	ar rcs $(LIB).a $(OBJ)

main_static: main.o $(LIB).a
	$(CC) main.o -L. -lstrutils -o main_static

# Build Shared
shared: $(LIB).so main_shared

$(LIB).so: $(OBJ)
	$(CC) -shared -o $(LIB).so $(OBJ)

main_shared: main.o $(LIB).so
	$(CC) main.o -L. -lstrutils -o main_shared

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean files
clean:
	rm -f *.o *.a *.so main_static main_shared
