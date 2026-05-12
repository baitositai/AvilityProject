#pragma once
#include "./ComponentAvilityBase.h"

class Player;

class ComponentAvilityBox : public ComponentAvilityBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ComponentAvilityBox(Player& owner);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComponentAvilityBox() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
private:

	//設置可能なボックス上限
	static constexpr int SET_BLAST_NUM = 3;

	//設置ボックスの数
	int boxCnt_;

	//クールタイム
	float coolCnt_;

	//ボックスの設置
	void PlaceBox();


};