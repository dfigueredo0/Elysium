#pragma once

// For use by Elysium applications

#include "Elysium/Core.h"
#include "Elysium/Application.h"
#include "Elysium/Layers/Layer.h"
#include "Elysium/Log.h"

#include "Elysium/Core/Timestep.h"

#include "Elysium/Input.h"
#include "Elysium/KeyCodes.h"

#include "Elysium/ImGui/ImGuiLayer.h"

#pragma region Renderer
#include "Elysium/Renderer/Renderer.h"
#include "Elysium/Renderer/RenderCommand.h"

#include "Elysium/Renderer/Buffer.h"
#include "Elysium/Renderer/Shader.h"
#include "Elysium/Renderer/VertexArray.h"

#include "Elysium/Renderer/Camera.h"
#pragma endregion

#pragma region Entry Point
#include "Elysium/EntryPoint.h"
#pragma endregion