#ifndef __OBJECTINFO__
#define __OBJECTINFO__

#include "Linker.h"
#include "INFO.h"
#include <Vector.h>
#include <Matrix.h>
#include <vector>
#include <array>

class CommonDLL_API ObjectINFO : public INFO
{
public:
	ObjectINFO();

	static const unsigned int USERDATASIZE = 16;

protected:
	CML::Vec4 Location;
	CML::Vec4 Rotation;
	CML::Vec4 Scale;
	CML::Matrix4x4 TranslationMatrix;
public:
	const CML::Vec4& GetLocation() const;
	void SetLocation(CML::Vec4 v);
	const CML::Vec4& GetRotation() const;
	void SetRotation(CML::Vec4 v);
	const CML::Vec4& GetScale() const;
	void SetScale(CML::Vec4 v);

	CML::Matrix4x4 GetTranslationMatrix();

	CML::Vec4 Diffuse;
	CML::Vec4 Ambient;
	CML::Vec4 Specular;
	std::string DrawObjID;
	std::vector<std::string> Texture2DVecs;
	std::vector<std::string> TextureCubeVecs;
	bool Light;
	bool Shadow;
	bool Depth;
	std::array<float, USERDATASIZE> UserData;
	struct sAnimationJoint
	{
		std::string AnimationID;
		std::string JointName;
	} AnimationJoint;
	std::string PhysicsRigidBodyID;

	void UpdateTranslationMatrix();

	virtual std::shared_ptr<Object> Get(const std::string& ID);
	virtual void Set(const std::string& ID, std::shared_ptr<Object> obj);
	virtual std::shared_ptr<INFO> Clone();
};

#endif //__OBJECTINFO__