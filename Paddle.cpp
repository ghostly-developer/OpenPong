
#include "Paddle.h"

Paddle::Paddle(glm::vec3 position, glm::vec3 scale, CONTROLTYPE type, glm::vec3 velocity) {
	this->position = glm::vec3(position);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(scale);
	this->type = type;
	this->velocity = glm::vec3(velocity);
} 


void Paddle::update(Game* g, GLFWwindow* window) {
	if (type == WASD) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (position.y >= 0.73f) {
				position.y += 0.0f;
			}
			if (position.y < 0.73f) {
				position.y += 0.01f;
				velocity.y += 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
			velocity.y = 0.0;

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (position.y <= -0.73f) {
				position.y -= 0.0f;
			}
			if (position.y > -0.73f) {
				position.y -= 0.01f;
				velocity.y -= 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
			velocity.y = 0.0;
		}
	}

	if (type == ARROW) {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			if (position.y >= 0.73f) {
				position.y += 0.0f;
			}
			if (position.y < 0.73f) {
				position.y += 0.01f;
				velocity.y += 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
			velocity.y = 0.0;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			if (position.y <= -0.73f) {
				position.y -= 0.0f;
			}
			if (position.y > -0.73f) {
				position.y -= 0.01f;
				velocity.y -= 0.0001;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
			velocity.y = 0.0;
		}
	}
}

