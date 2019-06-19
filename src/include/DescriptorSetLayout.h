#pragma once

namespace VkRes
{
	class DescriptorSetLayout
	{
	public:
		DescriptorSetLayout() = default;

		void CreateLayouts(vk::Device _device)
		{
			const vk::DescriptorSetLayoutCreateInfo create_info =
			{
				{},
				m_layout_bindings.size(),
				m_layout_bindings.data()
			};

			if (m_layout_bindings.size() > 0)
			{
				const auto result = _device.createDescriptorSetLayout(&create_info, nullptr, &m_layout);
				assert(("Failed to create a descriptor set layout", result == vk::Result::eSuccess));
			}
			else
			{
				throw std::logic_error("DescriptorSetLayout has no values");
			}
		}

		void Add(vk::DescriptorSetLayoutBinding _layout)
		{
			m_layout_bindings.emplace_back(_layout);
		}

		void Remove(vk::DescriptorSetLayoutBinding _layout)
		{
			m_layout_bindings.erase(std::remove(m_layout_bindings.begin(), m_layout_bindings.end(), _layout));
			m_layout_bindings.shrink_to_fit();
		}

		[[nodiscard]] vk::DescriptorSetLayout& Get()
		{
			return m_layout;
		}

	private:
		vk::DescriptorSetLayout                     m_layout;
		std::vector<vk::DescriptorSetLayoutBinding> m_layout_bindings;
	};
}
