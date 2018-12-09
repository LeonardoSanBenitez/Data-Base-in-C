CC = gcc
CFLAGS = -O3
LDLIBS = 
LDFLAGS = -lm

DEPS = btree.h btree_util.h pager.h sql_processor.h util.h
OBJ = btree.c btree_util.c pager.c sql_processor.c main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mybtree: $(OBJ)
	$(CC) -o $@ $^  $(LDFLAGS) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o mybtree
