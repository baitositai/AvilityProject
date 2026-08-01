#pragma once
#include "SceneBase.h"
#include "../Manager/Common/SoundType.h"
#include "../Common/CharacterString.h"

class ComponentTextAnimation;

class SceneTutorial : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneTutorial();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneTutorial() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;

private:

	// ステップ
	enum class STEP
	{
		GREETING,					// 挨拶
		BASE_ACTION,				// 基本操作確認
		ATTACK_ACTION_READY,		// 攻撃確認準備
		ATTACK_ACTION,				// 攻撃確認
		WORK_ACTION_READY,			// お金稼ぎ準備
		WORK_ACTION,				// お金稼ぎ
		ABILITY_GET_ACTION_READY,	// アビリティ取得準備
		STAMP_READY,				// スタンプ準備
		STAMP,						// スタンプ
		SHOT_READY,					// ショット準備
		SHOT,						// ショット
		TEREPORT_READY,				// テレポート準備
		TEREPORT,					// テレポート
		GRAVITY_READY,				// 重力準備
		GRAVITY,					// 重力
		END,						// 終了
		MAX
	};

	// テキスト
	std::unordered_map<STEP, std::vector<std::wstring>> TEXT_MAP = {
		{STEP::GREETING, {
			L"", 
			L"ゲームの説明をするよ", 
			L"このゲームはお金を稼ぎながら進む", 
			L"横スクロールアクションゲームだよ", 
			L"まずは基本操作を説明するね"}},
		{STEP::BASE_ACTION, {
			L"LStick:移動 B:ジャンプ A:ダッシュ", 
			L"いいね"}},
		{STEP::ATTACK_ACTION_READY, {
			L"次は攻撃だよ", 
			L"スライムを倒してみよう"}},
		{STEP::ATTACK_ACTION, {
			L"X:こうげき", 
			L"ナイス"}},
		{STEP::WORK_ACTION_READY, {
			L"そしたら次はお金を稼ぐよ", 
			L"お金は今みたいに敵を倒すと落ちるし", 
			L"お宝を盗んで還元もできる", 
			L"お宝を電車に投げ入れると", 
			L"少しボーナスで多めにもらえるよ",
			L"試しにお宝を投げてみよう"}},
		{STEP::WORK_ACTION, {
			L"A:ひろう RB/RT:投げる",
			L"素晴らしい"}},
		{STEP::ABILITY_GET_ACTION_READY, {
			L"最後にアビリティを紹介するよ", 
			L"アビリティは歯車みたいなアイテムで",
			L"ひろうと特別な力が手に入るよ",
			L"最大3つまで身につけれるから",
			L"色々とっかえひっかえしてゲームを進めるんだ",
			L"今回は特別な操作が必要なアビリティだけ紹介するよ",}},
		{STEP::STAMP_READY, {
			L"まずはスタンプだよ",
			L"空中から勢いよく落ちて攻撃できる技だよ",
			}},
		{STEP::STAMP, {
			L"スタンプ:B+LStick↓",
			L"次いくよ"}},
		{STEP::SHOT_READY, {
			L"次はショットだよ",
			L"力を溜めてぶっとぶ技だよ"}},
		{STEP::SHOT, {
			L"ショット:Y+LStick↓",
			L"次いくよ"}},
		{STEP::TEREPORT_READY, {
			L"次はテレポートだよ",
			L"消えて移動できる技で攻撃もできるよ"}},
		{STEP::TEREPORT, {
			L"テレポート:Y+LStick↑",
			L"次いくよ"}},
		{STEP::GRAVITY_READY, {
			L"最後に重力操作だよ",
			L"上下左右に重力方向を変えれるよ"}},
		{STEP::GRAVITY, {
			L"重力切り替え:RStick",
			L"特別な操作のものはこれくらいだよ"}},
		{STEP::END, {
			L"他にもアビリティはあるし", 
			L"色々試したいときはお試し部屋を使ってね", 
			L"アビリティやアイテムを駆使して", 
			L"いっぱいお金を稼ごう！"}},
	};

	// 表示時間
	static constexpr float DISPLAY_TIME = 2.0f;

	// 移動量条件
	static constexpr float MOVE_AMOUNT = 50000.0f;

	// クリアスコア
	static constexpr int CLEAR_SCORE = 33000;

	// メッセージカウント
	int messageCnt_;

	// 移動量バックアップ
	float backPosX_;
	float movedAmount_;	
	
	// ジャンプ判定
	bool isJump_;

	// ステップのクリア判定
	bool isClear_;

	// ステップ種類
	STEP nowStep_;
	STEP nextStep_;

	// 再生しているBGM種類
	SoundType::BGM soundType_;

	// メッセージ
	CharacterString message_;

	// タイマー
	float timer_;

	// 更新処理
	std::function<void()> stepFunction_;

	// 状態遷移処理
	std::unordered_map<STEP, std::function<void()>> changeStepMap_;

	// テキストアニメーション
	std::unique_ptr<ComponentTextAnimation> textAnimation_;

	// 更新関数
	void NormalUpdate() override;

	// 描画関数
	void NormalDraw() override;

	// 各ステップ別更新処理
	void UpdateMessage();
	void UpdateStepBaseAction();
	void UpdateStepAttackAction();
	void UpdateStepWorkAction();
	void UpdateStepAbilityGetAction();
	void UpdateStepStamp();
	void UpdateStepShot();
	void UpdateStepTeleport();
	void UpdateStepGravityControll();
	void UpdateStepEnd();

	// 状態遷移処理
	void ChangeStep(const STEP step);
	void ChangeStepGreeting();
	void ChangeStepBaseAction();
	void ChangeStepAttackActionReady();
	void ChangeStepAttackAction();
	void ChangeStepWorkActionReady();
	void ChangeStepWorkAction();
	void ChangeStepAbilityGetActionReady();
	void ChangeStepStampReady();
	void ChangeStepStamp();
	void ChangeStepShotReady();
	void ChangeStepShot();
	void ChangeStepTeleportReady();
	void ChangeStepTeleport();
	void ChangeStepGravityControllReady();
	void ChangeStepGravityControll();
	void ChangeStepEnd();
};