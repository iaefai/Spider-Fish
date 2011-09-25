Spider Fish
===========

Note: This is a test tree independent of the main source from
Salbris

Changelog
---------

25 Sep 11   *jeff*

    * Added Shader demo from SFML to test cross platform.
    * Works on the Mac
    * Uses [SFML](http://www.sfml-dev.org/)
      
26 Sep 11	*jeff*

    * Compiles on Windows

Installing
----------

Requires SFML

Always use a different build directory from the source to keep it clean.

Mac:

    * Install CMake
    * Build SFML, shared libraries, and install to default location
    * Run CMake, make on this.
    * Spider-Fish.app will be generated, and will work on the build machine
    
Windows: ~ will be assumed to be your user directory.

    1. Install CMake and Git using the official packages for windows, ensuring that commands are put in the local path.
	2. Open a Visual Studio 2010 64 bit command prompt, preferably in administrator mode for installations.
	2. md ~\source 
	3. cd ~\source
	4. git clone https://github.com/LaurentGomila/SFML.git
	5. mkdir build-SFML
	6. cd build-SFML
	7. cmake -G "NMake Makefiles" ../SFML
	8. nmake
	9. nmake install

Now SFML is installed, administrator mode is not need (and only was needed for step 9)

    10. cd ..
	11. git clone git://github.com/iaefai/Spider-Fish.git
	12. mkdir build-Spider-Fish
	13. cd build-Spider-Fish
	14. cmake -G "Visual Studio 10 Win64" -D SFMLDIR:String="C:\Program Files\SFML" ..\Spider-Fish

A Visual Studio sln file has been created. Note that if you built a 32 bit version you must change C:\Program Files to the x86 name.

    15. start Spider-Fish.sln
	16. Change the start up project to Spider-Fish.
	17. Change the path in resources.cpp to be appropriate to you (should just change your username)
	17. Run project.
	
At this point it should work, but it presently has a bug about loading images.

The reason for the separate build folders is so it does not pollute the source directory. 

If anyone can figure out the problem with the loading of the images, I would love to hear it.