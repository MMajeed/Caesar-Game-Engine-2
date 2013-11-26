#ifndef __Keys__
#define __Keys__

#include <string>

namespace Keys
{
	const static std::string ID = "_ID";
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
		const static std::string LIGHTTYPE = "LightType";
		namespace LightTypes
		{
			const static std::string DIRECTIONAL	= "Directional";
			const static std::string POINT			= "Point";
			const static std::string SPOT			= "Spot";
		};
		const static std::string DIFFUSE = "Diffuse";
		const static std::string AMBIENT = "Ambient";
		const static std::string SPECULAR = "Specular";
		const static std::string DIRECTION = "Direction";
		const static std::string RANGE = "Range";
		const static std::string ATTENUATION = "Attenuation";
		const static std::string SPOT = "Spot";
		const static std::string POSITION = "Position";
		const static std::string HASHADOW = "HasShadow";
	};

	namespace Window
	{
		const static std::string WIDTH = "WIDTH";
		const static std::string HEIGHT = "HEIGHT";
		const static std::string HWND = "HWND";
	};

	namespace Camera
	{
		const static std::string EYE = "Eye";
		const static std::string TARGETMAGNITUDE = "TargetMagnitude";
		const static std::string UP = "Up";
		const static std::string RADIANROLL = "RadianRoll";
		const static std::string RADIANPITCH = "RadianPitch";
		const static std::string RADIANYAW = "RadianYaw";
	};

	namespace Prespective
	{
		const static std::string FOVANGLE = "FovAngle";
		const static std::string SCREENWIDTH = "ScreenWidth";
		const static std::string SCREENHEIGHT = "ScreenHeight";
		const static std::string MINVIEWABLE = "MinViewable";
		const static std::string MAXVIEWABLE = "MaxViewable";
	};

	
	namespace BasicDrawable
	{
		const static std::string DRAWABLEOBJ = "DrawableObj";
		const static std::string MODELFILE = "ModelFile";
		const static std::string VERTEXSHADERFILE = "VertexShaderFile";
		const static std::string PIXELSHADERFILE = "PixelShaderFile";
		const static std::string CULLMODE = "CullMode";
		const static std::string FILLMODE = "FillMode";
		const static std::string ANTIALIASEDLINE = "Antialiasedline";
		const static std::string MULTISAMPLEENABLE = "MultisampleEnable";
	};

	namespace BasicTexture
	{
		const static std::string TEXTUREFILE = "TextureFile";
		const static std::string TEXTUREOBJ = "TextureObj";
	}

	namespace ObjectInfo
	{
		const static std::string LOCATION = "Location";
		const static std::string ROTATION = "Rotation";
		const static std::string SCALE = "Scale";
		const static std::string DIFFUSE = "Diffuse";
		const static std::string AMBIENT = "Ambient";
		const static std::string SPECULAR = "Specular";
		const static std::string DRAWABLEOBJ = "DrawableObj";
		const static std::string TEXTURE2DOBJ = "Texture2DObj";
		const static std::string TEXTURECUBEOBJ = "TextureCubeObj";
		const static std::string LIGHT = "Light";
		const static std::string SHADOW = "Shadow";
		const static std::string DEPTH = "Depth";
	};

	namespace ScreenCapture
	{
		const static std::string SCREENCAPTUREOBJ = "ScreenCaptureObj";
		const static std::string WIDTH = "Width";
		const static std::string HEIGHT = "Height";
		const static std::string CAMERAMATRIX = "CameraMatrix";
		const static std::string PRESPECTIVEMATRIX = "PrespectiveMatrix";
		const static std::string EYE = "Eye";
	};

};

#endif //__Keys__
