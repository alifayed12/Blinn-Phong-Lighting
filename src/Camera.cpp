#include "Camera.hpp"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

bool flag = false;

Camera::Camera(int windowWidth, int windowHeight, const glm::vec3& position)
	: m_Position(position), m_WindowWidth(windowWidth), m_WindowHeight(windowHeight)
{
	m_Target = glm::vec3(0.0f, 0.0f, 1.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_Speed = 0.02f;

	m_AngleHorizontal = -90.0f;
	m_AngleVertical = 0.0f;

	m_MousePosX = windowWidth / 2;
	m_MousePosY = windowHeight / 2;
}

Camera::~Camera()
{

}

void Camera::ProcessKeyboardInputs(GLFWwindow* window)
{
	/* Movements are inverted so everything in the scene moves the opposite direction */
	/* This simulates a camera */
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position -= m_Speed * glm::normalize(glm::vec3(m_Target.x, 0.0f, m_Target.z));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += m_Speed * glm::normalize(glm::vec3(m_Target.x, 0.0f, m_Target.z));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 leftVec = glm::normalize(glm::cross(m_Target, m_Up));
		m_Position += m_Speed * leftVec;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 rightVec = glm::normalize(glm::cross(m_Up, m_Target));
		m_Position += m_Speed * rightVec;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += m_Speed * glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Position -= m_Speed * glm::vec3(0.0f, 1.0f, 0.0f);
	}
}

void Camera::ProcessMouseMovements(GLFWwindow* window)
{
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	double deltaXPos = xPos - m_MousePosX;
	double deltaYPos = yPos - m_MousePosY;

	if (deltaXPos == 0 && deltaYPos == 0)
	{
		return;
	}

	m_MousePosX = xPos;
	m_MousePosY = yPos;

	/* Subtracting because we want the world to be rotated in the opposite direction */
	m_AngleHorizontal -= (float)deltaXPos / 20.0f;
	m_AngleVertical -= (float)deltaYPos / 20.0f;

	if (m_AngleVertical >= 89.0f)
	{
		m_AngleVertical = 89.0f;
	}
	if (m_AngleVertical <= -89.0f)
	{
		m_AngleVertical = -89.0f;
	}

	UpdateCameraUVN();
}

glm::mat4 Camera::CreateCameraMatrix()
{
	glm::vec3 nAxis = m_Target;
	glm::normalize(nAxis);

	glm::vec3 uAxis = glm::cross(m_Up, nAxis);
	glm::normalize(uAxis);

	glm::vec3 vAxis = glm::cross(nAxis, uAxis);

	float viewArray[] =
	{
		uAxis.x, uAxis.y, uAxis.z, 0.0f,
		vAxis.x, vAxis.y, vAxis.z, 0.0f,
		nAxis.x, nAxis.y, nAxis.z, 0.0f,
		0.0f,    0.0f,	  0.0f,    1.0f
	};

	glm::mat4 view = glm::transpose(glm::make_mat4(viewArray));
	view = glm::translate(view, -m_Position);

	return view;
}

void Camera::RotateVector(float angle, const glm::vec3& axis, glm::vec3& rotationVec)
{
	glm::quat q = glm::angleAxis(glm::radians(angle), axis);;
	glm::quat qPrime = glm::conjugate(q);
	glm::quat w = q * glm::quat(0.0f, rotationVec.x, rotationVec.y, rotationVec.z) * qPrime;

	rotationVec.x = w.x;
	rotationVec.y = w.y;
	rotationVec.z = w.z;
}

void Camera::UpdateCameraUVN()
{
	glm::vec3 yAxis(0.0f, 1.0f, 0.0f);

	glm::vec3 view(1.0f, 0.0f, 0.0f);
	RotateVector(m_AngleHorizontal, yAxis, view);
	glm::normalize(view);

	glm::vec3 u = glm::cross(yAxis, view);
	glm::normalize(u);
	RotateVector(m_AngleVertical, u, view);

	m_Target = view;
	glm::normalize(m_Target);

	m_Up = glm::cross(m_Target, u);
	glm::normalize(m_Up);
}

glm::mat4 Camera::GetViewMatrix()
{
	return CreateCameraMatrix();
}

void Camera::PrintPosition() const
{
	std::cout << "X: " << m_Position.x << " Y: " << m_Position.y << " Z: " << m_Position.z << std::endl;
}