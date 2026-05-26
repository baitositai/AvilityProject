#include "ParameterStage.h"

ParameterStage::ParameterStage() :
	chipSize_(Vector2()),
	path_(""),
    tileIndexs_(std::vector<std::vector<int>>())
{
}

ParameterStage::~ParameterStage()
{
}

void ParameterStage::LoadParameter(const Json& parameter)
{
    // ƒpƒ‰ƒ[ƒ^‚Ì“Ç‚İ‚İ
    path_ = parameter.value("path", "");

    if (parameter.contains("chipSize"))
    {
        chipSize_.x = parameter["chipSize"].value("x", -1);
        chipSize_.y = parameter["chipSize"].value("y", -1);
    }
}
