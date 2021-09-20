# RayTracer
My ray tracer includes four files that can be compiled and run. 

## Render
The primary program is ```render.cpp```. This program renders my demo scene using an orthographic or perspective camera. The camera type can be toggled by pressing the 'p' key on your keyboard. Use the following command to compile this program on Mac:
```
g++ -lglfw -lglew -framework OpenGL render.cpp RayTracer.cpp -o render.out
```
I do not own a Windows or Linux machine, but I believe the following command can be used for compilation on those platforms:
```
g++ -lglfw -lglew render.cpp RayTracer.cpp -o render.out
```
Once compiled, the program can be run using the following command: ```./render.out```

## Movie
I also have three programs that render each frame of a movie and save the image to a corresponding folder. I have already generated the images of each movie, and created the corresponding MP4 files. However, if you would like to modify the movie and/or render each frame of a movie again, the following instructions can be used for compilation. Note that each movie automatically writes each created image to a corresponding folder, so these folders must exist in the project directory before running any of the following programs.

### Movie 1
The first movie is a scan over my demo scene. On Mac this program can be compiled using the following command:
```
g++ -lglfw -lglew -framework OpenGL movie1.cpp RayTracer.cpp -o movie1.out
```
On Windows or Linux:
```
g++ -lglfw -lglew movie1.cpp RayTracer.cpp -o movie1.out
```
Finally, to run the program use the following command: ```./movie1.out```

Image files will be written to the folder ```movie1```.

### Movie 2
The second movie rotates the camera's position around the scene, while focusing on the scene's origin. On Mac this program can be compiled using the following command:
```
g++ -lglfw -lglew -framework OpenGL movie2.cpp RayTracer.cpp -o movie2.out
```
On Windows or Linux:
```
g++ -lglfw -lglew movie2.cpp RayTracer.cpp -o movie2.out
```
Finally, to run the program use the following command: ```./movie2.out```

Image files will be written to the folder ```movie2```.

### Movie 3
The third movie depicts a star setting on a planet's horizon with no atmosphere. On Mac this program can be compiled using the following command:
```
g++ -lglfw -lglew -framework OpenGL movie3.cpp RayTracer.cpp -o movie3.out
```
On Windows or Linux:
```
g++ -lglfw -lglew movie3.cpp RayTracer.cpp -o movie3.out
```
Finally, to run the program use the following command: ```./movie3.out```

Image files will be written to the folder ```movie3```.
