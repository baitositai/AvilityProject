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
class UiBase;
class UiMoney;

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
	SceneShop();

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

	/// <summary>
	/// PAD番号を指定
	/// </summary>
	/// <param name="padNo">画面を操作するユーザー</param>
	void SetPadNo(const Input::JOYPAD_NO padNo) { padNo_ = padNo; }

private:

	// 状態
	enum class STATE
	{
		SELECT,
		CHECK,
		MAX
	};

	// テキスト種類
	enum class TEXT_TYPE
	{
		ENTER,				// 入室
		EXIT,				// 退室
		INSUFFICIENT_FUNDS,	// 残額不足
		CONFIRMATION,		// 確認
		THANK_YOU,			// 感謝
		ITEM_FOOD,			// 食べ物
		ITEM_ABILITY,		// 能力
		ITEM_POTION,		// ポーション
		MAX
	};

	// テキストマップ
	std::unordered_map<TEXT_TYPE, std::wstring> TEXT_MAP = {
		{ TEXT_TYPE::ENTER, L"いらっしゃいませ" },
		{ TEXT_TYPE::EXIT, L"また来てな" },
		{ TEXT_TYPE::INSUFFICIENT_FUNDS, L"お金が足り―ひん" },
		{ TEXT_TYPE::CONFIRMATION, L"これを買いますか？" },
		{ TEXT_TYPE::THANK_YOU, L"ありがとうございやした" },
		{ TEXT_TYPE::ITEM_FOOD, L"体力が回復するぞ" },
		{ TEXT_TYPE::ITEM_ABILITY, L"特別な力が手に入るぞ" },
		{ TEXT_TYPE::ITEM_POTION, L"ステータスを強化するぞ" },
	};

	// 背景枚数
	static constexpr int BACK_GROUND_NUM = 10;

	// 列最大数
	static constexpr int ROW = 2;

	// 行最大数
	static constexpr int COL = 3;

	// 品物の最大数
	static constexpr int ITEM_MAX = ROW * COL;

	// 矢印相対位置
	const Vector2 ARROW_LOCAL_POS = { 64, 64 };

	// パッド番号
	Input::JOYPAD_NO padNo_;

	// 選択番号
	int selectIndex_;

	// 購入判定
	bool isPurchase_;

	// 矢印ハンドル
	int arrowHandle_;

	// SINフレーム
	float frameCount_;

	// 状態
	STATE state_;

	// 矢印位置
	Vector2 arrowPos_;

	// 持ち金
	std::unique_ptr<UiMoney> myMoney_;

	// 更新処理
	std::function<void()> stateUpdate_;

	// メッセージ
	CharacterString message_;

	// 金額
	CharacterString amount_;

	// はい、いいえ
	CharacterString yes_;
	CharacterString no_;

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

	void PurchaseCancel();

	// 状態遷移処理
	void ChangeState(const STATE state);
	void ChangeStateSelect();
	void ChangeStateCheck();

	// 購入処理
	void Purchase();

	// 確認時の描画
	void DrawCheck();

	// 品物に表示するメッセージを変更
	void ChangeItemMessage();
};