CC=gcc
CFLAGS=-g -c
OBJS=tobin.o main.o
a.out:$(OBJS)
	$(CC) $(OBJS) -o $@
$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@
.PHONY:clean
clean:
	rm *.o
