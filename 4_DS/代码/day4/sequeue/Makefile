CC=gcc
CFLAGS=-g -c
OBJS=sequeue.o main.o
a.out:$(OBJS)
	$(CC) $(OBJS) -o $@
$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@
.PHONY:clean
clean:
	rm *.o
