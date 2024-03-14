// Copyright (c) 2024 Dylan Figueredo
// Distributed under the MIT license. See the LICENSE file in the project root for more information
#pragma once
#include "ComponentsCommon.h"

namespace elysium::transform {

	struct init_info
	{
		float position[3]{};
		float rotation[4]{};
		float scale[3]{1.f, 1.f, 1.f};
	};

	component create_transform(const init_info& info, game_entity::entity entity);
	void remove_transform(component c);
}