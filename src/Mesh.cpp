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

void Mesh::MapData(vk::Device _device, int _shape_count)
{
	for(int index = 0; index < _shape_count; ++index)
	{
		auto vert = m_vertex_buffer[index];
		auto indi = m_index_buffer[index];

		vert.Map(_device);
		std::memcpy(vert.Data(), m_vertices[0].data(), m_vertices[0].size() * sizeof(VertexPosUVNormal));
		vert.Unmap(_device);

		indi.Map(_device);
		std::memcpy(indi.Data(), m_indices[0].data(), m_indices[0].size() * sizeof(int));
		indi.Unmap(_device);
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

	std::unordered_map<VertexPosUVNormal, uint32_t> unique_vertices = {};

	m_vertices.resize(_shapes.size());
	m_indices.resize(_shapes.size());

	int shape_counter = 0;
	for (const auto& shape : _shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			VertexPosUVNormal vertex = {};

			if (index.vertex_index != -1)
			{
				vertex.pos =
				{
					attrib.vertices[3 * index.vertex_index + 2],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 0]
				};
			}

			vertex.color = { 1.0f, 1.0f, 1.0f };

			if (index.texcoord_index != -1)
			{
				vertex.texCoord =
				{
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}

			if (index.normal_index != -1)
			{
				vertex.normal =
				{
					attrib.normals[3 * index.normal_index + 2],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 0]
				};
			}

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
		m_vertex_buffer[i] = VkRes::Buffer(_device, _physical_device, m_vertices[0].size() * sizeof(VertexPosUVNormal), vk::BufferUsageFlagBits::eVertexBuffer);
		m_index_buffer[i] = VkRes::Buffer(_device, _physical_device, m_indices[0].size() * sizeof(int), vk::BufferUsageFlagBits::eIndexBuffer);
	}

	MapData(_device, _shapes.size());
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
