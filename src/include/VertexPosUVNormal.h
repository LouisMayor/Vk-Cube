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

struct VertexPosUVNormal
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;
	glm::vec3 normal;

	static vk::VertexInputBindingDescription getBindingDescription()
	{
		vk::VertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding                           = 0;
		bindingDescription.stride                            = sizeof(VertexPosUVNormal);
		bindingDescription.inputRate                         = vk::VertexInputRate::eVertex;

		return bindingDescription;
	}

	static std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions()
	{
		std::vector<vk::VertexInputAttributeDescription> attributeDescriptions;
		attributeDescriptions.resize(4);

		attributeDescriptions[0].binding  = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[0].offset   = offsetof(VertexPosUVNormal, pos);

		attributeDescriptions[1].binding  = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[1].offset   = offsetof(VertexPosUVNormal, color);

		attributeDescriptions[2].binding  = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format   = vk::Format::eR32G32Sfloat;
		attributeDescriptions[2].offset   = offsetof(VertexPosUVNormal, texCoord);

		attributeDescriptions[3].binding  = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[3].offset   = offsetof(VertexPosUVNormal, normal);

		return attributeDescriptions;
	}

	bool operator==(const VertexPosUVNormal& other) const
	{
		return (pos == other.pos && normal == other.normal && color == other.color && texCoord == other.texCoord);
	}
};

namespace std
{
	template <> struct hash<VertexPosUVNormal>
	{
		size_t operator()(VertexPosUVNormal const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(
				vertex.texCoord) << 1);
		}
	};
}
