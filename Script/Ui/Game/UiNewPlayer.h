#include "../UiBase.h"

class PlayerManager;

class UiNewPlayer : public UiBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiNewPlayer();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiNewPlayer() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	// プレイヤー管理クラス
	const PlayerManager& playerManager_;

};