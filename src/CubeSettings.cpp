#include "include/CubeDemoSettings.h"

std::unique_ptr<CubeSettings> CubeSettings::m_instance = std::make_unique<CubeSettings>();

CubeSettings* CubeSettings::Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::make_unique<CubeSettings>();
	}

	return m_instance.get();
}
