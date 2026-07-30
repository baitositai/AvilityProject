#pragma once
#include <string>
#include <functional>
#include "../Common/Image.h"
#include "../Common/Sprite.h"

class SceneManager;
class SoundManager;
class PlayerManager;
class EnemyManager;

class GameStart
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="index">描画番号</param>
	GameStart(const int index);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameStart();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了判定
	/// </summary>
	/// <returns>終了判定</returns>
	const bool IsEnd() const { return isEnd_; }

private:

	SceneManager& sceneManager_;
	PlayerManager& playerManager_;
	EnemyManager& enemyManager_;
	SoundManager& soundManager_;

	// サブタイトル用描画番号
	int index_;

	// リソース
	Image mainTitle_;
	Sprite subTitle_;
	Image bar_;

	// バーサイズ
	Vector2 barSize_;

	// バーの長さ
	float barLength_;

	// ステップ
	float step_;

	// 終了判定
	bool isEnd_;

	// 処理
	std::function<void()> update_;

	// 更新処理
	void UpdateReady();
	void UpdateGo();
};

