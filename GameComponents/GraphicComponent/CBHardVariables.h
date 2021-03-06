#ifndef __CBHardVariables__
#define __CBHardVariables__

#include "Linker.h"
#include "GraphicCameraEntity.h"
#include "GraphicDrawSettingsEntity.h"
#include "GraphicObjectEntity.h"
#include "CBSetup.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

class GraphicComponentDLL_API CBHardVariables : public CBVariables
{
protected:
	CBHardVariables(std::vector<char>& bytes, const unsigned int StartOffset, const unsigned int sizeOfValue);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object) = 0;

	const unsigned int sizeOfValue;

	virtual std::string VName() const = 0{ return ""; };

	virtual ~CBHardVariables(){}
};


class GraphicComponentDLL_API CBufferWorld : public CBHardVariables
{
protected:
	CBufferWorld(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "World"; }
};

class GraphicComponentDLL_API CBufferView : public CBHardVariables
{
protected:
	CBufferView(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "View"; }
};

class GraphicComponentDLL_API CBufferView2D : public CBHardVariables
{
protected:
	CBufferView2D(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "View2D"; }
};

class GraphicComponentDLL_API CBufferPerspective : public CBHardVariables
{
protected:
	CBufferPerspective(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	std::string VName() const { return Name(); }
	static std::string Name() { return "Perspective"; }
};

class GraphicComponentDLL_API CBufferOrthogonal : public CBHardVariables
{
protected:
	CBufferOrthogonal(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	std::string VName() const { return Name(); }
	static std::string Name() { return "Orthogonal"; }
};

class GraphicComponentDLL_API CBufferWVP : public CBHardVariables
{
protected:
	CBufferWVP(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "WVP"; }
};

class GraphicComponentDLL_API CBufferWVO : public CBHardVariables
{
protected:
	CBufferWVO(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "WVO"; }
};

class GraphicComponentDLL_API CBufferEye : public CBHardVariables
{
protected:
	CBufferEye(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "Eye"; }
};

class GraphicComponentDLL_API CBufferScreenWidth : public CBHardVariables
{
protected:
	CBufferScreenWidth(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "ScreenWidth"; }
};

class GraphicComponentDLL_API CBufferScreenHeight : public CBHardVariables
{
protected:
	CBufferScreenHeight(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(std::shared_ptr<GraphicCameraEntity> camera, std::shared_ptr<GraphicDrawSettingsEntity> drawSettings, std::shared_ptr<GraphicObjectEntity> object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "ScreenHeight"; }
};

using VariableCreatorFunction = std::function<std::shared_ptr<CBHardVariables>(std::vector<char>&, const unsigned int)>;
VariableCreatorFunction findCBHardVariable(std::string Name);

#endif //__CBHardVariables__
