// macro 'TINYOBJLOADER_IMPLEMENTATION' defined in CubeDemo.cpp

#include "include/Mesh.h"

void Mesh::Destroy(vk::Device _device)
{
	for (auto &i : m_vertex_buffer)
	{
		i.Destroy(_device);
	}

	for (auto& i : m_index_buffer)
	{
		i.Destroy(_device);
	}
}

void Mesh::Load(vk::Device                        _device,
                vk::PhysicalDevice                _physical_device,
                std::string                       _dir,
                std::string                       _name,
                std::vector<tinyobj::material_t>& _materials,
                std::vector<tinyobj::shape_t>&    _shapes)
{
	tinyobj::attrib_t attrib;
	std::string       err;
	std::string       location = (_dir + _name);

	if (!tinyobj::LoadObj(&attrib, &_shapes, &_materials, &err, location.c_str(), ""))
	{
		throw std::runtime_error(err);
	}

	std::unordered_map<Vertex, uint32_t> unique_vertices = {};

	m_vertices.resize(_shapes.size());
	m_indices.resize(_shapes.size());

	int shape_counter = 0;
	for (const auto& shape : _shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			Vertex vertex = {};

			if (index.vertex_index != -1)
			{
				vertex.pos =
				{
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};
			}

			if (index.normal_index != -1)
			{
				vertex.normal =
				{
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]
				};
			}

			if (index.texcoord_index != -1)
			{
				vertex.texCoord =
				{
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}

			vertex.color = {1.0f, 1.0f, 1.0f};

			if (unique_vertices.count(vertex) == 0)
			{
				unique_vertices[vertex] = static_cast<uint32_t>(m_vertices[shape_counter].size());
				m_vertices[shape_counter].push_back(vertex);
			}

			m_indices[shape_counter].push_back(unique_vertices[vertex]);
		}
		shape_counter++;
	}

	for (auto& buffer : m_vertices)
	{
		vertex_count += buffer.size();
	}

	for (auto& buffer : m_indices)
	{
		index_count += buffer.size();
	}

	m_vertex_buffer.resize(_shapes.size());
	m_index_buffer.resize(_shapes.size());

	for (size_t i = 0; i < _shapes.size(); i++)
	{
		m_vertex_buffer[i] = VkRes::Buffer(_device, _physical_device, sizeof(m_vertices[0]) * m_vertices.size(), vk::BufferUsageFlagBits::eVertexBuffer);
		m_index_buffer[i] = VkRes::Buffer(_device, _physical_device, sizeof(m_indices[0]) * m_indices.size(), vk::BufferUsageFlagBits::eIndexBuffer);
	}	
}

void Mesh::Draw(vk::CommandBuffer _cmd_buffer)
{
	for (size_t i = 0; i < m_vertex_buffer.size(); i++)
	{
		vk::DeviceSize offsets[] = { 0 };
		_cmd_buffer.bindVertexBuffers(0, 1, &m_vertex_buffer[i].BufferData(), offsets);
		_cmd_buffer.bindIndexBuffer(m_index_buffer[i].BufferData(), 0, vk::IndexType::eUint32);
		const int num_of_indices = static_cast<uint32_t>(m_indices[i].size());
		_cmd_buffer.drawIndexed(num_of_indices, 1, 0, 0, 0);
	}
}
