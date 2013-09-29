#ifndef __Keys__
#define __Keys__

#include <string>

namespace Keys
{
	namespace ClassType
	{
		const static std::string Object			= "_Object";
		const static std::string Camera			= "_Camera";
		const static std::string Prespective	= "_Prespective";
		const static std::string WindowInfo		= "_WindowInfo";
		const static std::string Light			= "_Light";
	};

	const static std::string ID					= "_ID";
	const static std::string Class				= "_Class";
	const static std::string LOCATION			= "Location";
	const static std::string ROTATION			= "Rotation";
	const static std::string SCALE				= "Scale";
	const static std::string DIFFUSE			= "Diffuse";
	const static std::string AMBIENT			= "Ambient";
	const static std::string SPECULAR			= "Specular";
	const static std::string GRAPHICDRAWABLEID	= "GraphicDrawableID";
	const static std::string EYE				= "Eye";
	const static std::string TARGETMAGNITUDE	= "TargetMagnitude";
	const static std::string UP					= "Up";
	const static std::string RADIANROLL			= "RadianRoll";
	const static std::string RADIANPITCH		= "RadianPitch";
	const static std::string RADIANYAW			= "RadianYaw";
	const static std::string FOVANGLE			= "FovAngle";
	const static std::string SCREENWIDTH		= "ScreenWidth";
	const static std::string SCREENHEIGHT		= "ScreenHeight";
	const static std::string MINVIEWABLE		= "MinViewable";
	const static std::string MAXVIEWABLE		= "MaxViewable";
	const static std::string MODELFILE			= "ModelFile";
	const static std::string VERTEXSHADERFILE	= "VertexShaderFile";
	const static std::string PIXELSHADERFILE	= "PixelShaderFile";
	const static std::string TEXTUREFILE		= "TextureFile";
	const static std::string WIDTH				= "WIDTH";
	const static std::string HEIGHT				= "HEIGHT";
	const static std::string HWND				= "HWND";
};

#endif //__Keys__
