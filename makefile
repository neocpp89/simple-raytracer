# Project: 214rt.
CC = g++
BIN = 214rt
CFLAGS = -o $(BIN)
SRC = \
	214rt.cpp \
	bitmap.cpp \
	color.cpp \
	intersect.cpp \
	light.cpp \
	numeric.cpp \
	ray.cpp \
	scene.cpp \
	vec.cpp

HPP = \
	color.hpp \
	bitmap.hpp

DOXYCONF = Doxyfile

.PHONY: clean
.PHONY: doc

all: $(BIN)

clean:
	rm $(BIN)

doc: $(DOXYCONF)
	doxygen $(DOXYCONF)

$(DOXYCONF): $(SRC) $(HPP)
	doxygen -g $(DOXYCONF)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC)
