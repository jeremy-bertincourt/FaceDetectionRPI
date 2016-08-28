# FaceDetectionRPI

Subject of the project:
This is an eye and face detector for a video stream on the Raspberry PI

How it works:
This program uses the embedded Raspberry PI camera to process a video stream. It searches for faces and for each face, it draws a rectangle and searches for eyes. Finally it draws a circle for each eye.
As the stream processing is laggy on the Raspberry PI, only a sixth of searching iterations look for eyes and faces.

Note on compilation:
It does not provide cross-compilation. Thus this should be compiled directly on the Raspberry PI.
If an error occurs about libraries that cannot be found, be sure to export LD_LIBRARY_PATH with /usr/local/lib/ 
as all the system libraries should be in this repository on the RPI.

Intallation:
To compile the code, create a build directory and launch build_project.sh.
This will create the application executable in install/bin/
