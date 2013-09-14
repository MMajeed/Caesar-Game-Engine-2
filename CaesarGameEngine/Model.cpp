#include "Model.h"

Model::Model(std::string file)
{
	this->scene = aiImportFile(file.c_str(), aiProcessPreset_TargetRealtime_MaxQuality|aiProcess_ConvertToLeftHanded);
}