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

	/// <summary>
	/// hitInfoから、押し出しを実行
	/// </summary>
	/// <param name=""></param>
	void ResultPush(void);

private:

	enum class PRIORITY
	{
		STAGE=0,
		CHARACTER_PUSH=1,
		NORMAL=2
	};

	//オーナー
	AvilityBox& owner_;

	//押し出す方向box同士)
	bool pushDir_;

	//押し出し処理
	std::unordered_map<CollisionTags::TAG, std::function<void(const std::shared_ptr<ColliderBase>)>>pushFunc_;


	void OnHitPlayer(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitEnemy(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitStage(const std::weak_ptr<ColliderBase>& opponentCollider);
	void OnHitBox(const std::weak_ptr<ColliderBase>& opponentCollider);

	void PushOnHitPlayer(void);
	void PushOnHitBox(void);
};