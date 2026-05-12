#pragma once
#include <string>
#include <unordered_map>

class Animation
{
public:

	// 種類
	enum class TYPE
	{
		IDLE = 0,
		WALK = 1,
		BRAKE = 2,
		ATTACK = 3,
		JUMP = 4,
		FALL = 5,
		DEAD = 6,
		DAMAGE = 7,
		PAUSE = 8,
		MAX,
	};

	// アニメーションデータ
	struct Data
	{
		int startIndex = -1;
		int endIndex = -1;
		float animationSpeed = 0.0f;
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Animation();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Animation();

	/// <summary>
	/// 追加
	/// </summary>
	/// <param name="stringType">種類</param>
	/// <param name="startIndex">開始番号</param>
	/// <param name="endIndex">終了番号</param>
	/// <param name="animationSpeed">アニメーション速度</param>
	void Add(const std::string stringType, const int startIndex, const int endIndex, const float animationSpeed);

	/// <summary>
	/// 再生
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="isLoop">ループ判定</param>
	void Play(const TYPE type, const bool isLoop = true);

	/// <summary>
	/// 停止
	/// </summary>
	void Stop();

	/// <summary>
	/// 次に再生するアニメーションを確認
	/// </summary>
	void CheckNextAnimation();

	/// <summary>
	/// アニメーションの番号の設定
	/// </summary>
	/// <param name="animationIndex">アニメーション番号</param>
	void SetAnimationIndex(const int animationIndex) { animationIndex_ = animationIndex; }

	/// <summary>
	/// 次回再生予定のアニメーション種類の設定
	/// </summary>
	/// <param name="nextType">次回再生予定のアニメーション種類</param>
	void SetNextAnimationType(const TYPE nextType) { nextType_ = nextType; }

	/// <summary>
	/// ループ判定を返す
	/// </summary>
	/// <returns>ループ判定</returns>
	const bool IsLoop() const { return isLoop_; }

	/// <summary>
	/// 再生判定を返す
	/// </summary>
	/// <returns>再生判定</returns>
	const bool IsPlay() const { return isPlay_; }
	
	/// <summary>
	/// アニメーション番号を返す
	/// </summary>
	/// <returns>アニメーション番号</returns>
	const int GetAnimationIndex() const { return animationIndex_; }

	/// <summary>
	/// アニメーション種類を返す
	/// </summary>
	/// <returns>アニメーション種類</returns>
	const TYPE GetType() const { return type_; }

	/// <summary>
	/// 指定したアニメーション情報を返す
	/// </summary>
	/// <returns>アニメーション情報</returns>
	const Data GetAnimationData() const;

private:

	// ストリング型を列挙型へ変換する
	const std::unordered_map<std::string, TYPE> animationNameMap_ =
	{
		{ "idle", TYPE::IDLE },
		{ "walk", TYPE::WALK },
		{ "brake", TYPE::BRAKE },
		{ "attack", TYPE::ATTACK },
		{ "jump", TYPE::JUMP },
		{ "fall", TYPE::FALL },
		{ "dead", TYPE::DEAD },
		{ "damage", TYPE::DAMAGE },
		{ "pause", TYPE::PAUSE },
	};

	// アニメーション種類
	TYPE type_;

	// 次の再生予定のアニメーション種類
	TYPE nextType_;

	// アニメーション番号
	int animationIndex_;

	// ループ判定
	bool isLoop_;

	// 再生判定
	bool isPlay_;

	// アニメーションデータ管理マップ
	std::unordered_map<TYPE, Data> animationMap_;
};