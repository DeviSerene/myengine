#include "Stats.h"

Stats::Stats(std::shared_ptr<TextTexture> _name, std::shared_ptr<Resources> _resources)
{
	m_resources = _resources;
	m_maxHP = 75;
	m_curHP = 75;
	m_maxMP = 75;
	m_curMP = 25;

	m_str = 50;
	m_mag = 50;

	m_def = 50;
	m_res = 50;

	m_spd = 50;
	m_crit = 50;

	m_name = _name;
	m_name->SetText({ 220,220,220,255 }, 12);
	std::string text;
	text = "HP: " + std::to_string(m_curHP) + "/" + std::to_string(m_maxHP);
	m_hpText = _resources->Load<TextTexture>(text);
	m_hpText->SetText({ 225,225,225,255 }, 10);
	text = "SP: " + std::to_string(m_curMP) + "/" + std::to_string(m_maxMP);
	m_mpText = _resources->Load<TextTexture>(text);
	m_mpText->SetText({ 225,225,225,255 }, 10);

	m_hpBar = _resources->Load<Texture>("assets/hp.png");
	m_mpBar = _resources->Load<Texture>("assets/mp.png");
	m_statusBar = _resources->Load<Texture>("assets/infoBar.png");
	m_bp = _resources->Load<Texture>("assets/mana.png");
	m_bpEmpty = _resources->Load<Texture>("assets/manaEmpty.png");
	m_bpH = _resources->Load<Texture>("assets/manaHighlight.png");
}

void Stats::Draw(float _posY, std::shared_ptr <Gui> _gui, int _bp, int _bpH)
{
	_gui->SetFrameInfo({ 1,1,1,1 });
	//bg
	glm::vec4 pos;
	pos.z = 0.375f;
	pos.w = 0.35f;
	pos.x = 0.60f;
	pos.y = _posY- (pos.w/1.5f);
	_gui->SetTexture(m_statusBar->GetTexture());
	_gui->Sprite(pos);

	//name
	pos.x = 0.65f;
	pos.y = _posY;
	pos.z = 0.005f * m_name->GetWidth(); 
	pos.w = 0.005f * m_name->GetHeight();
	_gui->SetTexture(m_name->GetTexture());
	_gui->Sprite(pos);

	//HP
	pos.y -= 0.075f;
	//the bar
	pos.z = 0.3f * ((float)m_curHP / (float)m_maxHP);
	pos.w = 0.015f;
	_gui->SetTexture(m_hpBar->GetTexture());
	_gui->Sprite(pos);
	//the text
	pos.z = 0.005f * m_hpText->GetWidth();
	pos.w = 0.005f * m_hpText->GetHeight();
	_gui->SetTexture(m_hpText->GetTexture());
	_gui->Sprite(pos);

	//MP
	pos.y -= 0.075f;
	//the bar
	pos.z = 0.3f * ((float)m_curMP / (float)m_maxMP);
	pos.w = 0.015f;
	_gui->SetTexture(m_mpBar->GetTexture());
	_gui->Sprite(pos);
	//the text
	pos.z = 0.005f * m_mpText->GetWidth();
	pos.w = 0.005f * m_mpText->GetHeight();
	_gui->SetTexture(m_mpText->GetTexture());
	_gui->Sprite(pos);

	//BP
	pos.y -= 0.06f;
	for (int i = 1; i < 6; i++)
	{
		pos.z = 0.05f;
		pos.w = 0.05f;
		if (_bp >= i)
		{
			_gui->SetTexture(m_bp->GetTexture());
			_gui->Sprite(pos);
			if (_bpH >= i)
			{
				_gui->SetTexture(m_bpH->GetTexture());
				_gui->Sprite(pos);
			}
		}
		else
		{
			_gui->SetTexture(m_bpEmpty->GetTexture());
			_gui->Sprite(pos);
		}
		pos.x += 0.055f;
	}

}
