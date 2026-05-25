#include "ParameterStage.h"

ParameterStage::ParameterStage() :
	chipSize_(Vector2()),
	path_(""),
	hitIds_(std::vector<int>())
{
}

ParameterStage::~ParameterStage()
{
}

void ParameterStage::LoadParameter(const Json& parameter)
{
    // ƒpƒ‰ƒ[ƒ^‚Ì“Ç‚İ‚İ
    path_ = parameter.value("path", "");
    hitIds_ = parameter.value("hitIds", std::vector<int>());

    if (parameter.contains("chipSize"))
    {
        chipSize_.x = parameter["chipSize"].value("x", -1);
        chipSize_.y = parameter["chipSize"].value("y", -1);
    }
}
