Compiling QCustomPlot as shared library:
  - Make sure the amalgamated QCustomPlot source files (qcustomplot.h/.cpp) are in the directory above sharedlib (two directories above the .pro files).
  - Run qmake; make; in the sharedlib-compilation directory. This will create two library versions: "qcustomplot" for release mode and "qcustomplotd" for debug mode.
    For example, on Unix this will create libqcustomplot.so and libqcustomplotd.so and some softlink files to those shared library files.
    On MS Windows it will create corresponding .dll files.
    
Compiling an application that uses the shared library:
  - Copy all created library/softlink files from the previous step to the sharedlib-usage directory
  - run qmake; make; in the sharedlib-usage directory. This will build the application.
  
Running the application:
  - Make sure the application executable can find the shared library files:
    On MS Windows it is sufficient to have the library .dll files in the same directory as the executable.
    On Unix you have at least two options: You can specify the current directory in the LD_LIBRARY_PATH variable (call in
    terminal: "export LD_LIBRARY_PATH=." before launching the application from the same terminal session). This is useful
    for testing if it works. The other option is to install the library files to one of the default locations for shared
    objects: /usr/local/lib or /usr/lib for example.
  - On MS Windows, copy any additional needed Qt shared libraries:
    The deployment tool windeployqt.exe (e.g in C:\Qt\6.0.2\mingw81_64\bin\) will help with copying those files, when called
    with the "sharedlib-usage.exe" as parameter.
    In addition, the libraries Qt6PrintSupport.dll, libgcc_s_seh-1.dll, libstdc++-6.dll, and libwinpthread-1.dll are usually
    needed, and can be found in your Qt bin directory, e.g. C:\Qt\6.0.2\mingw81_64\bin\.
    More details can be found here: https://doc.qt.io/qt-6/windows-deployment.html
  - Launch the application.
