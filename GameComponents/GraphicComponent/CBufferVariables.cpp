#include "CBufferVariables.h"

#include "XNAConverter.h"
#include <Windows.h>
#include <xnamath.h>
#include <Logger.h>

CBufferVariables::CBufferVariables(std::vector<char>& bytes, const unsigned int StartOffset)
	: bytes(bytes), StartOffset(StartOffset)
{
}
