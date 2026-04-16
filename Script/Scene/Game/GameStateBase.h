#pragma once

class PlayerManager;
class EnemyManager;
class CollisionManager;
class StageManager;

class GameStateBase
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameStateBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameStateBase();

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
	/// デバッグ描画処理
	/// </summary>
	virtual void DebugDraw();

protected:

	// プレイヤー管理
	PlayerManager& playerMng_;

	// 敵管理
	EnemyManager& enemyMng_;
	
	// 衝突管理
	CollisionManager& collisionMng_;
	
	// ステージ管理
	StageManager& stageMng_;
};