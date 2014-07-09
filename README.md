MCPhoton
=============

MCPhoton can currently be used to model the attenuation of a 1 MeV photon beam 
through a iron shield 10 mfp thick. It can either linearly or logrithmicly 
interpolate cross section data. It also has three options for modelling 
inchorrent photon scattering: 1. Using a constant rejection function 2. Using a 
linear rejection function or 3. Using Kahn's two path method. 
 
This shows how to download and build MCPhoton with the desired data interpolator
and polar angle rejection technique. 

1) DOWNLOAD

a) In the desired directory enter the following into the command line:

```
$ git clone https://github.com/lkersting/MCPhoton.git
```

2) UPDATE ROOT DIRECTORY

a) Enter the MCPhoton src directory and open the CMakeLists.txt

```
$ cd MCPhoton/src
$ gedit CMakeLists.txt
```

b) At the top of the file change DIRECTORY to the directory in which 
MCPhoton was download. For example: the path to my copy of MCPhoton is 
"/home/lujoke/Documents/CPP/MCPhoton" so the first 4 lines look as follows

```
SET(DIRECTORY
  ${DIRECTORY}
  /home/lujoke/Documents/CPP
) 
```

2) COMPILE

a) Return to the MCPhoton directory and enter the following:

```
$ mkdir build
$ cd build
$ cmake ..
```

b) Choose the desired data interpolator and polar angle rejection technique:
[rejtech] constant, linear, or twopath
[interpolator] lin or log

```
$ make [rejtech]_[interpolator]
```

So if you want to use a linear rejection technique and linearly interpolate 
cross section data you would enter:

```
$ make linear_lin
```

3) RUN PROGRAM

a) From build run the exacutable (located in build/src)

```
$ ./src/MCPhoton
```

b) Follow the onscreen command to enter the # of photons to be modeled.
NOTE: the number cannot be in entered in shorthand.  
ie: 10000 (correct)   
	1E4   (Incorrect)

After the program has finished running it will print out how many photons exited
forward through the back of the shield, backward through the front of the 
shield, and how many were absorbed.
If any photons exited forward through the back of the shield it will display a 
histogram of their final energies and the scalar flux.
Finally, the total time it took the program to run will also be displayed.
