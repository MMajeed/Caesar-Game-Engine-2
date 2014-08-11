#ifndef __Keys__
#define __Keys__

#include <string>

namespace Keys
{
	namespace Camera
	{
		const static std::string EYE                = "Eye";
		const static std::string TARGETMAGNITUDE    = "TargetMagnitude";
		const static std::string UP                 = "Up";
		const static std::string ROLL				= "Roll";
		const static std::string PITCH				= "Pitch";
		const static std::string YAW				= "Yaw";
		const static std::string FOVANGLE		    = "FovAngle";
		const static std::string NEARZ			    = "NearZ";
		const static std::string FARZ               = "FarZ";
		const static std::string CLEARCOLOR         = "ClearColor";
		const static std::string TEXTURE		    = "Texture";
		const static std::string USERDATA			= "UserData";
		const static std::string INCLUSIONSTATE     = "InclusionState";
		const static std::string INCLUSIONLIST		= "InclusionList";
		const static std::string VERTEXSHADER		= "VertexShader";
		const static std::string VERTEXSHADERSTATE	= "VertexShaderState";
		const static std::string PIXELSHADER		= "PixelShader";
		const static std::string PIXELSHADERSTATE	= "PixelShaderState";
	};
	
	namespace BasicTexture
	{
		const static std::string TEXTUREFILE = "TextureFile";
		const static std::string TEXTUREOBJ  = "TextureObj";
	}

	namespace ObjectInfo
	{
		const static std::string LOCATION       = "Location";
		const static std::string ROTATION       = "Rotation";
		const static std::string SCALE          = "Scale";
		const static std::string DEPTH          = "Depth";
		const static std::string PRIORITY		= "Priority";
		const static std::string GRAPHICMODEL	= "GraphicModel";
		const static std::string VERTEXSHADER	= "VertexShader";
		const static std::string GEOMETRYSHADER	= "GeometryShader";
		const static std::string PIXELSHADER	= "PixelShader";
		const static std::string ANIMATIONOBJ   = "AnimationObj";
		const static std::string ANIMATIONJOINT = "AnimationJoint";
		const static std::string RIGIDBODY      = "RigidBody";
		const static std::string TEXTURE        = "Texture";
		const static std::string GROUP			= "Group";
		const static std::string USERDATA		= "UserData";
		const static std::string FILLMODE		= "FillMode";
		const static std::string CULLMODE		= "CullMode";
	};

	namespace ScreenShot
	{
		const static std::string ScreenShotOBJ     = "ScreenShotObj";
		const static std::string WIDTH             = "Width";
		const static std::string HEIGHT            = "Height";
		const static std::string CAMERAID          = "CameraID";
		const static std::string EYE               = "Eye";
	};

	namespace AnimationController
	{
		const static std::string BASICANIMATION		= "BasicAnimation";
		const static std::string ROOTNODE	        = "RootNode";
		const static std::string SPEED				= "Speed";
		const static std::string TRANSITIONTYPE 	= "TransitionType";
		const static std::string TRANSITIONLENGTH	= "TransitionLength";
		const static std::string STARTONNEXTPHASE 	= "StartOnNextPhase";
		const static std::string STARTNODENAME	    = "StartNodeName";
		const static std::string STARTRATIO			= "StartRatio";
		const static std::string STEPRATIO			= "StepRatio";
	};

	namespace RigidBody
	{
		const static std::string POSITION       = "Position";
		const static std::string ROTATION       = "Rotation";
		const static std::string INERTIA        = "Inertia";
		const static std::string MASS           = "Mass";
		const static std::string COLLISIONSHAPE = "CollisionShape";
	};

	namespace Constraint
	{
		const static std::string RIGIDBODYA        = "RigidBodyA";
		const static std::string PIVOTPOINTA       = "PivotPointA";
		const static std::string AXESA             = "AxesA";
		const static std::string RIGIDBODYB        = "RigidBodyB";
		const static std::string PIVOTPOINTB       = "PivotPointB";
		const static std::string AXESB             = "AxesB";
		const static std::string BREAKINGTHRESHOLD = "BreakingThreshold";
		const static std::string LOW               = "Low";
		const static std::string HIGH              = "High";
		const static std::string SOFTNESS          = "Softness";
		const static std::string BIASFACTOR        = "BiasFactor";
		const static std::string RELEXATIONFACTOR  = "RelaxationFactor";
		const static std::string MAXMOTORIMPULSE   = "MaxMotorImpulse";
	};
};

#endif //__Keys__
