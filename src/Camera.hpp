#pragma once

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

class Camera
{
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Target;
		glm::vec3 m_Up;

		int m_WindowWidth;
		int m_WindowHeight;
		
		float m_Speed;

		float m_AngleHorizontal;
		float m_AngleVertical;

		float m_MousePosX;
		float m_MousePosY;

		glm::mat4 CreateCameraMatrix();
		void RotateVector(float angle, const glm::vec3& axis, glm::vec3& rotationVec);
		void UpdateCameraUVN();
	public:
		Camera(int windowWidth, int windowHeight, const glm::vec3& position);
		~Camera();

		void ProcessKeyboardInputs(GLFWwindow* window);
		void ProcessMouseMovements(GLFWwindow* window);

		glm::mat4 GetViewMatrix();

		void PrintPosition() const;

		inline glm::vec3 GetPosition() const { return m_Position; }
};

