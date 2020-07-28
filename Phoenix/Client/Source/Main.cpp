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

#include <Client/Client.hpp>
#include <Client/Graphics/Camera.hpp>
#include <Client/Graphics/ShaderPipeline.hpp>
#include <Client/InputQueue.hpp>
#include <Client/Player.hpp>

#include <Common/Logger.hpp>

#include <entt/entt.hpp>
#include <glad/glad.h>
#include <stb_image.h>

//#include <Client/Audio/Audio.hpp>
//#include <Client/Audio/SourcePool.hpp>
//
//#include <Common/Logger.hpp>

using namespace phx;

struct Vertex
{
	math::vec3 pos;
	math::vec2 uv;
};

float blockVerts[] = {
		// front
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,

		// back
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

		// right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		// left
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		// bottom
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,

		// top
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f};

const Vertex vertBlock[] = {
	// front (north)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},

	// left (west)
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},

	// back (south)
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},

	// right (east)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},

	// top
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(1.f,  0.f)},

	// bottom
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
};

const Vertex vertSlab[] = {
	// front (north)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(0.f,  0.5f)},
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},

	// left (west)
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(1.f,  0.5f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},

	// back (south)
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},

	// right (east)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(0.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},

	// top
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(1.f,  0.f)},

	// bottom
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
};

const Vertex vertStair[] = {
	// front (north)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(0.f,  0.5f)},
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},

	// left (west)
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(1.f,  0.5f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},

	// back (south)
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},

	// right (east)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(0.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},

	// top
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f,  0.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  0.f,  0.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  0.f,  0.f), math::vec2(0.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  0.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f,  0.f, -1.f), math::vec2(1.f,  0.f)},

	// bottom
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},

	// upper back

	// front (north)
    {math::vec3(-1.f,  0.f,  0.f), math::vec2(1.f,  0.5f)},
    {math::vec3( 1.f,  0.f,  0.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  1.f,  0.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  0.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  0.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  0.f,  0.f), math::vec2(1.f,  0.5f)},

	// left (west)
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  0.f), math::vec2(0.5f, 1.f)},
    {math::vec3( 1.f,  0.f,  0.f), math::vec2(0.5f, 0.5f)},
    {math::vec3( 1.f,  0.f,  0.f), math::vec2(0.5f, 0.5f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},

	// back (south)
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(0.f,  0.5f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},

	// right (east)
    {math::vec3(-1.f,  0.f,  0.f), math::vec2(0.5f, 0.5f)},
    {math::vec3(-1.f,  1.f,  0.f), math::vec2(0.5f, 1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  0.f,  1.f), math::vec2(1.f,  0.5f)},
    {math::vec3(-1.f,  0.f,  0.f), math::vec2(0.5f, 0.5f)},

	// top
    {math::vec3(-1.f,  1.f,  0.f), math::vec2(1.f,  0.5f)},
    {math::vec3( 1.f,  1.f,  0.f), math::vec2(0.f,  0.5f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  1.f,  0.f), math::vec2(1.f,  0.5f)},

	// don't need a bottom.
};

const Vertex vertSlope[] = {
	// front (north)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},

	// left (west)
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},

	// back (south)
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},

	// right (east)
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},

	// no top, front is the slope.

	// bottom
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
};

const Vertex vertXPan[] = {
	// east-facing front
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},

	// back of east-facing
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},

	// west-facing front
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},

	// back of west-facing
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(1.f,  1.f)},
};

const Vertex vertXPanBlock[] = {
    // east-facing front
    {math::vec3(-1.75f, -1.75f, -1.75f), math::vec2(1.f, 0.f)},
    {math::vec3( 1.75f, -1.75f,  1.75f), math::vec2(0.f, 0.f)},
    {math::vec3( 1.75f,  1.75f,  1.75f), math::vec2(0.f, 1.f)},
    {math::vec3( 1.75f,  1.75f,  1.75f), math::vec2(0.f, 1.f)},
    {math::vec3(-1.75f,  1.75f, -1.75f), math::vec2(1.f, 1.f)},
    {math::vec3(-1.75f, -1.75f, -1.75f), math::vec2(1.f, 0.f)},

    // back of east-facing
    {math::vec3( 1.75f,  1.75f,  1.75f), math::vec2(1.f, 1.f)},
    {math::vec3( 1.75f, -1.75f,  1.75f), math::vec2(1.f, 0.f)},
    {math::vec3(-1.75f, -1.75f, -1.75f), math::vec2(0.f, 0.f)},
    {math::vec3(-1.75f, -1.75f, -1.75f), math::vec2(0.f, 0.f)},
    {math::vec3(-1.75f,  1.75f, -1.75f), math::vec2(0.f, 1.f)},
    {math::vec3( 1.75f,  1.75f,  1.75f), math::vec2(1.f, 1.f)},

    // west-facing front
    {math::vec3(-1.75f, -1.75f,  1.75f), math::vec2(1.f, 0.f)},
    {math::vec3( 1.75f, -1.75f, -1.75f), math::vec2(0.f, 0.f)},
    {math::vec3( 1.75f,  1.75f, -1.75f), math::vec2(0.f, 1.f)},
    {math::vec3( 1.75f,  1.75f, -1.75f), math::vec2(0.f, 1.f)},
    {math::vec3(-1.75f,  1.75f,  1.75f), math::vec2(1.f, 1.f)},
    {math::vec3(-1.75f, -1.75f,  1.75f), math::vec2(1.f, 0.f)},

    // back of west-facing
    {math::vec3( 1.75f,  1.75f, -1.75f), math::vec2(1.f, 1.f)},
    {math::vec3( 1.75f, -1.75f, -1.75f), math::vec2(1.f, 0.f)},
    {math::vec3(-1.75f, -1.75f,  1.75f), math::vec2(0.f, 0.f)},
    {math::vec3(-1.75f, -1.75f,  1.75f), math::vec2(0.f, 0.f)},
    {math::vec3(-1.75f,  1.75f,  1.75f), math::vec2(0.f, 1.f)},
    {math::vec3( 1.75f,  1.75f, -1.75f), math::vec2(1.f, 1.f)},

	// front (north)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},

	// left (west)
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},

	// back (south)
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},

	// right (east)
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},

	// top
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3( 1.f,  1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f,  1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3(-1.f,  1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3(-1.f,  1.f, -1.f), math::vec2(1.f,  0.f)},

	// bottom
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},
    {math::vec3( 1.f, -1.f, -1.f), math::vec2(1.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f, -1.f), math::vec2(0.f,  0.f)},
    {math::vec3(-1.f, -1.f,  1.f), math::vec2(0.f,  1.f)},
    {math::vec3( 1.f, -1.f,  1.f), math::vec2(1.f,  1.f)},

};


#undef main
int main(int argc, char** argv)
{
	// client::Client::get()->run();

	Logger::initialize({});

	gfx::Window window("poopoo peepee", 1280, 720);

	std::vector<Vertex> block(vertBlock,
	                          vertBlock + sizeof(vertBlock) / sizeof(Vertex));

	std::vector<Vertex> slab(vertSlab,
	                         vertSlab + sizeof(vertSlab) / sizeof(Vertex));

	std::vector<Vertex> stair(vertStair,
	                          vertStair + sizeof(vertStair) / sizeof(Vertex));

	std::vector<Vertex> slope(vertSlope,
	                          vertSlope + sizeof(vertSlope) / sizeof(Vertex));

	std::vector<Vertex> xpan(vertXPan,
	                         vertXPan + sizeof(vertXPan) / sizeof(Vertex));

	std::vector<Vertex> xpanBlock(vertXPanBlock, 
								  vertXPanBlock + sizeof(vertXPanBlock) / sizeof(Vertex));

	for (auto& element : slab)
	{
		element.pos.x += 4;
	}

	for (auto& element : stair)
	{
		element.pos.x += 8;
	}

	for (auto& element : slope)
	{
		element.pos.x += 12;
	}

	for (auto& element : xpan)
	{
		element.pos.x += 16;
	}

	for (auto& element : xpanBlock)
	{
		element.pos.x += 20;
	}

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, (block.size() + slab.size() + stair.size() + slope.size() + xpan.size() + xpanBlock.size()) * sizeof(Vertex), nullptr,
	             GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0,
	                block.size() * sizeof(Vertex), block.data());
	glBufferSubData(GL_ARRAY_BUFFER, 
					block.size() * sizeof(Vertex),
	                slab.size() * sizeof(Vertex), slab.data());
	glBufferSubData(GL_ARRAY_BUFFER,
	                (block.size() + slab.size()) * sizeof(Vertex),
	                stair.size() * sizeof(Vertex), stair.data());
	glBufferSubData(GL_ARRAY_BUFFER,
	                (block.size() + slab.size() + stair.size()) * sizeof(Vertex),
	                slope.size() * sizeof(Vertex), slope.data());
	glBufferSubData(GL_ARRAY_BUFFER,
	                (block.size() + slab.size() + stair.size() + slope.size()) * sizeof(Vertex),
	                xpan.size() * sizeof(Vertex), xpan.data());
	glBufferSubData(GL_ARRAY_BUFFER,
	                (block.size() + slab.size() + stair.size() + slope.size() + xpan.size()) * sizeof(Vertex),
	                xpanBlock.size() * sizeof(Vertex), xpanBlock.data());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                      reinterpret_cast<void*>(offsetof(Vertex, pos)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                      reinterpret_cast<void*>(offsetof(Vertex, uv)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	int   x, y, comp;
	unsigned char* data = stbi_load("Assets/test.png", &x, &y, &comp, 4);

    unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	stbi_image_free(data);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	entt::registry registry;
	gfx::FPSCamera camera(&window);
	
	gfx::ShaderPipeline pipeline;
	pipeline.prepare("Assets/Test.vert", "Assets/Test.frag", {{"a_Vertex", 0}, {"a_UV", 1}});
	pipeline.activate();

	pipeline.setMatrix("u_projection", camera.getProjection());
	pipeline.setMatrix("u_model", {});

	while (window.isRunning())
	{
		window.startFrame();

		camera.tick(0.001f);

		pipeline.setMatrix("u_view", camera.calculateViewMatrix());

		glDrawArrays(GL_TRIANGLES, 0, block.size() + slab.size() + stair.size() + slope.size() + xpan.size() + xpanBlock.size());
		
		window.endFrame();
	}

	return 0;
}
