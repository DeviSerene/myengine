#include "Texture.h"

std::shared_ptr<Texture> Texture::Load(std::string _path)
{
	std::shared_ptr<Texture> rtn = std::shared_ptr<Texture>(new Texture());
	rtn->LoadTexture(_path);
	rtn->m_path = _path;
	rtn->m_timer = 0;
	return rtn;
}

void Texture::LoadTexture(std::string filename)
{
	// Load SDL surface
	SDL_Surface *image = SDL_LoadBMP(filename.c_str());

	if (!image) // Check it worked
	{
		//std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;
		return;
	}

	// Create OpenGL texture
	unsigned int texName = 0;
	glGenTextures(1, &texName);


	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// By default, OpenGL mag filter is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// By default, OpenGL min filter will use mipmaps
	// We therefore either need to tell it to use linear or generate a mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// SDL loads images in BGR order
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	//glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(image);

	//glBindTexture(GL_TEXTURE_2D, 0);


	m_texture = texName;
}