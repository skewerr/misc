CC = clang

override CFLAGS+=-fPIC

OBJECTS = bufname.o decide.o misc.o
INCLUDES = bufname.h decide.h misc.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

misc.so: $(OBJECTS)
	$(CC) -shared $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	$(RM) *.o *.so
