#pragma once
#include <memory>
#include <vector>

class InputManager;

class PlayerNewAccept
{
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerNewAccept();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerNewAccept();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="playerNum">現在のプレイヤー人数</param>
	void Init(const int playerNum);

	/// <summary>
	/// 新規プレイヤーからの入力判定
	/// </summary>
	/// <returns>入力されてるか</returns>
	int IsNewPlayerAccept();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="padNo"></param>
	void SetPadNo(const int padNo) { padList_.push_back(padNo); }

private:

	// 管理クラスの参照
	InputManager& inputManager_;

	// パッドリスト
	std::vector<int> padList_;
};

