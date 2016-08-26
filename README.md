# FaceDetectionRPI
This is an eye and face detector for a video stream on the Raspberry PI

It does not provide cross-compilation. Thus this should be compiled directly on the Raspberry PI.

If an error occurs about libraries that cannot be found, be sure to export LD_LIBRARY_PATH with /usr/local/lib/ 
as all the system libraries should be in this repository on the RPI.

To compile the code, create a build directory and launch build_project.sh.
This will create the application executable in install/bin/
