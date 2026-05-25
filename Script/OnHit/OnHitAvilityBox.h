#include "./OnHitBase.h"

class AvilityBox;
class CharacterBase;

class OnHitAvilityBox :public OnHitBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	OnHitAvilityBox(AvilityBox& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~OnHitAvilityBox()override;

private:

	//オーナー
	AvilityBox& owner_;

	//ボックスの持ち主

	//押し出す方向box同士)
	bool pushDir_;
	//壁に当たっている判定
	bool isHitWall_;

	//押し出し処理
	std::unordered_map<CollisionTags::TAG, std::function<void(const std::shared_ptr<ColliderBase>)>>pushFunc_;

	//壁に当たっていたら移動量Xをなしにする
	void HitWall(void);

	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitBox(const std::weak_ptr<ColliderBase>& opponentCollider);
};