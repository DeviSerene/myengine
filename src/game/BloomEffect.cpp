#include "BloomEffect.h"
#include "myengine/Entity.h"
#include <fstream>
#include <iostream>

void BloomEffect::OnInit()
{
	m_cam = GetEntity()->GetComponent<Camera>();

	m_colourInfo = glm::vec3(0, 0, 0.55f);
	m_lightKey = std::shared_ptr<PostProcess>(new PostProcess());
	m_lightKey->LoadShader(GetCore(), "ColourKey", "compVert.txt", "colKeyFrag.txt");
	m_lightKey->AddEffect("in_Texture");
	m_lightKey->AddEffect("in_ColourInfo");

	m_blur = std::shared_ptr<PostProcess>(new PostProcess());
	m_blur->LoadShader(GetCore(), "Blur", "compVert.txt", "blurFrag.txt");
	m_blur->AddEffect("in_Texture");
	m_blur->AddEffect("in_Screen");
	m_blur->AddEffect("in_BlurInfo");

	m_merge = std::shared_ptr<PostProcess>(new PostProcess());
	m_merge->LoadShader(GetCore(), "Merge", "compVert.txt", "mergeFrag.txt");
	m_merge->AddEffect("in_Texture");
	m_merge->AddEffect("in_TextureTwo");

	m_pass = std::shared_ptr<PostProcess>(new PostProcess());
	m_pass->LoadShader(GetCore(), "PassThrough", "compVert.txt", "passFrag.txt");
	m_pass->AddEffect("in_Texture");
}

void BloomEffect::OnTick()
{
	m_lightKey->GetFB()->Update(GetCore()->GetScreenSize().x, GetCore()->GetScreenSize().y);

	if (GetCore()->GetKeyboard()->PressOnce(START_BUTTON))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_pass->GetFB()->GetBuffer());
		std::cout << std::endl << "PP SCREENSHOT" << std::endl;
		screenshot("testBEPa.tga", GetCore()->GetScreenSize().x, GetCore()->GetScreenSize().y);
	}
	if (GetCore()->GetKeyboard()->PressOnce(SELECT_BUTTON))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_blur->GetFB()->GetBuffer());
		std::cout << std::endl << "OG CAMERA SCREENSHOT" << std::endl;
		screenshot("testBEB.tga", GetCore()->GetScreenSize().x, GetCore()->GetScreenSize().y);
	}
}

void BloomEffect::OnPostProcess()
{

	m_lightKey->SetEffect("in_ColourInfo", m_colourInfo);
	m_lightKey->Draw(m_cam->GetTexture());

	m_blur->SetEffect("in_Screen", GetCore()->GetScreenSize());
	m_blur->SetEffect("in_BlurInfo", glm::vec3(0, 0, 0));
	m_blur->Draw(m_lightKey->GetTexture());

	for (int i = 0; i < 6; i++)
	{
		m_pass->Draw(m_blur->GetTexture());
		m_blur->SetEffect("in_Screen", GetCore()->GetScreenSize());
		m_blur->SetEffect("in_BlurInfo", glm::vec3(0, 0, 0));
		m_blur->Draw(m_pass->GetTexture());
	}

	m_merge->SetTexture("in_TextureTwo", m_blur->GetTexture(), 1);
	m_merge->Draw(m_cam->GetTexture());
}

void BloomEffect::OnGui()
{
	GetCore()->GetGui()->SetTexture(m_merge->GetTexture());
	GetCore()->GetGui()->Sprite(glm::vec4(-1,-1,2,2));
}

void BloomEffect::screenshot(char filename[160], int x, int y)
{// get the image data
	long imageSize = x * y * 3;
	unsigned char *data = new unsigned char[imageSize];
	glReadPixels(0, 0, x, y, GL_BGR, GL_UNSIGNED_BYTE, data);// split x and y sizes into bytes
	int xa = x % 256;
	int xb = (x - xa) / 256; int ya = y % 256;
	int yb = (y - ya) / 256;//assemble the header
	unsigned char header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,(char)xa,(char)xb,(char)ya,(char)yb,24,0 };

	// write header and data to file
	std::fstream File(filename, std::ios::out | std::ios::binary);
	File.write(reinterpret_cast<char *>(header), sizeof(char) * 18);
	File.write(reinterpret_cast<char *>(data), sizeof(char)*imageSize);
	File.close();

	delete[] data;
	data = NULL;
}
