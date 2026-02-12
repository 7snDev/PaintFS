## PaintFS

PaintFS is a minimal paint application written in **C using SDL2**.  
It supports basic drawing and erasing with a circular brush and allows exporting the canvas to a BMP image.

---

## Features

- Draw using the left mouse button  
- Erase using the right mouse button  
- Adjustable circular brush size (mouse wheel)  
- Export canvas to BMP (`Ctrl + S`)  
- Lightweight and minimal design  

---

## Controls

| Action | Input |
|---|---|
| Draw | Left mouse button |
| Erase | Right mouse button |
| Change brush size | Mouse wheel |
| Export image | Ctrl + S |

Exported images are saved in the same directory as the executable.

---

## Screenshots

![Drawing](Screenshots/Drawing.BMP)

---

## Build

### Requirements
- GCC  
- SDL2 development libraries  

### Compile
~~~
make build
~~~

### Run
~~~
./PaintFS
~~~

### Clean build files
~~~
make clean
~~~

---

## Project Status

Current limitations and planned improvements:

- GPU-accelerated rendering (SDL renderer instead of surface rendering)  
- Undo / redo system  
- Improved exporting workflow  
- Multiple colors and better brush control  

---

## License

![MIT License](LICENSE)
