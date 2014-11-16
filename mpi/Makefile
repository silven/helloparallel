CFLAGS = -Wall -std=c++11 -Wextra
LFLAGS =-lrt
OUT=mpi

all: $(OUT)

.PHONY: clean

clean:
	$(RM) $(OUT)
	$(RM) *.o

$(OUT): mpi.cpp
	mpic++ $(CFLAGS) $< -o $@ $(LFLAGS)

