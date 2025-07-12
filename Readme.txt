DreamStone is a game in which the goal is to collect characters and to progress in a world full of mysteries.

Here is the first version of the game. There are some bugs but it is not likely that you will discover many of them.

To compile the program into the game correctly, you first have to install a C++ compilator and the SFML library (library for C++ visual programming) :
-The C++ compilator I am using is GCC 64 bits, version 12.3.0 or 13.2.0 (use for example this link : https://www.equation.com/servlet/equation.cmd?fa=fortran)
-I am using SFML version 2.5.1 for C++ (https://www.sfml-dev.org/fr/download/sfml/). This version can be found by clicking the "Anciennes versions" button.

-When this is done, you will have to add the paths of the folders "gcc\bin" and "SFML-2.5.1\bin" in the system variable "PATH".

-Then you have to open the file "PlatformProject/Makefile" with a text editor, and modify the paths of the variables CXXFLAGS and LDFLAGS. Replace -I"path1" to -I"pathToSFML\SFML-2.5.1\include" and -L"path2" to -L"pathToSFML\SFML-2.5.1\lib"

-Then, open a cmd, go to the directory PlatformProject, and run the command : make (or exe)

-Finally, an executable "PlatformGame" should be created at the root directory. You just have to run the executable file.

If you already have the executable, then you do not need to install a C++ compilator nor SFML. You only need the executable, the Game.txt file, and the folders libs, res and data.

Enjoy the beta version !
