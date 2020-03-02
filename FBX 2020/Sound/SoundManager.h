#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "AudioPlayer.h"
#include"../Window.h"
#include <string>

class SoundManager
{
public:
	static SoundManager* Instance();

	// 各シーンごとの音素材登録
	void RegisterTitleSound();		// タイトル
	void RegisterSelectSound();		// セレクト
	void RegisterGameMainSound();	// ゲームメイン
	void RegisterEndSound();		// ゲームエンド

	// 鳴らす関数
	void SoundBGM();
	void SoundSelectBGM();
	void SoundSelectSE();
	void SoundSelect2SE();
	void SoundSelect3SE();
	void SoundClickSE();
	void SoundBullet1SE();
	void SoundBullet2SE();
	void SoundBullet3SE();

	void ResetSelectFlag();

	// 解放関数
	void ReleaseTitleSound();
	void ReleaseSelectSound();
	void ReleaseBattleSound();

protected:
	SoundManager();
	~SoundManager();

private:
	static SoundManager* p_instance;

	bool m_select1_flag;	// selectSEをループさせないためのフラグ
	bool m_select2_flag;
	bool m_select3_flag;


	// 使用する際の変数名　※初期化必須
	std::string m_bgm;
	std::string m_select1_se;
	std::string m_select2_se;
	std::string m_select3_se;
	std::string m_click_se;
	std::string m_bullet1_se;
	std::string m_bullet2_se;
	std::string m_bullet3_se;

	// flie読み込み用変数
	std::string m_bgm_file;
	std::string m_se1_file;
	std::string m_se2_file;
	std::string m_se3_file;
	std::string m_click_se_file;
	std::string m_bullet1_se_file;
	std::string m_bullet2_se_file;
	std::string m_bullet3_se_file;

	AudioPlayer* m_pAudio = AudioPlayer::GetInstance(GetWindowHandle());
};

#endif

