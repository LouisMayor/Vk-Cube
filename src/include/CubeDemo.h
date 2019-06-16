#pragma once

#include "Demo.h"
#include "Settings.h"
#include "UI.h"
#include "Model.h"

class VkCubeDemo : public VkDemo
{
public:

	VkCubeDemo() = default;

	explicit VkCubeDemo(const VkApp& _app_instance) : VkDemo(_app_instance)
	{}

	VkCubeDemo(const VkCubeDemo& _other) = delete;

	VkCubeDemo(VkCubeDemo&& _other) noexcept = delete;

	VkCubeDemo& operator=(const VkCubeDemo& _other) = delete;

	VkCubeDemo& operator=(VkCubeDemo&& _other) noexcept = delete;

	~VkCubeDemo() override
	{ }

	void Setup() override;

	void Run() override;

	void Shutdown() override;

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      _message_severity,
	                                                    VkDebugUtilsMessageTypeFlagsEXT             _message_type,
	                                                    const VkDebugUtilsMessengerCallbackDataEXT* _p_callback_data,
	                                                    void*                                       _p_user_data);

private:

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

	VkRes::Swapchain                m_swapchain;
	VkRes::Command                  m_command;
	VkRes::RenderTarget             m_backbuffer;
	VkRes::RenderPass               m_render_pass;
	std::vector<VkRes::FrameBuffer> m_framebuffers;
	VkRes::GraphicsPipeline         m_graphics_pipeline;
	VkRes::Shader                   m_vert;
	VkRes::Shader                   m_frag;
	std::vector<VkRes::Fence>       m_inflight_fences;
	std::vector<VkRes::Semaphore>   m_image_available_semaphores;
	std::vector<VkRes::Semaphore>   m_render_finished_semaphores;

	std::vector<Model> m_render_list;

	UI m_ui_instance;

	float m_total_time;
	float m_frame_delta;

	bool m_settings_updated = false;
};
