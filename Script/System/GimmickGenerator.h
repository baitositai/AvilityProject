#include <memory>
#include <list>
#include <vector>
#include <functional>
#include <unordered_map>
#include "../../Manager/Game/GimmickTypes.h"
#include "../../Common/Vector2F.h"

class GimmickBase;
class GimmickDoor;
class GimmickTarget;
class GimmickBamboo;
class GimmickGrowingBamboo;
class GimmickTreasureChest;
class GimmickShop;

class ParameterGimmick;

class GimmickGenerator
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GimmickGenerator();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GimmickGenerator();

	/// <summary>
	/// パラメータ情報を初期化
	/// </summary>
	void InitParameter();

	/// <summary>
	/// ギミックの生成
	/// </summary>
	/// <param name="type">種類</param>
	/// <returns>ギミックを返す</returns>
	std::unique_ptr<GimmickBase> Create(const GimmickTypes::TYPE type);

	/// <summary>
	/// ターゲットの生成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="isMove">移動判定</param>
	/// <returns>ギミックを返す</returns>
	std::unique_ptr<GimmickTarget> CreateTarget(const Vector2F pos, const Vector2F& moveDir = {});
	
private:

	// イベントの生成マップ
	std::unordered_map<GimmickTypes::TYPE, std::function<std::unique_ptr<GimmickBase>()>> createGimmickMap_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<GimmickTypes::TYPE, std::unique_ptr<ParameterGimmick>> templateParameterMap_;

	// 各種ギミックの生成処理
	std::unique_ptr<GimmickDoor> CreateGimmickDoor();
	std::unique_ptr<GimmickTarget> CreateGimmickTarget();
	std::unique_ptr<GimmickBamboo> CreateGimmickBamboo();
	std::unique_ptr<GimmickGrowingBamboo> CreateGimmickGrowingBamboo();
	std::unique_ptr<GimmickTreasureChest> CreateGimmickTreasureChest();
	std::unique_ptr<GimmickShop> CreateGimmickShop();
};