# Project: simple-raytracer
CC = g++
BIN = simple-raytracer
CFLAGS = -O3 -Wall -std=c++11 -march=native -I $(LIBSRCDIR) -I $(DRIVERSRCDIR)
LIBSRC = \
	Bitmap.cpp \
	Camera.cpp \
	Color.cpp \
	Primitives.cpp \
	Light.cpp \
    Screen.cpp \
	Scene.cpp

DRIVERSRC = main.cpp

LIBSRCDIR = src/libsrt/
DRIVERSRCDIR = src/driver/

FP_LIBSRC = $(addprefix $(LIBSRCDIR), $(LIBSRC))
FP_DRIVERSRC= $(addprefix $(DRIVERSRCDIR), $(DRIVERSRC))

DOXYCONF = Doxyfile

.PHONY: clean
.PHONY: doc

all: $(BIN)

clean:
	rm $(BIN)

doc: $(DOXYCONF)
	doxygen $(DOXYCONF)

$(DOXYCONF): $(FP_LIBSRC) $(FP_DRIVERSRC)
	doxygen -g $(DOXYCONF)

$(BIN): $(FP_LIBSRC) $(FP_DRIVERSRC)
	$(CC) $(CFLAGS) -o $@ $^
