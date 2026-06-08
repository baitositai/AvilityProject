#include "ParameterStage.h"

ParameterStage::ParameterStage() :
    connectNum_(-1),
	chipSize_(Vector2()),
	path_(""),
    candidates_(std::vector<std::string>()),
    tileIndexs_(std::vector<std::vector<int>>())
{
}

ParameterStage::~ParameterStage()
{
}

void ParameterStage::LoadParameter(const Json& parameter)
{
    ParameterActor::LoadParameter(parameter);

    // ƒpƒ‰ƒ[ƒ^‚Ì“Ç‚İ‚İ
    path_ = parameter.value("path", "");
    connectNum_ = parameter.value("connectNum", -1);
    candidates_ = parameter.value("candidates", std::vector<std::string>());

    if (parameter.contains("chipSize"))
    {
        chipSize_.x = parameter["chipSize"].value("x", -1);
        chipSize_.y = parameter["chipSize"].value("y", -1);
    }
}
