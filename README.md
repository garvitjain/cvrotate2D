cvrotate2D
==========

The library **cvrotate2D** is an OpenCV library for rotating a matrix without cropping.

![Overview of cvrotate2D](https://raw.github.com/milq/cvrotate2D/master/overview.png "Overview of cvrotate2D")

How to use
----------

<i>void rotate2D(InputArray <b>src</b>, OutputArray **dst**, double <b>degrees</b>)</i>

Example
-------

Compile the test with the following command:

```
g++ test.cpp cvrotate2D.cpp -lopencv_core -lopencv_highgui -lopencv_imgproc
```

And then execute ```./a.out``` to obtain the file *rotated.png* with the image rotated.

Example 2 (compiling the library)
---------------------------------

Compile the library:

```
g++ -O3 -Wall -shared -fpic -o libcvrotate2D.so cvrotate2D.cpp
```

Compile the test using the compiled library *cvrotate2D*:

```
g++ test.cpp -lopencv_core -lopencv_highgui -lopencv_imgproc -lcvrotate2D -I./ -L./
```

Finally, execute ```./a.out``` to obtain the file *rotated.png* with the image rotated.
