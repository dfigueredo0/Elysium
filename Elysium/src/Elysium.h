#pragma once

// For use by Elysium applications

#include "Elysium/Core/Core.h"
#include "Elysium/Core/Application.h"
#include "Elysium/Layers/Layer.h"
#include "Elysium/Core/Log.h"

#include "Elysium/Core/Timestep.h"

#include "Elysium/Core/Input.h"
#include "Elysium/Core/KeyCodes.h"

#include "Elysium/ImGui/ImGuiLayer.h"

#pragma region Renderer
#include "Elysium/Renderer/Renderer.h"
#include "Elysium/Renderer/RenderCommand.h"

#include "Elysium/Renderer/Buffer.h"
#include "Elysium/Renderer/Shader.h"
#include "Elysium/Renderer/Texture.h"
#include "Elysium/Renderer/VertexArray.h"

#include "Elysium/Renderer/Camera.h"
#include "Elysium/Renderer/CameraController.h"
#pragma endregion