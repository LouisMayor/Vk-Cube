#pragma once

#include "Settings.h"
#include <memory>

class CubeSettings : public Settings
{
public:
	explicit CubeSettings(bool _use_msaa          = false,
	                      int  _msaa_sample_count = 2)
	{
		use_msaa     = _use_msaa;
		sample_level = _msaa_sample_count;
	}

	~CubeSettings()
	{}

	static CubeSettings* Instance();

	enum class CubeDemos : int
	{
		Textured,
		Shader,
		Lit,
		NumOf
	};

	void SetDemo(CubeDemos _demo)
	{
		if (current_demo == _demo)
		{
			return;
		}

		current_demo = _demo;

		m_updated = SettingUpdateFlags::DescriptorsRecreation | SettingUpdateFlags::SwapchainRecreation;
		OnDemoUpdated.invoke_safe(current_demo);
	}

	std::string ToString(CubeSettings::CubeDemos _val)
	{
		switch (_val)
		{
			case CubeSettings::CubeDemos::Textured:
			{
				return "Textured";
			}
			case CubeSettings::CubeDemos::Shader:
			{
				return "Shader";
			}
			case CubeSettings::CubeDemos::Lit:
			{
				return "Lit";
			}
			default:
			{
				return "Invalid";
			}
		}
	}

	CubeDemos current_demo = CubeDemos::Textured;

	Event<CubeDemos> OnDemoUpdated;

private:
	static std::unique_ptr<CubeSettings> m_instance;
};
