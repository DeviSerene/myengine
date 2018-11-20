#include "Texture.h"

std::shared_ptr<Texture> Texture::Create()
{
	std::shared_ptr<Texture> rtn = std::shared_ptr<Texture>(new Texture());
	rtn->m_timer = 0;
	return rtn;
}

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
	std::string type = filename.substr(filename.length() - 3);
	// Load SDL surface
	//SDL_Surface *image = SDL_LoadBMP(filename.c_str());
	SDL_Surface *image = IMG_Load(filename.c_str());


	if (!image) // Check it worked
	{
		//std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;
		return;
	}
	m_height = image->h;
	m_width = image->w;

	// Create OpenGL texture
	m_texture = 0;
	glGenTextures(1, &m_texture);


	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// By default, OpenGL mag filter is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// By default, OpenGL min filter will use mipmaps
	// We therefore either need to tell it to use linear or generate a mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// SDL loads images in BGR order
	if(type == "bmp")
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(image);

	//glBindTexture(GL_TEXTURE_2D, 0);


	m_texture;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}