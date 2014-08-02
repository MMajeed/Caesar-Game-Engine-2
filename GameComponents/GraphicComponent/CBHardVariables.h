#ifndef __CBHardVariables__
#define __CBHardVariables__

#include "Linker.h"
#include "GraphicCameraEntity.h"
#include "GraphicObjectEntity.h"
#include "CBSetup.h"
#include <hash_map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

class GraphicComponentDLL_API CBHardVariables : public CBVariables
{
protected:
	CBHardVariables(std::vector<char>& bytes, const unsigned int StartOffset, const unsigned int sizeOfValue);
public:
	virtual void Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object) = 0;

	const unsigned int sizeOfValue;

	virtual std::string VName() const = 0{ return ""; };

	virtual ~CBHardVariables(){}
};


class GraphicComponentDLL_API CBufferWorld : public CBHardVariables
{
protected:
	CBufferWorld(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "World"; }
};

class GraphicComponentDLL_API CBufferView : public CBHardVariables
{
protected:
	CBufferView(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "View"; }
};

class GraphicComponentDLL_API CBufferProjection : public CBHardVariables
{
protected:
	CBufferProjection(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	std::string VName() const { return Name(); }
	static std::string Name() { return "Projection"; }
};

class GraphicComponentDLL_API CBufferWVP : public CBHardVariables
{
protected:
	CBufferWVP(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "WVP"; }
};

class GraphicComponentDLL_API CBufferEye : public CBHardVariables
{
protected:
	CBufferEye(std::vector<char>& bytes, const unsigned int StartOffset);
public:
	virtual void Update(const GraphicCameraEntity& camera, const GraphicObjectEntity& object);
	static std::shared_ptr<CBHardVariables> Spawn(std::vector<char>& bytes, const unsigned int StartOffset);
	virtual std::string VName() const { return Name(); }
	static std::string Name() { return "Eye"; }
};

using VariableCreatorFunction = std::function<std::shared_ptr<CBHardVariables>(std::vector<char>&, const unsigned int)>;
VariableCreatorFunction FindCBHardVariable(std::string Name);

#endif //__CBHardVariables__
