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

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec3 tangent;
	glm::vec2 texCoord;

	static vk::VertexInputBindingDescription getBindingDescription()
	{
		vk::VertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding                           = 0;
		bindingDescription.stride                            = sizeof(Vertex);
		bindingDescription.inputRate                         = vk::VertexInputRate::eVertex;

		return bindingDescription;
	}

	static std::vector<vk::VertexInputAttributeDescription> getAttributeDescriptions()
	{
		std::vector<vk::VertexInputAttributeDescription> attributeDescriptions;
		attributeDescriptions.resize(5);

		attributeDescriptions[0].binding  = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[0].offset   = offsetof(Vertex, pos);

		attributeDescriptions[1].binding  = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[1].offset   = offsetof(Vertex, normal);

		attributeDescriptions[2].binding  = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[2].offset   = offsetof(Vertex, color);

		attributeDescriptions[3].binding  = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format   = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[3].offset   = offsetof(Vertex, tangent);

		attributeDescriptions[4].binding  = 0;
		attributeDescriptions[4].location = 4;
		attributeDescriptions[4].format   = vk::Format::eR32G32Sfloat;
		attributeDescriptions[4].offset   = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}

	bool operator==(const Vertex& other) const
	{
		return (pos == other.pos && normal == other.normal && color == other.color && texCoord == other.texCoord);
	}
};

namespace std
{
	template <> struct hash<Vertex>
	{
		size_t operator()(Vertex const& vertex) const
		{
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(
				vertex.texCoord) << 1);
		}
	};
}
