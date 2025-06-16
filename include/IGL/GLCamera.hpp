#pragma once

#include <glm/glm.hpp>

namespace IGL {

class GLCamera {
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right;
    float pitch = 0.0f, roll = 0.0f, yaw = 0.0f;
    
    GLCamera(glm::vec3 _position,
             glm::vec3 _direction = glm::vec3(0.0f, 0.0f, -1.0f),
             glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f)
    );
    
    void setTarget(glm::vec3 target);
    void updateVectors();
    glm::mat4 getViewMat();
};

} // namespace IGL
