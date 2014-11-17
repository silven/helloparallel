CFLAGS = -Wall -std=c++11 -Wextra -Wl,--no-as-needed
LFLAGS =-lrt 
OUT=atomic

all: $(OUT)

.PHONY: clean

clean:
	$(RM) $(OUT)
	$(RM) *.o

$(OUT): atomic.cpp
	g++ $(CFLAGS) $< -o $@ $(LFLAGS)

