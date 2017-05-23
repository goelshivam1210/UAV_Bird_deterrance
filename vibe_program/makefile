#make the vibe program and the makefile makes the object file out of the program
#this has been created because the current program has a lot of dependencies
#
#
#

program: program.o mylib.o
	g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o vib ViBe_colour.cpp -lopencv_highgui -lvibe++ -lopencv_core -lopencv_videoio -lopencv_imgproc
clean:
	$(RM) vibe
