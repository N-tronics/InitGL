# An initializer lib for GLFW, GLAD, OpenGL development in C++

## Usage
To use InitGL in your project, clone the repo into your project directory
In your project CMakeLists.txt file, add 
```
add_subdirectory(<path to InitGL repo>)
```
Then, when linking libraries, add ```InitGL```

All headers files can be included with
```
#include <IGL/<IGL header file>.hpp
```

GLFW, GLAD, GLM, and stb_image libraries can be used as is.
```
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>
```
