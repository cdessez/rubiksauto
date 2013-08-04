--- Abstract ---

This academic project aims at implementing a software that provides a easy and intuitive way to capture the configuration of a RubiksCube (which can then be used for example by a solver).
The user just needs to show successively to their webcam the 6 faces of the cube, which are detected and analyzed by an algorithm of computer vision.
The face faces have to be shown in a predefined order.


--- Overview of the algorithm ---

The algorithm relies on the extraction of the colors of the 9 facets. Those colors being sufficiently distinguishable, its first step consists in extracting for each color the zones of the image that are the closest to it.
Then for each color, it selects the blobs formed by the facets. This is done by two successive selections. First, it considers each connected component independantly to keep only those that have good geometrical properties. Second, it considers each tuple of three remaining blobs and analyses their alignment and spacing, which is a way to keep only the nine ones that correspond to the facets, and to characterize them.
The next step consists in, given those 9 blobs and their properties, associating each one of them to a case in the 3X3 matrix that represents the face.
At this stage, we have a way to process independantly each image sent by the webcam and to determine if it contains a face of the RubiksCube. Thus we just have to detect the stability of the configuration to know when we can store this state so that the user can show the next face.


--- Languages ---

This project was implemented in C++ with the library OpenCV.
