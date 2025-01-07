#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Renderer/Mesh.h"

class Cubemap : public Mesh
{
public:

	Cubemap();
	void LoadCubemap();
	void CreateCubemap();
	void DrawCubemap(Shader& skyboxShader);
	void BindCubemap();
	void InitializeFaces();
	void InitializeVertices();
private:
	Mesh* cubemapMesh;
	unsigned int textureID;
	float skyboxVertices[216];
	std::vector<const char*> skyboxFaces;
	unsigned int skyboxVAO, skyboxVBO;
};

