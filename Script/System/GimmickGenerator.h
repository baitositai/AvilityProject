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
	/// <returns>イベントのインスタンス</returns>
	std::unique_ptr<GimmickBase> Create(const GimmickTypes::TYPE type);

private:

	// イベントの生成マップ
	std::unordered_map<GimmickTypes::TYPE, std::function<std::unique_ptr<GimmickBase>()>> createGimmickMap_;

	// テンプレートとなるパラメータマップ
	std::unordered_map<GimmickTypes::TYPE, std::unique_ptr<ParameterGimmick>> templateParameterMap_;

	// 各種ギミックの生成処理
	std::unique_ptr<GimmickDoor> CreateGimmickDoor();
	std::unique_ptr<GimmickTarget> CreateGimmickTarget();
};