#include "GenerateGUID.h"
#include "Converter.h"
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

std::string CHL::GenerateGUID()
{
	return CHL::ToString(boost::uuids::random_generator()());
}
