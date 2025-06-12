#include "GLCamera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/geometric.hpp>

namespace IGL {

GLCamera::GLCamera(glm::vec3 _position,
         glm::vec3 _direction,
         glm::vec3 _up
) {
    position = _position;
    direction = _direction;
    up = _up;
}

void GLCamera::setTarget(glm::vec3 target) {
    direction = glm::normalize(target - position);
}

void GLCamera::updateVectors() {
    direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    direction.y = std::sin(glm::radians(pitch));
    direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    direction = glm::normalize(direction);
    right = glm::normalize(glm::cross(direction, worldUp));
    up = glm::normalize(glm::cross(right, direction));
}
    
glm::mat4 GLCamera::getViewMat() {
    return glm::lookAt(position, position + direction, up);
}

} // namespace IGL
