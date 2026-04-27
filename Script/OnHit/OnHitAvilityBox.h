#include "./OnHitBase.h"

class AvilityBox;
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

	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitBox(const std::weak_ptr<ColliderBase>& opponentCollider);
};