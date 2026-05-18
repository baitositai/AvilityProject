#pragma once
#include <unordered_map>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

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

	// 共通パラメータ
	struct Parameter
	{	
		// 描画に必要な情報
		int texureHandle = -1;					// テクスチャハンドル
		const int* texuresHandle = nullptr;		// テクスチャハンドル(スプライト用)
		float scale = 1.0f;						// 拡大率
		float angle = 0.0f;						// 角度
		bool direction = false;					// 向き(false:右,true:左)
		bool transparent = true;				// 透過判定
		Vector2 localPos = {};					// 相対位置
		Vector2 drawPos = {};					// 描画位置
		Vector2 divisionNum = {};				// 分割数

		// 移動に必要な情報		
		float moveSpeed = 0.0f;					// 移動速度
		float moveSpeedBoostRate = 0.0f;		// 移動速度上昇率
		Vector2F pos = {};						// 位置
		Vector2F moveAmount = {};				// 移動量

		// 重力関係
		float gravityPower = 0.0f;				// 重力
		float gravityBoostRate = 0.0f;			// 重力の上昇値
		DIR gravityDir = DIR::DOWN;				// 重力方向
		float weight = 0.0f;					// 物体の重み

		// 衝突判定用
		bool isGround = false;					// 地面判定
		bool isFall = false;					// 落下判定
		Vector2 hitSize = {};					// ヒットサイズ
		float hitRadius = 0.0f;					// ヒット半径
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	/// <param name="animation">アニメーション情報</param>
	ActorBase(Parameter* parameter, const std::vector<std::string>& componentNameList = {}, std::unique_ptr<Animation> animation = nullptr);

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
	/// 角度の設定
	/// </summary>
	/// <param name="angle">角度</param>
	void SetAngle(const float angle) { actorParameterPtr_->angle = angle; }

	/// <summary>
	/// 方向の設定
	/// </summary>
	/// <param name="direction">方向</param>
	void SetDirection(const bool direction) { actorParameterPtr_->direction = direction; }

	/// <summary>
	/// 重力量の設定
	/// </summary>
	/// <param name="gravityPower">重力量</param>
	void SetGravityPower(const float gravityPower) { actorParameterPtr_->gravityPower = gravityPower; }

	/// <summary>
	/// 重力量の追加
	/// </summary>
	/// <param name="gravityPower">重力量</param>
	void AddGravityPower(const float gravityPower) { actorParameterPtr_->gravityPower += gravityPower; }

	/// <summary>
	/// 重力の上昇率を追加
	/// </summary>
	/// <param name="gravityRate">重力の上昇率</param>
	void AddGravityBoostRate(const float gravityRate) { actorParameterPtr_->gravityBoostRate += gravityRate; }

	/// <summary>
	/// 重力方向の設定
	/// </summary>
	/// <param name="gravityDir">重力方向</param>
	void SetGravityDir(const DIR gravityDir) { actorParameterPtr_->gravityDir = gravityDir; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const Vector2F pos) { actorParameterPtr_->pos = pos; }

	/// <summary>
	/// 移動量の設定
	/// </summary>
	/// <param name="moveAmount">移動量</param>
	void SetMoveAmount(const Vector2F moveAmount) { actorParameterPtr_->moveAmount = moveAmount; }

	/// <summary>
	/// 地面判定の設定
	/// </summary>
	/// <param name="isGround">地面判定</param>
	void SetIsGround(const bool isGround) { actorParameterPtr_->isGround = isGround; }

	/// <summary>
	/// 落下判定の設定
	/// </summary>
	/// <param name="isFall">落下判定</param>
	void SetIsFall(const bool isFall) { actorParameterPtr_->isFall = isFall; }

	/// <summary>
	/// コライダーの活動状態の設定
	/// </summary>
	/// <param name="isActive">活動状態</param>
	void SetColliderActive(const bool isActive);

	/// <summary>
	/// 移動量の設定
	/// </summary>
	/// <param name="moveAmount">移動量</param>
	void AddMoveAmount(const Vector2F moveAmount);

	/// <summary>
	/// 移動速度の上昇率を追加
	/// </summary>
	/// <param name="moveSpeedBoostRate">移動速度の上昇率</param>
	void AddMoveSpeedBoostRate(const float moveSpeedBoostRate) { actorParameterPtr_->moveSpeedBoostRate = moveSpeedBoostRate; }

	/// <summary>
	/// パラメータ情報を返す
	/// </summary>
	/// <returns></returns>
	Parameter* GetParameter() const { return actorParameterPtr_; }

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
	/// 地面判定を返す
	/// </summary>
	/// <returns>地面判定</returns>
	const bool IsGround() const { return actorParameterPtr_->isGround; }

	/// <summary>
	/// 落下判定を返す
	/// </summary>
	/// <returns>落下判定</returns>
	const bool IsFall() const { return actorParameterPtr_->isFall; }

	/// <summary>
	/// 削除フラグをtrueにする
	/// </summary>
	/// <param name="_isDelete"></param>
	void SetIsDelete(void);

	/// <summary>
	/// 重力方向をベクトル変換して返す
	/// </summary>
	/// <returns>重力方向のベクトル</returns>
	const Vector2F GetGravityDirectionVector() const;

	/// <summary>
	/// 現在の前方向のベクトルを返す
	/// </summary>
	/// <returns>前方向のベクトル</returns>
	const Vector2F GetFront() const;

	/// <summary>
	/// 現在の後方向のベクトルを返す
	/// </summary>
	/// <returns>後方向のベクトル</returns>
	const Vector2F GetBack() const;

	/// <summary>
	/// 現在の上方向のベクトルを返す
	/// </summary>
	/// <returns>上方向のベクトル</returns>	
	const Vector2F GetUp() const;

	/// <summary>
	/// 現在の下方向のベクトルを返す
	/// </summary>
	/// <returns>下方向のベクトル</returns>	
	const Vector2F GetDown() const;

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

private:

	// 生成するコンポーネントのリスト
	const std::vector<std::string> DEFAULT_COMPONENT_CREATE_LIST;

	// 共通パラメータ(ポインタで所持)
	Parameter* actorParameterPtr_;
};