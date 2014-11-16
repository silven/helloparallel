CFLAGS = -Wall -std=c++11 -Wextra -fopenmp
LFLAGS =-lrt
OUT=openmp

all: $(OUT)

.PHONY: clean

clean:
	$(RM) $(OUT)
	$(RM) *.o

$(OUT): openmp.cpp
	g++ $(CFLAGS) $< -o $@ $(LFLAGS)

