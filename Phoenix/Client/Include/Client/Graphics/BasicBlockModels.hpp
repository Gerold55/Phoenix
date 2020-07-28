// Copyright 2019-20 Genten Studios
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

/**
 * @file ChunkMesher.hpp
 * @brief The mesher class for use with chunks.
 *
 * @copyright Copyright (c) 2019-20 Genten Studios
 */

#pragma once

#include <Common/Math/Math.hpp>

namespace phx
{
	struct Vertex
	{
		math::vec3 pos;
		math::vec2 uv;
		math::vec3 normal;
	};
}

// clang-format off
static const phx::Vertex vertBlock[] = {
	// front (north)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 0, -1)},

	// left (west)
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1, 0, 0)},

	// back (south)
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, 1)},

	// right (east)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1, 0, 0)},

	// top
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, 0)},

	// bottom
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, -1, 0)},
};

static const phx::Vertex vertSlab[] = {
	// front (north)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 0, -1)},

	// left (west)
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(-1, 0, 0)},

	// back (south)
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, 1)},

	// right (east)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(1, 0, 0)},

	// top
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, 0)},

	// bottom
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, -1, 0)},
};

static const phx::Vertex vertStair[] = {
	// front (north)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 0, -1)},

	// left (west)
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(-1, 0, 0)},

	// back (south)
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, 1)},

	// right (east)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(1, 0, 0)},

	// top
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  0.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  0.f,  0.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  0.f,  0.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  0.f,  0.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  0.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, 1, 0)},

	// bottom
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f),  phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f),  phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(0, -1, 0)},

	// upper back

	// front (north)
    {phx::math::vec3(-1.f,  0.f,  0.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  0.f,  0.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  1.f,  0.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  1.f,  0.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f,  1.f,  0.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f,  0.f,  0.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, -1)},

	// left (west)
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  1.f,  0.f), phx::math::vec2(0.5f, 1.f),  phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  0.f,  0.f), phx::math::vec2(0.5f, 0.5f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  0.f,  0.f), phx::math::vec2(0.5f, 0.5f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(-1, 0, 0)},

	// back (south)
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(0, 0, 1)},

	// right (east)
    {phx::math::vec3(-1.f,  0.f,  0.f), phx::math::vec2(0.5f, 0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f,  0.f), phx::math::vec2(0.5f, 1.f),  phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f,  1.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  0.f,  0.f), phx::math::vec2(0.5f, 0.5f), phx::math::vec3(1, 0, 0)},

	// top
    {phx::math::vec3(-1.f,  1.f,  0.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f,  0.f), phx::math::vec2(0.f,  0.5f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f),  phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f),  phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  1.f,  0.f), phx::math::vec2(1.f,  0.5f), phx::math::vec3(0, 1, 0)},

	// don't need a bottom.
};

static const phx::Vertex vertSlope[] = {
	// front (north)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, -1)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 1, -1)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, -1)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, -1)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 1, -1)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, -1)},

	// left (west)
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1, 0, 0)},

	// back (south)
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, 1)},

	// right (east)
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1, 0, 0)},

	// no top, front is the slope.

	// bottom
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, -1, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, -1, 0)},
};

static const phx::Vertex vertXPan[] = {
	// east-facing front
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1.f, 0.f, -1.f)},

	// back of east-facing
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1.f, 0.f, 1.f)},

	// west-facing front
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(1.f, 0.f, -1.f)},

	// back of west-facing
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(-1.f, 0.f, 1.f)},
};

static const phx::Vertex vertXPanBlock[] = {
    // east-facing front
    {phx::math::vec3(-1.75f, -1.75f, -1.75f), phx::math::vec2(1.f, 0.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.75f, -1.75f,  1.75f), phx::math::vec2(0.f, 0.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.75f,  1.75f,  1.75f), phx::math::vec2(0.f, 1.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.75f,  1.75f,  1.75f), phx::math::vec2(0.f, 1.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.75f,  1.75f, -1.75f), phx::math::vec2(1.f, 1.f), phx::math::vec3(-1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.75f, -1.75f, -1.75f), phx::math::vec2(1.f, 0.f), phx::math::vec3(-1.f, 0.f, -1.f)},

    // back of east-facing
    {phx::math::vec3( 1.75f,  1.75f,  1.75f), phx::math::vec2(1.f, 1.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.75f, -1.75f,  1.75f), phx::math::vec2(1.f, 0.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.75f, -1.75f, -1.75f), phx::math::vec2(0.f, 0.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.75f, -1.75f, -1.75f), phx::math::vec2(0.f, 0.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.75f,  1.75f, -1.75f), phx::math::vec2(0.f, 1.f), phx::math::vec3(1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.75f,  1.75f,  1.75f), phx::math::vec2(1.f, 1.f), phx::math::vec3(1.f, 0.f, 1.f)},

    // west-facing front
    {phx::math::vec3(-1.75f, -1.75f,  1.75f), phx::math::vec2(1.f, 0.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.75f, -1.75f, -1.75f), phx::math::vec2(0.f, 0.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.75f,  1.75f, -1.75f), phx::math::vec2(0.f, 1.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3( 1.75f,  1.75f, -1.75f), phx::math::vec2(0.f, 1.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.75f,  1.75f,  1.75f), phx::math::vec2(1.f, 1.f), phx::math::vec3(1.f, 0.f, -1.f)},
    {phx::math::vec3(-1.75f, -1.75f,  1.75f), phx::math::vec2(1.f, 0.f), phx::math::vec3(1.f, 0.f, -1.f)},

    // back of west-facing
    {phx::math::vec3( 1.75f,  1.75f, -1.75f), phx::math::vec2(1.f, 1.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.75f, -1.75f, -1.75f), phx::math::vec2(1.f, 0.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.75f, -1.75f,  1.75f), phx::math::vec2(0.f, 0.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.75f, -1.75f,  1.75f), phx::math::vec2(0.f, 0.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3(-1.75f,  1.75f,  1.75f), phx::math::vec2(0.f, 1.f), phx::math::vec3(-1.f, 0.f, 1.f)},
    {phx::math::vec3( 1.75f,  1.75f, -1.75f), phx::math::vec2(1.f, 1.f), phx::math::vec3(-1.f, 0.f, 1.f)},

	// front (north)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, -1)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 0, -1)},

	// left (west)
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(-1, 0, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(-1, 0, 0)},

	// back (south)
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 0, 1)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 0, 1)},

	// right (east)
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(1, 0, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(1, 0, 0)},

	// top
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f,  1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f,  1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, 0)},

	// bottom
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f, -1.f, -1.f), phx::math::vec2(1.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f, -1.f, -1.f), phx::math::vec2(0.f,  0.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3(-1.f, -1.f,  1.f), phx::math::vec2(0.f,  1.f), phx::math::vec3(0, 1, 0)},
    {phx::math::vec3( 1.f, -1.f,  1.f), phx::math::vec2(1.f,  1.f), phx::math::vec3(0, 1, 0)},
};
// clang-format on
