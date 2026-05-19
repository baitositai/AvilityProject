#pragma once
#include <unordered_map>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "../Parameter/ParameterActor.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

class ParameterActor;
class Animation;
class ColliderBase;
class OnHitBase;
class ComponentBase;

class SceneManager;
class ResourceManager;
class SoundManager;
class CollisionManager;
class FactoryComponent;

class ActorBase
{
public:	
	
	// 方向(重力用)
	enum class DIR
	{
		RIGHT,
		LEFT,
		UP,
		DOWN,
		MAX
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="animation">アニメーション情報</param>
	ActorBase(
		std::unique_ptr<ParameterActor> parameter = nullptr, 
		std::unique_ptr<Animation> animation = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ActorBase();

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
	/// デバッグ描画
	/// </summary>
	virtual void DebugDraw();

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	virtual void InitAnimation();

	/// <summary>
	/// 削除処理
	/// </summary>
	void Delete();

	/// <summary>
	/// 着地処理
	/// </summary>
	virtual void Landing();

	/// <summary>
	/// コンポーネントの追加
	/// </summary>
	/// <param name="name">コンポーネントの名前</param>
	/// <param name="component">コンポーネント</param>
	void AddComponent(const std::string& name, std::unique_ptr<ComponentBase> component);

	/// <summary>
	/// コンポーネントを外す
	/// </summary>
	/// <param name="name">コンポーネントの名前</param>
	void RemoveComponent(const std::string& name);	

	/// <summary>
	/// 指定したコンポーネントの活動状態を返す
	/// </summary>
	/// <param name="name">コンポーネント名</param>
	/// <returns>コンポーネント名前</returns>
	bool IsComponentActive(const std::string& name) const;

	/// <summary>
	/// 指定したコンポーネントの活動状態を設定
	/// </summary>
	/// <param name="name">コンポーネント名</param>
	/// <param name="isActive">活動状態</param>
	void SetComponentActive(const std::string& name, const bool isActive);
	
	/// <summary>
	/// 衝突後の処理
	/// </summary>
	/// <param name="opponentCollider">衝突した相手のコライダー</param>
	void OnHit(const std::weak_ptr<ColliderBase>& opponentCollider);

	/// <summary>
	/// コライダーの活動状態の設定
	/// </summary>
	/// <param name="isActive">活動状態</param>
	void SetColliderActive(const bool isActive);

	/// <summary>
	/// アニメーションを返す
	/// </summary>
	/// <returns>アニメーション</returns>
	Animation& GetAnimation() const { return *animation_; }

	/// <summary>
	/// パフを重ねた重力を返す
	/// </summary>
	/// <returns>重力</returns>
	const float GetGravityPowerWithBoost() const;

	/// <summary>
	/// 活動しているか返す
	/// </summary>
	/// <returns>活動判定</returns>
	const bool IsActive() const { return isActive_; }

	/// <summary>
	/// 削除するか返す
	/// </summary>
	/// <returns>削除判定</returns>
	const bool IsDelete() const { return isDelete_; }

	/// <summary>
	/// 削除フラグをtrueにする
	/// </summary>
	/// <param name="_isDelete"></param>
	void SetIsDelete(void);

	/// <summary>
	/// パラメーターを返す(変更可)
	/// </summary>
	/// <returns>パラメータ</returns>
	ParameterActor& GetParameter() { return *parameter_.get(); }

	/// <summary>
	/// パラメータを返す
	/// </summary>
	/// <returns>パラメータ</returns>
	const ParameterActor& GetParameter() const { return *parameter_.get(); }

protected:

	// 管理クラスの参照
	SceneManager& scnMng_;
	ResourceManager& resMng_;
	SoundManager& sndMng_;
	CollisionManager& collMng_;
	FactoryComponent& facCom_;

	// アニメーション
	std::unique_ptr<Animation> animation_;

	// コンポーネントの管理マップ
	std::unordered_map<std::string, ComponentBase*> componentMap_;

	// 追加順を保持し、更新（Update等）で使用するリスト
	std::vector<std::unique_ptr<ComponentBase>> componentList_;

	// コライダー
	std::shared_ptr<ColliderBase> collider_;

	// 衝突後処理
	std::unique_ptr<OnHitBase> onHit_;

	// 活動状態
	bool isActive_;

	// 削除判定
	bool isDelete_;

	// コライダーの登録
	void RegisterCollider();	
	
	// コンポーネントの生成
	virtual void CreateComponents();

	// 型変換用のパラメータを返す関数
	ParameterActor* GetParameterActorPtr() { return parameter_.get(); }

private:
	
	// パラメータ
	std::unique_ptr<ParameterActor> parameter_;
};