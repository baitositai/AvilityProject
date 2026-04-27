#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"

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
		Vector2F pos = {};						// 位置
		Vector2F moveAmount = {};				// 移動量

		// 重力関係
		float gravityPower = 0.0f;				// 重力
		DIR gravityDir = DIR::DOWN;				// 重力方向
		float weight = 0.0f;					//物体の重み

		float animationSpeed = 0.0f;			// アニメーション速度の格納
	};
	
	// アニメーション用の情報
	struct ParameterAnimation
	{
		int animationType = -1;						// アニメーションの種類		
		int animationIndex = 0;						// アニメーションインデックス
		int animationStartIndex = 0;				// アニメーション開始インデックス
		int animationFinishIndex = 0;				// アニメーション終了インデックス
		float animationSpeed = 0.0f;				// アニメーションスピード
		bool isPlay = false;						// アニメーション再生判定 
		bool isStop = false;						// アニメーション停止判定
		bool isLoop = false;						// アニメーションループ判定
		std::unordered_map<int, int> animationsMap;	// 種類別アニメーション数管理マップ
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parameter">パラメータ情報</param>
	ActorBase(Parameter* parameter, const std::vector<std::string>& componentNameList = {});

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
	/// 衝突後の処理
	/// </summary>
	/// <param name="opponentCollider">衝突した相手のコライダー</param>
	void OnHit(const std::weak_ptr<ColliderBase>& opponentCollider);
	
	/// <summary>
	/// アニメーションインデックスの設定
	/// </summary>
	/// <param name="animationIndex">アニメーションインデックス</param>
	void SetAnimationIndex(const int animationIndex) { parameterAnimation_.animationIndex = animationIndex; }

	/// <summary>
	/// アニメーション速度の設定
	/// </summary>
	/// <param name="animationSpeed">アニメーション速度</param>
	void SetAnimationSpeed(const int animationSpeed) { parameterAnimation_.animationSpeed = animationSpeed; }

	/// <summary>
	/// アニメーションの再生判定を設定
	/// </summary>
	/// <param name="isPlay">再生判定</param>
	void SetAnimationIsPlay(const bool isPlay) { parameterAnimation_.isPlay = isPlay; } 
	
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
	/// 移動量の設定
	/// </summary>
	/// <param name="moveAmount">移動量</param>
	void AddMoveAmount(const Vector2F moveAmount);

	/// <summary>
	/// パラメータ情報を返す
	/// </summary>
	/// <returns></returns>
	const Parameter* GetParameter() const { return actorParameterPtr_; }

	/// <summary>
	/// アニメーション情報を返す
	/// </summary>
	/// <returns>アニメーション情報</returns>
	const ParameterAnimation& GetParameterAnimation() const { return parameterAnimation_; }

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

protected:

	// 管理クラスの参照
	SceneManager& scnMng_;
	ResourceManager& resMng_;
	SoundManager& sndMng_;
	CollisionManager& collMng_;
	FactoryComponent& facCom_;

	// アニメーション用のパラメータ
	ParameterAnimation parameterAnimation_;

	// コンポーネントの管理マップ
	std::unordered_map<std::string, std::unique_ptr<ComponentBase>> componentMap_;

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