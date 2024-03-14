// Copyright (c) 2024 Dylan Figueredo
// Distributed under the MIT license. See the LICENSE file in the project root for more information
#pragma once
#include "CommonHeaders.h"

namespace elysium::math {
	constexpr float pi = 3.1415926535897932384626433832795f;
	constexpr float epsilon = 1e-5f;

#if defined(_WIN64)
	using v2 = DirectX::XMFLOAT2;
	using v2a = DirectX::XMFLOAT2A;
	using v3 = DirectX::XMFLOAT3;
	using v3a = DirectX::XMFLOAT3A;
	using v4 = DirectX::XMFLOAT4;
	using v4a = DirectX::XMFLOAT4A;
	using uint32_v2 = DirectX::XMUINT2;
	using uint32_v3 = DirectX::XMUINT3;
	using uint32_v4 = DirectX::XMUINT4;
	using int32_v2 = DirectX::XMINT2;
	using int32_v3 = DirectX::XMINT3;
	using int32_v4 = DirectX::XMINT4;
	using m3x3 = DirectX::XMFLOAT3X3;
	using m4x4 = DirectX::XMFLOAT4X4;
	using m4x4a = DirectX::XMFLOAT4X4A;

#endif // defined(_WIN64)

}