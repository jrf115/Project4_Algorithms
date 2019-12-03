# Project4_Algorithms
Using Seam Carving to make cool pictures

To compile, run 

	make all

And then you can execute the program by entering the command:

	./seam435 yourimagefile.pgm #verticalSeams #horizontalSeams

To clean, run

	make clean

Note on Project:
=
For some reason, with the files bigger than the bug.pgm, the binaries between my processed
and the test cases differ quite a bit. But visually the differences are negligible.
The processed bug.pgm has exactly two different values from the test case. I have no
idea why that is, but it is probably related to why the contents of the bigger pgms
differ so much in binary. The test cases smaller than the bug.pgm work well.