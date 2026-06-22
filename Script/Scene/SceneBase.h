#pragma once
#include<functional>
#include<memory>

class SceneManager;
class ResourceManager;
class SoundManager;
class InputManager;
class FontManager;
class ScoreManager;
class Loading;

class PlayerManager;
class EnemyManager;
class ItemManager;
class StageManager;
class GimmickManager;
class SpriteEffectManager;
class CollisionManager;
class UiManager;
class FactoryComponent;

class SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~SceneBase();

	/// <summary>
	/// 読み込み処理
	/// </summary>
	virtual void Load();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// シーン遷移の準備
	/// </summary>
	virtual void SceneChangeReady();

protected:

	// リソース管理
	ResourceManager& resMng_;
	InputManager& inputMng_;
	SoundManager& sndMng_;
	SceneManager& scnMng_;
	FontManager& fontMng_;
	ScoreManager& scoreManager_;
	Loading& loading_;

	// オブジェクト管理
	PlayerManager& playerMng_;
	EnemyManager& enemyMng_;
	CollisionManager& collisionMng_;
	StageManager& stageMng_;
	ItemManager& itemMng_;
	SpriteEffectManager& effectMng_;
	GimmickManager& gimmickMng_;
	UiManager& uiMng_;
	FactoryComponent& facCom_;

	//更新処理管理
	std::function<void()> updataFunc_;
	std::function<void()> drawFunc_;

	//更新関数
	virtual void LoadingUpdate();
	virtual void NormalUpdate();

	//描画関数
	virtual void LoadingDraw();
	virtual void NormalDraw();

	//デバッグ処理
	virtual void DebugUpdate();
	virtual void DebugDraw();	
	
private:

	//ローディング処理から通常処理へ
	void ChangeNormal();
};