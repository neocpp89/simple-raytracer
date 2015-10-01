# Project: simple-raytracer
CC = g++
BIN = simple-raytracer
CFLAGS = -O3 -Wall -std=c++11 -march=native
SRC = \
	214rt.cpp \
	Bitmap.cpp \
	Camera.cpp \
	Color.cpp \
	Primitives.cpp \
	intersect.cpp \
	Light.cpp \
	numeric.cpp \
    Screen.cpp \
	Scene.cpp

SRCDIR = src/

FP_SRC = $(addprefix $(SRCDIR), $(SRC))

DOXYCONF = Doxyfile

.PHONY: clean
.PHONY: doc

all: $(BIN)

clean:
	rm $(BIN)

doc: $(DOXYCONF)
	doxygen $(DOXYCONF)

$(DOXYCONF): $(FP_SRC)
	doxygen -g $(DOXYCONF)

$(BIN): $(FP_SRC)
	$(CC) $(CFLAGS) -o $@ $^
