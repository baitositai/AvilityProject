#pragma once
#include <functional>
#include <unordered_map>
#include <array>
#include "SceneBase.h"
#include "../Common/Image.h"
#include "../Common/Sprite.h"
#include "../Manager/Common/Input.h"

class Application;

class SceneSetting : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneSetting();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneSetting() override;

	/// <summary>
	/// 初期化か
	/// </summary>
	void Init() override;

	/// <summary>
	/// PAD番号を指定
	/// </summary>
	/// <param name="padNo">画面を操作するユーザー</param>
	void SetPadNo(const Input::JOYPAD_NO padNo) { padNo_ = padNo; }

private:

	// 種類
	enum class TYPE
	{
		SCREEN,
		VOLUME_BGM,
		VOLUME_SE,
		ETC,
		MAX
	};

	// 総種類数
	static constexpr int TYPE_MAX = 4;

	// アプリケーションの参照
	Application& application_;

	// 選択項目
	int selectIndex_;
	
	// ウィンドウ判定
	bool isWindow_;
	
	// 選択状態
	bool isBack_;

	// 音量
	int volumeSe_;
	int volumeBgm_;

	// 操作プレイヤーコントローラー
	Input::JOYPAD_NO padNo_;

	// リソース
	std::array<Sprite, TYPE_MAX> typeSprites_;
	Sprite screenSprite_;
	Image triangle_;
	int* numberHandles_;
	float numberScale_;
	Vector2 volumeBgmPos_;
	Vector2 volumeSePos_;

	// 種類別更新処理
	std::unordered_map<TYPE, std::function<void()>> updateTypeMap_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	// タイプ別処理
	void UpdateTypeScreen();
	void UpdateTypeVolumeBgm();
	void UpdateTypeVolumeSe();
	void UpdateTypeEtc();

	// 適用処理
	void Apply();

	// 戻る処理
	void Back();

	// 数字の描画
	void DrawNumber(const Vector2& pos, const int volume);
};

