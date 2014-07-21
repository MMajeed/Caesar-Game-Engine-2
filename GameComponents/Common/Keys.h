#ifndef __Keys__
#define __Keys__

#include <string>

namespace Keys
{
	const static std::string ID    = "_ID";
	const static std::string Class = "_Class";

	namespace ClassType
	{
		const static std::string Object			= "_Object";
		const static std::string Camera			= "_Camera";
		const static std::string Prespective	= "_Prespective";
		const static std::string WindowInfo		= "_WindowInfo";
		const static std::string Light			= "_Light";
	};

	namespace Light
	{
		const static std::string LIGHTTYPE   = "LightType";
		namespace LightTypes
		{
			const static std::string DIRECTIONAL	= "Directional";
			const static std::string POINT			= "Point";
			const static std::string SPOT			= "Spot";
		};
		const static std::string DIFFUSE     = "Diffuse";
		const static std::string AMBIENT     = "Ambient";
		const static std::string SPECULAR    = "Specular";
		const static std::string DIRECTION   = "Direction";
		const static std::string RANGE       = "Range";
		const static std::string ATTENUATION = "Attenuation";
		const static std::string SPOT        = "Spot";
		const static std::string POSITION    = "Position";
		const static std::string HASHADOW    = "HasShadow";
	};

	namespace Window
	{
		const static std::string WIDTH  = "WIDTH";
		const static std::string HEIGHT = "HEIGHT";
		const static std::string HWND   = "HWND";
	};

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
		const static std::string GLOBAL2DTEXTURE    = "Global2DTexture";
		const static std::string GLOBALCUBETEXTURE  = "GlobalCubeTexture";
		const static std::string GLOBALUSERDATA     = "GlobalUserData";
		const static std::string INCLUSIONSTATE     = "InclusionState";
		const static std::string INCLUSIONLIST		= "InclusionList";
	};
	
	namespace BasicDrawable
	{
		const static std::string DRAWABLEOBJ         = "DrawableObj";
		const static std::string MODEL	             = "MODEL";
		const static std::string VERTEXSHADERFILE    = "VertexShaderFile";
		const static std::string PIXELSHADERFILE     = "PixelShaderFile";
		const static std::string GEOMETRYSHADERFILE  = "GeometryShaderFile";
		const static std::string CULLMODE            = "CullMode";
		const static std::string FILLMODE            = "FillMode";
		const static std::string DIMENSION		     = "Dimension";
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
		const static std::string DRAWABLEOBJ    = "DrawableObj";
		const static std::string ANIMATIONOBJ   = "AnimationObj";
		const static std::string ANIMATIONJOINT = "AnimationJoint";
		const static std::string RIGIDBODY      = "RigidBody";
		const static std::string TEXTURE2DOBJ   = "Texture2DObj";
		const static std::string TEXTURECUBEOBJ = "TextureCubeObj";
		const static std::string GROUP			= "Group";
		const static std::string USERDATA		= "UserData";
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
