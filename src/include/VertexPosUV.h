#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/hash.hpp>

#include <unordered_map>
#include <array>

#include "VulkanObjects.h"

struct VertexPosUV
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static vk::VertexInputBindingDescription getBindingDescription()
	{
		vk::VertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding                           = 0;
		bindingDescription.stride                            = sizeof(VertexPosUV);
		bindingDescription.inputRate                         = vk::VertexInputRate::eVertex;

		return bindingDescription;
	}

	static std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions()
	{
		std::vector<vk::VertexInputAttributeDescription> attributeDescriptions;
		attributeDescriptions.resize(3);

		attributeDescriptions[0].binding  = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[0].offset   = offsetof(VertexPosUV, pos);

		attributeDescriptions[1].binding  = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[1].offset   = offsetof(VertexPosUV, color);

		attributeDescriptions[2].binding  = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format   = vk::Format::eR32G32Sfloat;
		attributeDescriptions[2].offset   = offsetof(VertexPosUV, texCoord);

		return attributeDescriptions;
	}

	bool operator==(const VertexPosUV& other) const
	{
		return (pos == other.pos && color == other.color && texCoord == other.texCoord);
	}
};

namespace std
{
	template <> struct hash<VertexPosUV>
	{
		size_t operator()(VertexPosUV const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(
				vertex.texCoord) << 1);
		}
	};
}
