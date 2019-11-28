# Custom Makefile for Alogrithms Project 4
#

.PHONY all:
all: seam

seam: seam435.cpp
	g++ seam435.cpp -o seam435

.PHONY clean:

clean:
	rm -rf seam435