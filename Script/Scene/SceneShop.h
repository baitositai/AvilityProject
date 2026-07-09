#pragma once
#include <unordered_map>
#include "SceneBase.h"
#include "../Manager/Common/Input.h"
#include "../Manager/Game/ItemTypes.h"
#include "../Common/CharacterString.h"

class ComponentTextAnimation;
class BackGround;
class ItemBase;
class PixelMaterial;
class PixelRenderer;

class SceneShop : public SceneBase
{
public:

	struct Exhibits
	{
		int handle = -1;
		int drawIndex = -1;
		int amount = -1;
		Vector2 division = {};
		std::string message = "";
		ItemTypes::TYPE type = ItemTypes::TYPE::MAX;
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="no">画面を操作するユーザー</param>
	SceneShop(const Input::JOYPAD_NO padNo);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneShop() override;

	/// <summary>
	/// 読み込み処理(何もしない)
	/// </summary>
	void Load() override {};

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	// 状態
	enum class STATE
	{
		SELECT,
		CHECK,
		MAX
	};

	// 背景枚数
	static constexpr int BACK_GROUND_NUM = 10;

	// 列最大数
	static constexpr int ROW = 2;

	// 行最大数
	static constexpr int COL = 3;

	// 品物の最大数
	static constexpr int ITEM_MAX = ROW * COL;

	// パッド番号
	const Input::JOYPAD_NO padNo_;

	// 選択番号
	int selectIndex_;

	// 購入判定
	bool isPurchase_;

	// 矢印ハンドル
	int arrowHandle_;

	// 状態
	STATE state_;

	// 更新処理
	std::function<void()> stateUpdate_;

	// テキスト
	CharacterString message_;

	// テキストアニメーション
	std::unique_ptr<ComponentTextAnimation> textAnimation_;

	// 背景
	std::unique_ptr<BackGround> backGround_[BACK_GROUND_NUM];

	// 状態別更新処理
	std::unordered_map<STATE, std::function<void()>> changeStateMap_;

	// 展示品の情報
	std::vector<Exhibits> exhibits_;

	// 購入品用のレンダラー
	std::vector<std::unique_ptr<PixelMaterial>> exhibitsMaterial_;
	std::vector<std::unique_ptr<PixelRenderer>> exhibitsRenderer_;

	//更新関数
	void NormalUpdate()override;

	//描画関数
	void NormalDraw()override;

	// 状態別更新処理
	void UpdateSelect();
	void UpdateCheck();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateSelect();
	void ChangeStateCheck();

	// 購入処理
	void Purchase();
};