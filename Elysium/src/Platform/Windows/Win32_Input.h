#pragma once

#include "Elysium/Input.h"

namespace Elysium {
	/* The polymorphism is not necessary here (neither in the window class). The platform will not be decided at runtime, it's known at compile time. So no need at all for runtime polymorphism.
		what he could do (and would be better) is to make an implementation class for every supported platform and include the correct one through the preprocessor.
		That has zero overhead (virtual functions do have overhead) and the code is simpler.
	*/
	class Win32_Input : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}
