# Logistic map

This directory creates a high resolution image of the logistic map bifurcation diagram for 3.5 < r < 4.0.

### gen\_data.cpp

Compile with your chosen c++ compiler and run to generate a file with all the data. The format is 1 r value per line, with the r value followed by space seperated x values.

### gen\_image.py

This uses matplot lib to generate a histogram to make the diagram. It will be outputted as a png.
