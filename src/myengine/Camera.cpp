#include "Camera.h"
#include "Entity.h"
#include "Core.h"


Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));

	// This represents the camera's orientation and position
	_viewMatrix = glm::translate(glm::mat4(1.0f), cameraPos);

	// Set up a projection matrix
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
	m_fb = std::shared_ptr<FrameBuffer>(new FrameBuffer());
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	
	_viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return _viewMatrix;
}

glm::mat4 Camera::GetProjMatrix()
{
	int x, y;
	SDL_GetWindowSize(GetCore()->GetWindow(), &x, &y);
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)x / (float)y, 0.1f, 100.0f);
	return _projMatrix;
}

void Camera::OnTick()
{
	m_fb->Update(GetCore()->GetScreenSize().x, GetCore()->GetScreenSize().y);
	std::shared_ptr<Keyboard> m_keyboard = GetKeyboard();

	if (m_keyboard->Input(RLEFT_BUTTON))
	{
		yaw -= 0.5f;
		//	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
			//_cameraAngleY -= 0.05f;
	}
	if (m_keyboard->Input(RRIGHT_BUTTON))
	{
		yaw += 0.5f;
		//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
			//_cameraAngleY += 0.05f;
	}
	if (m_keyboard->Input(RDOWN_BUTTON))
	{
		pitch -= 0.5f;
		//	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
		//_cameraAngleY -= 0.05f;
	}
	if (m_keyboard->Input(RUP_BUTTON))
	{
		pitch += 0.5f;
		//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.05f;
		//_cameraAngleY += 0.05f;
	}
	if (m_keyboard->Input(UP_BUTTON))
	{
		cameraPos += 0.05f * cameraFront;
		//_cameraPosition -= glm::vec3(0.5f *_cameraPosition.x * _cameraAngleX, 0.5f  *_cameraPosition.y * _cameraAngleY, -0.05);
	}
	if (m_keyboard->Input(DOWN_BUTTON))
	{
		cameraPos -= 0.05f * cameraFront;
		//_cameraPosition += glm::vec3(0.5f  *_cameraPosition.x * _cameraAngleX, 0.5f  *_cameraPosition.y * _cameraAngleY, 0.05);
	}
	if (m_keyboard->Input(RIGHT_BUTTON))
	{
		cameraPos += 0.05f * cameraRight;
		//_cameraPosition -= glm::vec3(0.5f *_cameraPosition.x * _cameraAngleX, 0.5f  *_cameraPosition.y * _cameraAngleY, -0.05);
	}
	if (m_keyboard->Input(LEFT_BUTTON))
	{
		cameraPos += 0.05f * -cameraRight;
		//_cameraPosition -= glm::vec3(0.5f *_cameraPosition.x * _cameraAngleX, 0.5f  *_cameraPosition.y * _cameraAngleY, -0.05);
	}

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	cameraRight = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUp = glm::normalize(glm::cross(cameraRight, front));

}
