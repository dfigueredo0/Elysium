#pragma once

#include "Elysium/Core.h"
#include "Elysium/Core/Timestep.h"
#include "Elysium/Events/Event.h"

namespace Elysium {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		// TODO: Establish Macros to def/undef for distribution build
		std::string m_DebugName;
	};
}