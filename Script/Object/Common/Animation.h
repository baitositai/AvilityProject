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
		WALK,
		DASH,
		BRAKE,
		ATTACK,
		ATTACK_2,
		ATTACK_3,
		ATTACK_4,
		JUMP,
		FALL,
		DEAD,
		DAMAGE,
		PAUSE,
		DEFENCE,
		EFFECT, 
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
	/// リスタート
	/// </summary>
	void Restart() { isPlay_ = true; }

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
	void SetNextAnimationType(const TYPE nextType, const bool isNextLoop = true);

	void SetAnimationSpeed(const std::string stringType, const float speed = 1.0f);

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
		{ "dash", TYPE::DASH },
		{ "brake", TYPE::BRAKE },
		{ "attack", TYPE::ATTACK },
		{ "attack2", TYPE::ATTACK_2 },
		{ "attack3", TYPE::ATTACK_3 },
		{ "attack4", TYPE::ATTACK_4 },
		{ "jump", TYPE::JUMP },
		{ "fall", TYPE::FALL },
		{ "dead", TYPE::DEAD },
		{ "damage", TYPE::DAMAGE },
		{ "pause", TYPE::PAUSE },
		{ "defence", TYPE::DEFENCE },
		{ "effect", TYPE::EFFECT },
	};

	// アニメーション種類
	TYPE type_;

	// 次の再生予定のアニメーション種類
	TYPE nextType_;

	// アニメーション番号
	int animationIndex_;

	// ループ判定
	bool isLoop_;

	// 次のアニメーションのループ判定
	bool isNextLoop_;

	// 再生判定
	bool isPlay_;

	// アニメーションデータ管理マップ
	std::unordered_map<TYPE, Data> animationMap_;
};