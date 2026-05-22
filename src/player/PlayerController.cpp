#include "PlayerController.h"

#include "../platform/input/Input.h"

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

void PlayerController::update(Camera &camera,
                              TransformComponent &transform,
                              RigidbodyComponent &rigidbody,
                              bool &cursorLocked,
                              SDL_Window *window) {

  /*
    CURSOR TOGGLE
*/

  if (Input::escapePressed) {
    cursorLocked = !cursorLocked;

    SDL_SetWindowRelativeMouseMode(window, cursorLocked);
  }
  /*
      CAMERA
  */

  if (cursorLocked) {
    camera.yaw += Input::mouseX * 0.1f;

    camera.pitch -= Input::mouseY * 0.1f;

    camera.pitch = glm::clamp(camera.pitch, -89.0f, 89.0f);

    camera.updateVectors();
  }

  /*
      MOVEMENT
  */

  glm::vec3 right = glm::normalize(glm::cross(camera.front, camera.up));

  glm::vec3 flatFront =
      glm::normalize(glm::vec3(camera.front.x, 0.0f, camera.front.z));

  glm::vec3 moveDir(0.0f);

  if (Input::w)
    moveDir += flatFront;

  if (Input::s)
    moveDir -= flatFront;

  if (Input::a)
    moveDir -= right;

  if (Input::d)
    moveDir += right;

  if (glm::length(moveDir) > 0.0f) {
    moveDir = glm::normalize(moveDir);

    rigidbody.velocity.x = moveDir.x * 5.0f;

    rigidbody.velocity.z = moveDir.z * 5.0f;
  } else {
    rigidbody.velocity.x = 0.0f;

    rigidbody.velocity.z = 0.0f;
  }

  /*
      JUMP
  */

  if (Input::space && rigidbody.grounded) {
    rigidbody.velocity.y = rigidbody.jumpForce;
  }

  /*
      CAMERA FOLLOW
  */

  camera.position = transform.position + glm::vec3(0.0f, 1.7f, 0.0f);
}