#pragma once

#include "../vendor/stb_image/stb_image.h"

#include <string>
#include <vector>

class Texture
{
public:
	Texture();
	Texture(const std::string& texturePath);
	
	~Texture();

	void Bind(unsigned int slot=0) const;
	void UnBind() const;

private:
	unsigned int m_RenderID;
	std::string m_FilePath;

	int m_Width;
	int m_Height;
	int m_BPP;
	unsigned char* m_LocalBuffer;
};