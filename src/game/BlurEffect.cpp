#include "BlurEffect.h"
#include "myengine/Entity.h"
#include <fstream>
#include <iostream>

void BlurEffect::OnInit()
{
	m_pp = std::shared_ptr<PostProcess>(new PostProcess());
	m_pp->LoadShader(GetCore(), "Blur", "compVert.txt", "blurFrag.txt");
	m_pp->AddEffect("in_Projection");
	m_pp->AddEffect("in_Model");
	m_pp->AddEffect("in_Texture");
	m_pp->AddEffect("in_Screen");
	m_cam = GetEntity()->GetComponent<Camera>();
}

void BlurEffect::OnTick()
{
	m_pp->GetFB()->Update(GetCore()->GetScreenSize().x, GetCore()->GetScreenSize().y);

	if (GetCore()->GetKeyboard()->PressOnce(Y_BUTTON))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_pp->GetFB()->GetBuffer());
		std::cout << std::endl << "PP SCREENSHOT" << std::endl;
		screenshot("testPP.tga", GetCore()->GetScreenSize().x, GetCore()->GetScreenSize().y);
	}
	if (GetCore()->GetKeyboard()->PressOnce(X_BUTTON))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_cam->GetFrameBuffer()->GetBuffer());
		std::cout << std::endl << "OG CAMERA SCREENSHOT" << std::endl;
		screenshot("testC.tga", GetCore()->GetScreenSize().x, GetCore()->GetScreenSize().y);
	}
}

void BlurEffect::OnPostProcess()
{
	m_pp->SetEffect("in_Projection", GetCore()->GetPM());
	glm::mat4 modelmat = glm::mat4(1.0f);
	modelmat = glm::translate(modelmat, glm::vec3(-1, -1, 0));
	modelmat = glm::scale(modelmat, glm::vec3(2, 2, 1));
	m_pp->SetEffect("in_Model", modelmat);

	m_pp->SetEffect("in_Screen", GetCore()->GetScreenSize());

	m_pp->Draw(m_cam->GetTexture());

	//m_cam->SetTexture(m_pp->GetTexture());
	
}

void BlurEffect::OnGui()
{
	GetCore()->GetGui()->SetTexture(m_pp->GetTexture());
	GetCore()->GetGui()->Sprite(glm::vec4(-1,-1,2,2));
}

void BlurEffect::screenshot(char filename[160], int x, int y)
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
