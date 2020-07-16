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
#include <Common/Actor.hpp>

#include <Common/Logger.hpp>

#include <entt/entt.hpp>
#include <glad/glad.h>

//#include <Client/Audio/Audio.hpp>
//#include <Client/Audio/SourcePool.hpp>
//
//#include <Common/Logger.hpp>

using namespace phx;

const math::vec3 block[] = {
    // front
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, 1.f, -1.f),
    phx::math::vec3(1.f, 1.f, -1.f),
    phx::math::vec3(-1.f, 1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),

    // left
    phx::math::vec3(-1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, 1.f),

    // back
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),

    // right
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(1.f, 1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),

    // top
    phx::math::vec3(-1.f, 1.f, -1.f),
    phx::math::vec3(1.f, 1.f, -1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, -1.f),

    // bottom
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
};

const math::vec3 slab[] = {
    // front
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(-1.f, 0.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),

    // left
    phx::math::vec3(-1.f, 0.f, 1.f),
    phx::math::vec3(-1.f, 0.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, 0.f, 1.f),

    // back
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, 0.f, 1.f),
    phx::math::vec3(1.f, 0.f, 1.f),
    phx::math::vec3(-1.f, 0.f, 1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),

    // right
    phx::math::vec3(1.f, 0.f, 1.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, 0.f, 1.f),

    // top
    phx::math::vec3(-1.f, 0.f, -1.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(1.f, 0.f, 1.f),
    phx::math::vec3(1.f, 0.f, 1.f),
    phx::math::vec3(-1.f, 0.f, 1.f),
    phx::math::vec3(-1.f, 0.f, -1.f),

    // bottom
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
};

const math::vec3 stairFront[] = {
    // front
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(-1.f, 0.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    
    // left
    phx::math::vec3(-1.f, 0.f, 0.f),
    phx::math::vec3(-1.f, 0.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, 0.f),
    phx::math::vec3(-1.f, 0.f, 0.f),
    
    // back
    phx::math::vec3(-1.f, -1.f, 0.f),
    phx::math::vec3(1.f, -1.f, 0.f),
    phx::math::vec3(1.f, 0.f, 0.f),
    phx::math::vec3(1.f, 0.f, 0.f),
    phx::math::vec3(-1.f, 0.f, 0.f),
    phx::math::vec3(-1.f, -1.f, 0.f),
    
    // right
    phx::math::vec3(1.f, 0.f, 0.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 0.f),
    phx::math::vec3(1.f, 0.f, 0.f),
    
    // top
    phx::math::vec3(-1.f, 0.f, -1.f),
    phx::math::vec3(1.f, 0.f, -1.f),
    phx::math::vec3(1.f, 0.f, 0.f),
    phx::math::vec3(1.f, 0.f, 0.f),
    phx::math::vec3(-1.f, 0.f, 0.f),
    phx::math::vec3(-1.f, 0.f, -1.f),
    
    // bottom
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 0.f),
    phx::math::vec3(1.f, -1.f, 0.f),
    phx::math::vec3(-1.f, -1.f, 0.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    
    // BACK TALL BIT
    
    // front
    phx::math::vec3(-1.f, -1.f, 0.f),
    phx::math::vec3(1.f,  -1.f, 0.f),
    phx::math::vec3(1.f,   1.f, 0.f),
    phx::math::vec3(1.f,   1.f, 0.f),
    phx::math::vec3(-1.f,  1.f, 0.f),
    phx::math::vec3(-1.f, -1.f, 0.f),
    
    // left
    phx::math::vec3(-1.f,  1.f,  1.f),
    phx::math::vec3(-1.f,  1.f,  0.f),
    phx::math::vec3(-1.f, -1.f,  0.f),
    phx::math::vec3(-1.f, -1.f,  0.f),
    phx::math::vec3(-1.f, -1.f,  1.f),
    phx::math::vec3(-1.f,  1.f,  1.f),
    
    // back
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(1.f,  -1.f, 1.f),
    phx::math::vec3(1.f,   1.f, 1.f),
    phx::math::vec3(1.f,   1.f, 1.f),
    phx::math::vec3(-1.f,  1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),
    
    // right
    phx::math::vec3(1.f,  1.f,  1.f),
    phx::math::vec3(1.f,  1.f,  0.f),
    phx::math::vec3(1.f, -1.f,  0.f),
    phx::math::vec3(1.f, -1.f,  0.f),
    phx::math::vec3(1.f, -1.f,  1.f),
    phx::math::vec3(1.f,  1.f,  1.f),
    
    // top
    phx::math::vec3(-1.f, 1.f,  0.f),
    phx::math::vec3(1.f,  1.f,  0.f),
    phx::math::vec3(1.f,  1.f,  1.f),
    phx::math::vec3(1.f,  1.f,  1.f),
    phx::math::vec3(-1.f, 1.f,  1.f),
    phx::math::vec3(-1.f, 1.f,  0.f),
    
    // bottom
    phx::math::vec3(-1.f, -1.f,  0.f),
    phx::math::vec3(1.f,  -1.f,  0.f),
    phx::math::vec3(1.f,  -1.f,  1.f),
    phx::math::vec3(1.f,  -1.f,  1.f),
    phx::math::vec3(-1.f, -1.f,  1.f),
    phx::math::vec3(-1.f, -1.f,  0.f),
};

const math::vec3 slope[] = {
    // front
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),

    // left
    phx::math::vec3(-1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, 1.f),

    // back
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, 1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),

    // right
    phx::math::vec3(1.f, 1.f, 1.f),
    phx::math::vec3(1.f, 1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, 1.f, 1.f),

    // bottom
    phx::math::vec3(-1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, -1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, 1.f),
    phx::math::vec3(-1.f, -1.f, -1.f),
}

#undef main
int main(int argc, char** argv)
{
	// client::Client::get()->run();

	Logger::initialize({});

	gfx::Window window("poopoo peepee", 1280, 720);

	std::vector<math::vec3> testSlab(slab, slab + 36);

	std::vector<math::vec3> testBlock(block, block + 36);
	for (auto& element : testBlock)
	{
		element.x += 4.f;
	}

	std::vector<math::vec3> testStair(stairFront, stairFront + 72);
	for (auto& element : testStair)
	{
		element.x += 8.f;
	}

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
	             sizeof(math::vec3) *
	                 (testSlab.size() + testBlock.size() + testStair.size()),
	             nullptr, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, testSlab.size() * sizeof(math::vec3),
	                testSlab.data());

	glBufferSubData(GL_ARRAY_BUFFER, testSlab.size() * sizeof(math::vec3),
	                testBlock.size() * sizeof(math::vec3), testBlock.data());

	glBufferSubData(GL_ARRAY_BUFFER,
	                (testSlab.size() + testBlock.size()) * sizeof(math::vec3),
	                testStair.size() * sizeof(math::vec3), testStair.data());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3),
	                      nullptr);

	glEnableVertexAttribArray(0);

	entt::registry registry;
	gfx::FPSCamera camera(&window);

	gfx::ShaderPipeline pipeline;
	pipeline.prepare("Assets/Test.vert", "Assets/Test.frag", {{"a_Vertex", 0}});
	pipeline.activate();

	pipeline.setMatrix("u_projection", camera.getProjection());
	pipeline.setMatrix("u_model", {});

	while (window.isRunning())
	{
		window.startFrame();

		camera.tick(0.001f);

		pipeline.setMatrix("u_view", camera.calculateViewMatrix());

		glDrawArrays(GL_TRIANGLES, 0,
		             testSlab.size() + testBlock.size() + testStair.size());

		window.endFrame();
	}

	return 0;
}
