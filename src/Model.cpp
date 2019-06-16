#include "include/Model.h"

extern Logger g_Logger;

void Model::LoadMesh(vk::Device         _device,
                     vk::PhysicalDevice _physical_device,
                     std::string        _dir,
                     std::string        _name)
{
	m_model_directory = _dir;
	m_model_name      = _name;

	m_mesh.Load(_device, _physical_device, _dir, _name, m_materials, m_shapes);

	g_Logger.Info<Model>(*this, "Model Loaded");
}

void Model::LoadTexture(std::string _dir, std::string _name)
{}

void Model::Destroy(vk::Device _device)
{
	m_mesh.Destroy(_device);
}

std::ostream& operator<<(std::ostream& _ostream, const Model& _other)
{
	_ostream << std::endl <<
			"Model name: " << _other.m_model_name << std::endl <<
			"Model directory: " << _other.m_model_directory << std::endl <<
			"Number of vertices " << _other.m_mesh.vertex_count << std::endl <<
			"Number of indices " << _other.m_mesh.index_count << std::endl <<
			"Number of sub-models " << _other.m_shapes.size() << std::endl;

	for (auto& i : _other.m_shapes)
	{
		_ostream << i.name << std::endl;
	}

	return _ostream;
}
