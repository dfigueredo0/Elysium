#pragma once

#include "Elysium/Layers/Layer.h"

#include "Elysium/Events/ApplicationEvent.h"
#include "Elysium/Events/MouseEvent.h"
#include "Elysium/Events/KeyEvent.h"

namespace Elysium {
	class ELYSIUM_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender();

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}