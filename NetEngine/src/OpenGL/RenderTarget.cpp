
#include "RenderTarget.h"
#include <iostream>

void TextureAttachment::CreateAttachment()
{
	glGenTextures(1, &attachment);
}

void TextureAttachment::Bind()
{
	glBindTexture(GL_TEXTURE_2D, attachment);
}

void TextureAttachment::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderBuffer::CreateBufferObject()
{
	glGenRenderbuffers(1, &bufferObject);
}

void RenderBuffer::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, bufferObject);
}

void RenderBuffer::Unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderTarget::CreateRenderTarget()
{
	glGenFramebuffers(1, &currentFBTarget);
	glBindFramebuffer(GL_FRAMEBUFFER, currentFBTarget);
}

void RenderTarget::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, currentFBTarget);
}

void RenderTarget::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::AttachTextureAttachment(TextureAttachment& attachment)
{
	glBindTexture(GL_TEXTURE_2D, attachment.attachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, attachment.attachment, 0);
}

void RenderTarget::AttachRenderBuffer(RenderBuffer& bufferObject)
{
	glBindRenderbuffer(GL_RENDERBUFFER, bufferObject.bufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, bufferObject.bufferObject); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}