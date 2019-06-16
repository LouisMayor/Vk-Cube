#pragma once

#include "Mesh.h"

#include <string>
#include <variant>

enum class ERenderType
{
	Diffuse,
	DiffuseSpec,
	DiffuseSpecNormal,
	ShaderBased
};

struct ShaderBased
{
	/* Nothing set by the program, all colours set via shader */
};

struct Diffuse
{
	VkRes::Texture<VkRes::ETextureLoader::STB> DiffuseTexture;
};

struct DiffuseSpec
{
	VkRes::Texture<VkRes::ETextureLoader::STB> DiffuseTexture;
	VkRes::Texture<VkRes::ETextureLoader::STB> SpecularTexture;
};

struct DiffuseSpecNormal
{
	VkRes::Texture<VkRes::ETextureLoader::STB> DiffuseTexture;
	VkRes::Texture<VkRes::ETextureLoader::STB> SpecularTexture;
	VkRes::Texture<VkRes::ETextureLoader::STB> NormalTexture;
};

class Model
{
public:

	Model() = default;

	void Destroy(vk::Device);

	template <ERenderType render_type> void SetTextureSupport()
	{
		if constexpr (render_type == ERenderType::Diffuse)
		{
			m_textures = Diffuse();
		}
		else if constexpr (render_type == ERenderType::DiffuseSpec)
		{
			m_textures = DiffuseSpec();
		}
		else if constexpr (render_type == ERenderType::DiffuseSpecNormal)
		{
			m_textures = DiffuseSpecNormal();
		}
	}

	void LoadMesh(vk::Device, vk::PhysicalDevice, std::string, std::string);

	void LoadTexture(std::string, std::string);

	friend std::ostream& operator<<(std::ostream& _ostream, const Model& _other);

	Mesh& MeshInstance()
	{
		return m_mesh;
	}

private:

	std::string m_model_directory;
	std::string m_model_name;

	Mesh                                                  m_mesh;
	std::variant<Diffuse, DiffuseSpec, DiffuseSpecNormal> m_textures;

	std::vector<tinyobj::shape_t> m_shapes;
	std::vector<tinyobj::material_t> m_materials;
};
