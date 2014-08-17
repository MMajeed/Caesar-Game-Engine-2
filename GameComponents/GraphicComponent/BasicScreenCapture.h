#ifndef __BasicScreenCapture__
#define __BasicScreenCapture__

#include "ScreenCapture.h"
#include "BasicScreenShot.h"

class GraphicComponentDLL_API BasicScreenCapture : public ScreenCapture
{
protected:
	BasicScreenCapture();
public:
	virtual void Init();
	virtual void Snap(const std::unordered_map<std::string, std::shared_ptr<GraphicObjectEntity>>& list);
	virtual std::shared_ptr<ScreenCapture> clone() const;
	virtual ~BasicScreenCapture(){}

	static std::shared_ptr<BasicScreenCapture> Spawn(const std::vector<std::string>& textureID,
													 unsigned int width,
													 unsigned int height,
													 unsigned int numberOfTargets,
													 unsigned int Priority,
													 const std::string& cameraID);

	std::shared_ptr<BasicScreenShot>	ScreenShot[2];
	std::string							cameraID;
	unsigned int						width;
	unsigned int						height;
	unsigned int						numberOfTargets;
	unsigned int						current;
};


#endif //__BasicScreenCapture__
