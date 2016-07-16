# UAV_Bird_deterrance

  Object Detection (ViBe)
  -----

    In order to run Vibe implementation:
    -  Install the ViBe* (copyright of the University de leige, Belgium*) Libraries
    -  Run the code

   Installing the ViBe Library:
  ------
    Using Linux Machine,
    We have tested this on Ubuntu 16.04 with opencv 3.1

    
  * Compilation
  
  To compile the program, go into the 'build' directory (or make one) in the libvibe++ and enter the following
  commands:
```
    $ cmake -DCMAKE_BUILD_TYPE=Release ..
    $ make
```
  By default, the example programs are compiled. If you want to disable the
compilation of these programs, you must set to `'OFF'` the
`'libvibe++_COMPILE_EXAMPLES'` variable in the cache of CMake. As an alternative,
you can use the following commands instead of the previous ones:
```
 $ cmake -DCMAKE_BUILD_TYPE=Release -Dlibvibe++_COMPILE_EXAMPLES:BOOL=OFF ..
 $ make
```
Note that on OS X, the program will not compile with clang++ (the default
compiler used by CMake). You can for instance use GCC as following (considering
that you installed, for example, GCC 5 with MacPorts):
```
$ cmake -DCMAKE_CXX_COMPILER=g++-mp-5 -DCMAKE_BUILD_TYPE=Release ..
$ make
```
or the Intel compiler:
```
$ cmake -DCMAKE_CXX_COMPILER=icpc -DCMAKE_BUILD_TYPE=Release ..
$ make
```
 * Installation
  
To install the libvibe++ onto your system after the compilation step, you can
enter the following command (in superuser mode):
```
 $ sudo make install
```
The files will be installed into '/usr/local'.

This installs the library in the system so all the dependencies are cleared now.
Next step is the running of the Vibe Code.

Running the main code:
--------------
  Compilation
  ------
  
On a terminal `cd` into the `"main"` folder of the Vibe and enter the following command
```
$ g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o <Name of the object file>  ViBe_colour.cpp -lopencv_highgui -lvibe++ -lopencv_core -lopencv_videoio -lopencv_imgproc
```
Execution
----
After the object file is created after compilation, enter the following command
```
 $ ./<name_of_object_file> <argument containg the name of the Video and its path>
```
Note: if the Video is in the same folder then we dont need to input the path, just the name of the video is enough.






  > *ViBe is not our implementation its a copyright under the University of Leige, Belgium. This is a research project and the libraries are solely used for Research purposes alone.
