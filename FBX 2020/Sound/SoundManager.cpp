#include "SoundManager.h"

SoundManager* SoundManager::p_instance = 0;

SoundManager* SoundManager::Instance()
{
	if (p_instance == 0)
	{
		p_instance = new SoundManager;
	}

	return p_instance;
}

void SoundManager::RegisterTitleSound()
{
	m_bgm_file = "Res/wav/TitleBgm.wav";
	m_se1_file = "Res/Wav/SelectSE.wav";
	m_click_se_file = "Res/wav/ClickSE.wav";
	m_pAudio->Load(m_bgm, m_bgm_file);
	//m_pAudio->Load(m_select1_se, m_se1_file);
	m_pAudio->Load(m_click_se, m_click_se_file);
}

void SoundManager::RegisterSelectSound()
{
	m_bgm_file = "Res/Wav/SelectBgm.wav";
	m_se1_file = "Res/Wav/SelectSE.wav";
	m_se2_file = "Res/Wav/SelectSE.wav";
	m_se3_file = "Res/Wav/SelectSE.wav";

	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_select1_se, m_se1_file);
	m_pAudio->Load(m_select2_se, m_se2_file);
	m_pAudio->Load(m_select3_se, m_se3_file);
}

void SoundManager::RegisterGameMainSound()
{
	m_bgm_file = "Res/Wav/forestBGM1.wav";
	m_bullet1_se_file = "Res/Wav/Trp1.wav";
	m_bullet2_se_file = "Res/Wav/Trp2.wav";
	m_bullet3_se_file = "Res/Wav/Trp3.wav";

	m_pAudio->Load(m_bgm, m_bgm_file);
	m_pAudio->Load(m_bullet1_se, m_bullet1_se_file);
	m_pAudio->Load(m_bullet2_se, m_bullet2_se_file);
	m_pAudio->Load(m_bullet3_se, m_bullet3_se_file);

}

void SoundManager::RegisterEndSound()
{
}


void SoundManager::SoundBGM()
{
	m_pAudio->Play(m_bgm, -500, true);
}

void SoundManager::SoundSelectBGM()
{
	m_pAudio->Play(m_bgm, 0, true);
}

void SoundManager::SoundSelectSE()
{
	if (m_select1_flag == false)
	{
		m_pAudio->Play(m_select1_se, -1000, false);
		m_select1_flag = true;
		m_select2_flag = false;
		m_select3_flag = false;
	}
}

void SoundManager::SoundSelect2SE()
{
	if (m_select2_flag == false)
	{
		m_pAudio->Play(m_select2_se, -1000, false);
		m_select1_flag = false;
		m_select2_flag = true;
		m_select3_flag = false;
		m_select2_flag = true;
	}
}

void SoundManager::SoundSelect3SE()
{
	if (m_select3_flag == false)
	{
		m_pAudio->Play(m_select3_se, -1000, false);
		m_select1_flag = false;
		m_select2_flag = false;
		m_select3_flag = true;
	}
}

void SoundManager::SoundClickSE()
{
	m_pAudio->Play(m_click_se, 0, false);
}

void SoundManager::SoundBullet1SE()
{
	m_pAudio->Play(m_bullet1_se, -1000, false);
}

void SoundManager::SoundBullet2SE()
{
	m_pAudio->Play(m_bullet1_se, -1000, false);
}

void SoundManager::SoundBullet3SE()
{
	m_pAudio->Play(m_bullet1_se, -1000, false);
}

void SoundManager::ResetSelectFlag()
{
	m_select1_flag = false;
	m_select2_flag = false;
	m_select3_flag = false;
}

void SoundManager::ReleaseTitleSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_select1_se);

}

void SoundManager::ReleaseSelectSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_select1_se);
	m_pAudio->Release(m_select2_se);
	m_pAudio->Release(m_select3_se);
}

void SoundManager::ReleaseBattleSound()
{
	m_pAudio->Release(m_bgm);
	m_pAudio->Release(m_bullet1_se);
	m_pAudio->Release(m_bullet2_se);
	m_pAudio->Release(m_bullet3_se);
}

SoundManager::SoundManager()
{
	m_select1_flag = false;
	m_select2_flag = false;
	m_select3_flag = false;

	m_bgm = "BGM";
	m_select1_se = "SelectSE";
	m_select2_se = "Select2SE";
	m_select3_se = "Select3SE";
	m_click_se = "ClickSE";
	m_bullet1_se = "BulletSE";
}

SoundManager::~SoundManager()
{

}

