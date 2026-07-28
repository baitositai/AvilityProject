#pragma once
#include <vector>
#include <functional>
#include <unordered_map>
#include "../../Component/Avility/AvilityTypes.h"
#include "../UiBase.h"

class SceneManager;
class SoundManager;

class UiExplanations : public UiBase
{
public:

	enum class TYPE
	{
		MOVE,
		DASH,
		JUMP,
		THROW,
		ATTACK,
		ABILITY,
	};
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UiExplanations();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~UiExplanations() override;

	void Init() override;
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 追加
	/// </summary>
	/// <param name="type">種類</param>
	/// <param name="abilityType">アビリティの種類</param>
	void Add(const TYPE type, const AvilityTypes::TYPE abilityType = AvilityTypes::TYPE::MAX);

private:

	static constexpr int EXPLANATION_NUM = 11;
	static constexpr float DISPLAY_TIME = 3.0f;
	static constexpr float MOVE_TIME = 1.0f;
	static constexpr int POS_Y = 236;
	static constexpr float START_POS = 1376.0f;
	static constexpr float END_POS = 1184.0f;

	SceneManager& sceneManager_;
	SoundManager& soundManager_;


	int* handles_;
	int index_;
	float moveStep_;	
	// 表示位置
	std::function<void()> update_;
	std::vector<int> indexList_;
	const std::unordered_map<TYPE, int> INDEX_MAP = {
		{ TYPE::MOVE, 0},
		{ TYPE::DASH, 1},
		{ TYPE::JUMP, 2},
		{ TYPE::THROW, 3},
		{ TYPE::ATTACK, 4},
	};

	const std::unordered_map<AvilityTypes::TYPE, int> INDEX_ABILITY_MAP = {
		{ AvilityTypes::TYPE::STAMP, 5},
		{ AvilityTypes::TYPE::SHOT, 6},
		{ AvilityTypes::TYPE::TELEPORT, 7},
		{ AvilityTypes::TYPE::GRAVITYCONTROLL, 8},
		{ AvilityTypes::TYPE::AIRWALK, 9},
		{ AvilityTypes::TYPE::AIRSLASH, 10},
	};

	std::unordered_map<int, bool> displayMap_;

	void UpdateEnter();
	void UpdateExit();
	void UpdateDisplay();
};

