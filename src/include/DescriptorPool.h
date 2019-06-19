#pragma once

#include "unordered_map"

namespace VkRes
{
	class DescriptorPool
	{
	public:
		DescriptorPool() = default;

		void CreatePool(vk::Device _device, uint32_t _max_sets)
		{
			if (m_desc_types.empty())
			{
				throw std::logic_error("DescriptorPool has no values");
			}

			std::vector<vk::DescriptorPoolSize> pool_data(m_desc_types.size());

			const auto value_selector = [](auto pair)
			{
				return pair.second;
			};

			std::transform(m_desc_types.begin(), m_desc_types.end(), pool_data.begin(), value_selector);

			const vk::DescriptorPoolCreateInfo create_info =
			{
				{},
				_max_sets,
				pool_data.size(),
				pool_data.data()
			};

			const auto result = _device.createDescriptorPool(&create_info, nullptr, &m_pool);
			assert(("Failed to create a descriptor pool", result == vk::Result::eSuccess));
		}

		void Add(vk::DescriptorType _type, uint32_t _index)
		{
			m_desc_types[_index] = _type;
		}

		void Remove(uint32_t _index)
		{
			m_desc_types.erase(_index);
		}

		[[nodiscard]] vk::DescriptorPool& Get()
		{
			return m_pool;
		}

	private:
		vk::DescriptorPool                               m_pool;
		std::unordered_map<uint32_t, vk::DescriptorType> m_desc_types;
	};
}
