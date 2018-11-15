#include "TextTexture.h"
#include <iostream>

std::shared_ptr<TextTexture> TextTexture::Create()
{
	std::shared_ptr<TextTexture> rtn = std::shared_ptr<TextTexture>(new TextTexture());
	rtn->m_timer = 0;
	return rtn;
}

std::shared_ptr<TextTexture> TextTexture::Load(std::string _path)
{
	std::shared_ptr<TextTexture> rtn = std::shared_ptr<TextTexture>(new TextTexture());
	rtn->m_path = _path;
	rtn->m_timer = 0;
	return rtn;
}

void TextTexture::SetText(SDL_Color _colour, int _textsize)
{
	
	_TTF_Font* font = TTF_OpenFont("Verdana.ttf", _textsize); //font and fontsize
	SDL_Surface* surfaceText = TTF_RenderUTF8_Blended(font, m_path.c_str(), _colour);
	
	
	//m_texture = SDL_CreateTextureFromSurface(_renderer, surfaceText); //convert the surface into a texture
	if (!surfaceText) // Check it worked
	{
		std::cout << "Error: " << SDL_GetError() << std::endl;
		//std::cerr << "WARNING: could not load BMP image: " << filename << std::endl;
		return;
	}

	unsigned int texName = 0;
	glGenTextures(1, &texName);


	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// By default, OpenGL mag filter is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// By default, OpenGL min filter will use mipmaps
	// We therefore either need to tell it to use linear or generate a mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//
	GLint colors = surfaceText->format->BytesPerPixel;
	GLint texture_format;
	if (colors == 4) {   // alpha
		if (surfaceText->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	}
	else {             // no alpha
		if (surfaceText->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	}
	//
	glTexImage2D(GL_TEXTURE_2D, 0, colors, surfaceText->w, surfaceText->h, 0, texture_format, GL_UNSIGNED_BYTE, surfaceText->pixels);

	//glGenerateMipmap(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);

	m_texture = texName;

	SDL_FreeSurface(surfaceText); //free the surface
	surfaceText = nullptr;

	TTF_SetFontOutline(font, 0);

	TTF_CloseFont(font);
	font = nullptr;

}