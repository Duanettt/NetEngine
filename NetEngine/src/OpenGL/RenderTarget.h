#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct TextureAttachment
{
	unsigned int attachment;

	void CreateAttachment();

	void Bind();

	void Unbind();
	
};

struct RenderBuffer
{
	unsigned int bufferObject;

	void CreateBufferObject();

	void Bind();

	void Unbind();
};

class RenderTarget
{
public:

	void CreateRenderTarget();
	void Bind();
	void Unbind();

	void AttachTextureAttachment(TextureAttachment& attachment);
	void AttachRenderBuffer(RenderBuffer& bufferObject);

private:
	unsigned int currentFBTarget;
};

