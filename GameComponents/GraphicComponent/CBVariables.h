#ifndef __CBVariables__
#define __CBVariables__

#include "Linker.h"
#include <ObjectEntity.h>
#include <vector>
#include "GraphicCameraEntity.h"
#include "GraphicDrawSettingsEntity.h"
#include "GraphicObjectEntity.h"

class GraphicComponentDLL_API CBVariables
{
protected:
	CBVariables(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object) = 0;

	std::vector<char>& bytes;
	const unsigned int StartOffset;

	virtual ~CBVariables(){}
};
#endif //__CBVariables__
