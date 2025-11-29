gcc program.c -o calculator.exe ^
-I"C:\msys64\mingw64\include\gtk-3.0" ^
-I"C:\msys64\mingw64\include\cairo" ^
-L"C:\msys64\mingw64\lib" ^
-lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0
pause
