// MythTV
#include "vulkan/mythvertexbuffervulkan.h"
#include "vulkan/mythuniformbuffervulkan.h"
#include "vulkan/mythwindowvulkan.h"
#include "vulkan/mythshadersvulkan.h"
#include "visualisations/vulkan/mythvisualmonoscopevulkan.h"

#define LineVertex450    (VK_SHADER_STAGE_VERTEX_BIT   | (1 << 6))
#define LineFragment450  (VK_SHADER_STAGE_FRAGMENT_BIT | (1 << 7))

static const MythBindingMap k450LineBindings = {
    { LineVertex450,
        { VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
        { { 0, { 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT, nullptr } } },
        { 0, 2 * sizeof(float), VK_VERTEX_INPUT_RATE_VERTEX },
        { { 0, 0, VK_FORMAT_R32G32_SFLOAT, 0 } },
        { VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(PushBuffer) } }
    },
    { LineFragment450,
        { VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
        { },
        { },
        { },
        { } }
    }
};

static const MythShaderMap k450LineShaders = {
{
LineVertex450,
{
"#version 450\n"
"#extension GL_ARB_separate_shader_objects : enable\n"
"layout(set = 0, binding = 0) uniform Projection { mat4 projection; } proj;\n"
"layout(push_constant) uniform ComboBuffer {\n"
"    mat4 transform;\n"
"    vec4 color;\n"
"} cb;\n"
"layout(location = 0) in  vec2 fragPosition;\n"
"layout(location = 0) out vec4 fragColor;\n"
"void main() {\n"
"    gl_Position = proj.projection * cb.transform * vec4(fragPosition, 0.0, 1.0);\n"
"    fragColor   = cb.color;\n"
"}\n",
{
0x07230203, 0x00010300, 0x00080008, 0x0000002F,
0x00000000, 0x00020011, 0x00000001, 0x0006000B,
0x00000001, 0x4C534C47, 0x6474732E, 0x3035342E,
0x00000000, 0x0003000E, 0x00000000, 0x00000001,
0x0008000F, 0x00000000, 0x00000004, 0x6E69616D,
0x00000000, 0x0000000D, 0x00000020, 0x0000002A,
0x00030003, 0x00000002, 0x000001C2, 0x00090004,
0x415F4C47, 0x735F4252, 0x72617065, 0x5F657461,
0x64616873, 0x6F5F7265, 0x63656A62, 0x00007374,
0x00040005, 0x00000004, 0x6E69616D, 0x00000000,
0x00060005, 0x0000000B, 0x505F6C67, 0x65567265,
0x78657472, 0x00000000, 0x00060006, 0x0000000B,
0x00000000, 0x505F6C67, 0x7469736F, 0x006E6F69,
0x00070006, 0x0000000B, 0x00000001, 0x505F6C67,
0x746E696F, 0x657A6953, 0x00000000, 0x00070006,
0x0000000B, 0x00000002, 0x435F6C67, 0x4470696C,
0x61747369, 0x0065636E, 0x00070006, 0x0000000B,
0x00000003, 0x435F6C67, 0x446C6C75, 0x61747369,
0x0065636E, 0x00030005, 0x0000000D, 0x00000000,
0x00050005, 0x00000011, 0x6A6F7250, 0x69746365,
0x00006E6F, 0x00060006, 0x00000011, 0x00000000,
0x6A6F7270, 0x69746365, 0x00006E6F, 0x00040005,
0x00000013, 0x6A6F7270, 0x00000000, 0x00050005,
0x00000017, 0x626D6F43, 0x6675426F, 0x00726566,
0x00060006, 0x00000017, 0x00000000, 0x6E617274,
0x726F6673, 0x0000006D, 0x00050006, 0x00000017,
0x00000001, 0x6F6C6F63, 0x00000072, 0x00030005,
0x00000019, 0x00006263, 0x00060005, 0x00000020,
0x67617266, 0x69736F50, 0x6E6F6974, 0x00000000,
0x00050005, 0x0000002A, 0x67617266, 0x6F6C6F43,
0x00000072, 0x00050048, 0x0000000B, 0x00000000,
0x0000000B, 0x00000000, 0x00050048, 0x0000000B,
0x00000001, 0x0000000B, 0x00000001, 0x00050048,
0x0000000B, 0x00000002, 0x0000000B, 0x00000003,
0x00050048, 0x0000000B, 0x00000003, 0x0000000B,
0x00000004, 0x00030047, 0x0000000B, 0x00000002,
0x00040048, 0x00000011, 0x00000000, 0x00000005,
0x00050048, 0x00000011, 0x00000000, 0x00000023,
0x00000000, 0x00050048, 0x00000011, 0x00000000,
0x00000007, 0x00000010, 0x00030047, 0x00000011,
0x00000002, 0x00040047, 0x00000013, 0x00000022,
0x00000000, 0x00040047, 0x00000013, 0x00000021,
0x00000000, 0x00040048, 0x00000017, 0x00000000,
0x00000005, 0x00050048, 0x00000017, 0x00000000,
0x00000023, 0x00000000, 0x00050048, 0x00000017,
0x00000000, 0x00000007, 0x00000010, 0x00050048,
0x00000017, 0x00000001, 0x00000023, 0x00000040,
0x00030047, 0x00000017, 0x00000002, 0x00040047,
0x00000020, 0x0000001E, 0x00000000, 0x00040047,
0x0000002A, 0x0000001E, 0x00000000, 0x00020013,
0x00000002, 0x00030021, 0x00000003, 0x00000002,
0x00030016, 0x00000006, 0x00000020, 0x00040017,
0x00000007, 0x00000006, 0x00000004, 0x00040015,
0x00000008, 0x00000020, 0x00000000, 0x0004002B,
0x00000008, 0x00000009, 0x00000001, 0x0004001C,
0x0000000A, 0x00000006, 0x00000009, 0x0006001E,
0x0000000B, 0x00000007, 0x00000006, 0x0000000A,
0x0000000A, 0x00040020, 0x0000000C, 0x00000003,
0x0000000B, 0x0004003B, 0x0000000C, 0x0000000D,
0x00000003, 0x00040015, 0x0000000E, 0x00000020,
0x00000001, 0x0004002B, 0x0000000E, 0x0000000F,
0x00000000, 0x00040018, 0x00000010, 0x00000007,
0x00000004, 0x0003001E, 0x00000011, 0x00000010,
0x00040020, 0x00000012, 0x00000002, 0x00000011,
0x0004003B, 0x00000012, 0x00000013, 0x00000002,
0x00040020, 0x00000014, 0x00000002, 0x00000010,
0x0004001E, 0x00000017, 0x00000010, 0x00000007,
0x00040020, 0x00000018, 0x00000009, 0x00000017,
0x0004003B, 0x00000018, 0x00000019, 0x00000009,
0x00040020, 0x0000001A, 0x00000009, 0x00000010,
0x00040017, 0x0000001E, 0x00000006, 0x00000002,
0x00040020, 0x0000001F, 0x00000001, 0x0000001E,
0x0004003B, 0x0000001F, 0x00000020, 0x00000001,
0x0004002B, 0x00000006, 0x00000022, 0x00000000,
0x0004002B, 0x00000006, 0x00000023, 0x3F800000,
0x00040020, 0x00000028, 0x00000003, 0x00000007,
0x0004003B, 0x00000028, 0x0000002A, 0x00000003,
0x0004002B, 0x0000000E, 0x0000002B, 0x00000001,
0x00040020, 0x0000002C, 0x00000009, 0x00000007,
0x00050036, 0x00000002, 0x00000004, 0x00000000,
0x00000003, 0x000200F8, 0x00000005, 0x00050041,
0x00000014, 0x00000015, 0x00000013, 0x0000000F,
0x0004003D, 0x00000010, 0x00000016, 0x00000015,
0x00050041, 0x0000001A, 0x0000001B, 0x00000019,
0x0000000F, 0x0004003D, 0x00000010, 0x0000001C,
0x0000001B, 0x00050092, 0x00000010, 0x0000001D,
0x00000016, 0x0000001C, 0x0004003D, 0x0000001E,
0x00000021, 0x00000020, 0x00050051, 0x00000006,
0x00000024, 0x00000021, 0x00000000, 0x00050051,
0x00000006, 0x00000025, 0x00000021, 0x00000001,
0x00070050, 0x00000007, 0x00000026, 0x00000024,
0x00000025, 0x00000022, 0x00000023, 0x00050091,
0x00000007, 0x00000027, 0x0000001D, 0x00000026,
0x00050041, 0x00000028, 0x00000029, 0x0000000D,
0x0000000F, 0x0003003E, 0x00000029, 0x00000027,
0x00050041, 0x0000002C, 0x0000002D, 0x00000019,
0x0000002B, 0x0004003D, 0x00000007, 0x0000002E,
0x0000002D, 0x0003003E, 0x0000002A, 0x0000002E,
0x000100FD, 0x00010038
} } },
{
LineFragment450,
{
"#version 450\n"
"#extension GL_ARB_separate_shader_objects : enable\n"
"layout(location = 0) in  vec4 lineColor;\n"
"layout(location = 0) out vec4 fragColor;\n"
"void main() {\n"
"    fragColor = lineColor;\n"
"}\n",
{
0x07230203, 0x00010300, 0x00080008, 0x0000000D,
0x00000000, 0x00020011, 0x00000001, 0x0006000B,
0x00000001, 0x4C534C47, 0x6474732E, 0x3035342E,
0x00000000, 0x0003000E, 0x00000000, 0x00000001,
0x0007000F, 0x00000004, 0x00000004, 0x6E69616D,
0x00000000, 0x00000009, 0x0000000B, 0x00030010,
0x00000004, 0x00000007, 0x00030003, 0x00000002,
0x000001C2, 0x00090004, 0x415F4C47, 0x735F4252,
0x72617065, 0x5F657461, 0x64616873, 0x6F5F7265,
0x63656A62, 0x00007374, 0x00040005, 0x00000004,
0x6E69616D, 0x00000000, 0x00050005, 0x00000009,
0x67617266, 0x6F6C6F43, 0x00000072, 0x00050005,
0x0000000B, 0x656E696C, 0x6F6C6F43, 0x00000072,
0x00040047, 0x00000009, 0x0000001E, 0x00000000,
0x00040047, 0x0000000B, 0x0000001E, 0x00000000,
0x00020013, 0x00000002, 0x00030021, 0x00000003,
0x00000002, 0x00030016, 0x00000006, 0x00000020,
0x00040017, 0x00000007, 0x00000006, 0x00000004,
0x00040020, 0x00000008, 0x00000003, 0x00000007,
0x0004003B, 0x00000008, 0x00000009, 0x00000003,
0x00040020, 0x0000000A, 0x00000001, 0x00000007,
0x0004003B, 0x0000000A, 0x0000000B, 0x00000001,
0x00050036, 0x00000002, 0x00000004, 0x00000000,
0x00000003, 0x000200F8, 0x00000005, 0x0004003D,
0x00000007, 0x0000000C, 0x0000000B, 0x0003003E,
0x00000009, 0x0000000C, 0x000100FD, 0x00010038
} } }
};

MythVisualMonoScopeVulkan::MythVisualMonoScopeVulkan(AudioPlayer *Audio, MythRender *Render, bool Fade)
  : VideoVisualMonoScope(Audio, Render, Fade),
    MythVulkanObject(dynamic_cast<MythRenderVulkan*>(Render))
{
    m_needsPrepare = true;
}

MythVisualMonoScopeVulkan::~MythVisualMonoScopeVulkan()
{
    MythVisualMonoScopeVulkan::TearDown();
}

void MythVisualMonoScopeVulkan::Prepare(const QRect &Area)
{
    if (!Initialise(Area))
        return;

    UpdateTime();

    // Rotate the vertex buffers and state
    if (m_fade)
    {
        // fade away...
        float fade = 1.0F - (m_rate / 150.0F);
        float zoom = 1.0F - (m_rate / 4000.0F);
        for (auto & state : m_vertexBuffers)
        {
            state.second[1] *= fade;
            state.second[2] *= zoom;
        }

        // drop oldest
        auto vertex = m_vertexBuffers.front();
        m_vertexBuffers.pop_front();
        m_vertexBuffers.append(vertex);
    }

    // Update the newest vertex buffer
    auto & vertex = m_vertexBuffers.back();
    vertex.second[0] = m_hue;
    vertex.second[1] = 1.0;
    vertex.second[2] = 1.0;
    auto * buffer = vertex.first->GetMappedMemory();
    UpdateVertices(static_cast<float*>(buffer));
    vertex.first->Update(nullptr);
}

void MythVisualMonoScopeVulkan::Draw(const QRect& Area, MythPainter* /*Painter*/, QPaintDevice* /*Device*/)
{
    if (!Initialise(Area))
        return;

    // Retrieve current command buffer
    auto currentcmdbuf = m_vulkanWindow->currentCommandBuffer();

    // Bind our pipeline and retrieve layout
    m_vulkanFuncs->vkCmdBindPipeline(currentcmdbuf, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
    auto layout = m_vulkanShader->GetPipelineLayout();

    // Bind projection descriptor set
    m_vulkanFuncs->vkCmdBindDescriptorSets(currentcmdbuf, VK_PIPELINE_BIND_POINT_GRAPHICS,
                                               layout, 0, 1, &m_projectionDescriptor, 0, nullptr);

    // Iterate over vertex buffers - vertex buffers run oldest to newest, which
    // ensures rendering is correct
    float centrex = m_area.left() + m_area.width() / 2;
    float centrey = m_area.top() + m_area.height() / 2;

    for (auto & vertex : m_vertexBuffers)
    {
        // Bind vertex buffer
        VkDeviceSize offset = 0;
        VkBuffer vbos { vertex.first->GetBuffer() };
        m_vulkanFuncs->vkCmdBindVertexBuffers(currentcmdbuf, 0, 1, &vbos, &offset);

        // Set line width
        m_vulkanFuncs->vkCmdSetLineWidth(currentcmdbuf,
                std::clamp(m_lineWidth * vertex.second[2], 1.0F, m_maxLineWidth));

        // Push colour and transform
        QMatrix4x4 transform;
        if (m_fade)
        {
            transform.translate(centrex, centrey);
            transform.scale(vertex.second[2]);
            transform.translate(-centrex, -centrey);
        }

        auto color = QColor::fromHsvF(static_cast<qreal>(vertex.second[0]), 1.0,
                                      static_cast<qreal>(vertex.second[1]));

        memcpy(&m_pushBuffer.transform[0], transform.constData(), sizeof(float) * 16);
        m_pushBuffer.color[0] = static_cast<float>(color.redF());
        m_pushBuffer.color[1] = static_cast<float>(color.greenF());
        m_pushBuffer.color[2] = static_cast<float>(color.blueF());
        m_pushBuffer.color[3] = static_cast<float>(color.alphaF());

        m_vulkanFuncs->vkCmdPushConstants(currentcmdbuf, layout, VK_SHADER_STAGE_VERTEX_BIT,
                                          0, sizeof(PushBuffer), &m_pushBuffer);

        // Draw
        m_vulkanFuncs->vkCmdDraw(currentcmdbuf, NUM_SAMPLES, 1, 0, 0);
    }
}

MythRenderVulkan* MythVisualMonoScopeVulkan::Initialise(const QRect& Area)
{
    if (m_disabled)
        return nullptr;

    if (!IsValidVulkan())
        return nullptr;

    if ((Area == m_area) && m_vulkanShader && m_pipeline &&
        m_projectionUniform && m_descriptorPool && m_projectionDescriptor &&
        !m_vertexBuffers.empty())
    {
        return m_vulkanRender;
    }

    TearDown();
    InitCommon(Area);

    // Check wideLines support
    // N.B. This still fails validation on Mesa for some reason
    if (m_vulkanRender->GetPhysicalDeviceFeatures().wideLines)
    {
        m_maxLineWidth = m_vulkanRender->GetPhysicalDeviceLimits().lineWidthRange[1];
    }
    else
    {
        m_lineWidth = 1.0;
        m_maxLineWidth = 1.0;
    }

    // Create line shader
    std::vector<int> stages = { LineVertex450, LineFragment450 };
    m_vulkanShader = MythShaderVulkan::Create(this, stages, &k450LineShaders, &k450LineBindings);
    if (!m_vulkanShader)
        return nullptr;

    // Create pipeline
    std::vector<VkDynamicState> linewidth { VK_DYNAMIC_STATE_LINE_WIDTH };
    QRect viewport(QPoint{0, 0}, m_vulkanWindow->swapChainImageSize());
    m_pipeline = m_vulkanRender->CreatePipeline(m_vulkanShader, viewport, linewidth);

    // Create projection uniform
    m_projectionUniform = MythUniformBufferVulkan::Create(this, sizeof(float) * 16);
    if (!m_projectionUniform)
        return nullptr;

    // Set projection
    QMatrix4x4 projection;
    projection.setToIdentity();
    projection.ortho(viewport);
    projection = m_vulkanWindow->clipCorrectionMatrix() * projection;
    m_projectionUniform->Update(projection.data());

    // Create descriptor pool
    const auto & sizes = m_vulkanShader->GetPoolSizes(0);
    VkDescriptorPoolCreateInfo pool { VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, nullptr,
                                      0, 1, static_cast<uint32_t>(sizes.size()), sizes.data() };
    if (m_vulkanFuncs->vkCreateDescriptorPool(m_vulkanDevice, &pool, nullptr, &m_descriptorPool) != VK_SUCCESS)
    {
        LOG(VB_GENERAL, LOG_ERR, DESC + "Failed to create descriptor pool for projection");
        return nullptr;
    }

    // Create descriptor
    auto layout = m_vulkanShader->GetDescSetLayout(0);
    VkDescriptorSetAllocateInfo alloc { };
    alloc.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    alloc.descriptorPool = m_descriptorPool;
    alloc.descriptorSetCount = 1;
    alloc.pSetLayouts = &layout;

    if (m_vulkanFuncs->vkAllocateDescriptorSets(m_vulkanDevice, &alloc,
                                                    &m_projectionDescriptor) != VK_SUCCESS)
    {
        LOG(VB_GENERAL, LOG_INFO, DESC + "Failed to allocate projection descriptor set");
        return nullptr;
    }

    // Update descriptor
    auto buffdesc = m_projectionUniform->GetBufferInfo();
    VkWriteDescriptorSet write { };
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = m_projectionDescriptor;
    write.dstBinding = 0;
    write.dstArrayElement = 0;
    write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write.descriptorCount = 1;
    write.pBufferInfo = &buffdesc;
    m_vulkanFuncs->vkUpdateDescriptorSets(m_vulkanDevice, 1, &write, 0, nullptr);

    // Create vertex buffer(s)
    int size = m_fade ? 8 : 1;
    while (m_vertexBuffers.size() < size)
        m_vertexBuffers.push_back({MythBufferVulkan::Create(this, sizeof(float) * NUM_SAMPLES * 2), { }});

    if (m_vertexBuffers.size() == size)
        return m_vulkanRender;
    return nullptr;
}

void MythVisualMonoScopeVulkan::TearDown()
{
    if (IsValidVulkan())
    {
        m_vulkanFuncs->vkDestroyPipeline(m_vulkanDevice, m_pipeline, nullptr);
        m_vulkanFuncs->vkDestroyDescriptorPool(m_vulkanDevice, m_descriptorPool, nullptr);
    }

    delete m_projectionUniform;
    delete m_vulkanShader;
    for (auto & vertex : m_vertexBuffers)
        delete vertex.first;

    m_pipeline = nullptr;
    m_projectionDescriptor = nullptr; // destroyed with pool
    m_descriptorPool = nullptr;
    m_projectionUniform = nullptr;
    m_vertexBuffers.clear();
    m_vulkanShader = nullptr;
}

