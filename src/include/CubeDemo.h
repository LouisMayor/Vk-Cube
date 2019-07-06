#pragma once

#include "Demo.h"
#include "CubeDemoSettings.h"
#include "UI.h"
#include "Model.h"

class VkCubeDemo : public VkDemo
{
public:

	VkCubeDemo();

	explicit VkCubeDemo(const VkApp& _app_instance) : VkDemo(_app_instance)
	{
	}

	VkCubeDemo(const VkCubeDemo& _other) = delete;

	VkCubeDemo(VkCubeDemo&& _other) noexcept = delete;

	VkCubeDemo& operator=(const VkCubeDemo& _other) = delete;

	VkCubeDemo& operator=(VkCubeDemo&& _other) noexcept = delete;

	~VkCubeDemo() override
	{ }

	static VkCubeDemo* Instance();

	void Setup() override;

	void Run() override;

	void Shutdown() override;

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      _message_severity,
	                                                    VkDebugUtilsMessageTypeFlagsEXT             _message_type,
	                                                    const VkDebugUtilsMessengerCallbackDataEXT* _p_callback_data,
	                                                    void*                                       _p_user_data);

	static void ChangeCubeDemo(CubeSettings::CubeDemos);

private:

	void SetActiveShaders(CubeSettings::CubeDemos);

	void RecreateActivePipeline();

	void RecreateDescriptors();

	void CreateDescriptorLayouts() override;

	void CreateDescriptorPools() override;

	void CreateDescriptorSets() override;

	void CreateResources() override;

	void UpdateBufferData(uint32_t, bool) override;

	void LoadAssets() override;

	void SubmitQueue() override;

	void CreateSyncObjects() override;

	void RecordCmdBuffer() override;

	void CreateSwapchain() override;

	void CreateShaders() override;

	void CreateCmdPool() override;

	void CreateRenderPasses() override;

	void CreateFrameBuffers() override;

	void CreatePipelines() override;

	void CreateColourResources() override;

	void CreateDepthResources() override;

	void CleanSwapchain() override;

	void RecreateSwapchain() override;

	void CreateCmdBuffers() override;

	struct CubeData
	{
		glm::mat4x4 mvp;
		glm::mat4x4 world;
	};

	struct TimeData
	{
		float timer;
	};

	struct ViewportData
	{
		glm::vec2 dims;
	};

	struct DirectionalLight
	{
		glm::vec3 direction;
	};

	VkRes::Shader* active_vert;
	VkRes::Shader* active_frag;

	VkRes::GraphicsPipeline         m_non_lit_graphics_pipeline;
	VkRes::Shader                   m_non_lit_vert;
	VkRes::Shader                   m_non_lit_frag;
	VkRes::Shader                   m_non_lit_tex_vert;
	VkRes::Shader                   m_non_lit_tex_frag;

	VkRes::GraphicsPipeline         m_lit_graphics_pipeline;
	VkRes::Shader                   m_lit_vert;
	VkRes::Shader                   m_lit_frag;

	VkRes::Swapchain                m_swapchain;
	VkRes::Command                  m_command;
	VkRes::DepthBuffer              m_depth_buffer;
	VkRes::RenderTarget             m_backbuffer;
	VkRes::RenderPass               m_render_pass;
	VkRes::DescriptorSetLayout      m_desc_set_layouts;
	VkRes::DescriptorPool           m_desc_pool;
	VkRes::DescriptorSet            m_desc_sets;
	std::vector<VkRes::FrameBuffer> m_framebuffers;
	std::vector<VkRes::Fence>       m_inflight_fences;
	std::vector<VkRes::Semaphore>   m_image_available_semaphores;
	std::vector<VkRes::Semaphore>   m_render_finished_semaphores;

	VkRes::Sampler<vk::Filter::eLinear>                                  m_sampler;
	VkRes::UniformBuffer<DirectionalLight, VkRes::EDataUsageFlags::Once> m_dir_light_ubo;
	VkRes::UniformBuffer<ViewportData, VkRes::EDataUsageFlags::OnResize> m_view_ubo;
	VkRes::UniformBuffer<CubeData, VkRes::EDataUsageFlags::PerFrame>     m_cube_ubo;
	std::vector<Model>                                                   m_render_list;

	UI m_ui_instance;

	static VkCubeDemo* m_instance;

	float m_total_time;
	float m_frame_delta;

	std::string m_non_lit_texture_vert = "Tranform_tex.vert";
	std::string m_non_lit_texture_frag = "unlit_tex.frag";

	std::string m_shader_vert = "Tranform.vert";
	std::string m_shader_frag = "unlit.frag";

	std::string m_tex_lit_vert = "forward_Tranform_tex.vert";
	std::string m_tex_lit_frag = "forward_tex.frag";

	Settings::SettingUpdateFlags m_settings_updated = Settings::SettingUpdateFlags::None;
};
