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

#pragma once

#include <Client/Graphics/ChunkRenderer.hpp>

#include <Common/Voxels/Map.hpp>

#include <Client/Network.hpp>
#include <Common/Util/BlockingQueue.hpp>
#include <vector>

namespace phx::voxels
{
	// supports some default block models, and customs too.
	enum class BlockModel
	{
		BLOCK,
		SLAB,
		SLOPE,
		STAIR,
		X_PANEL,
		X_PANEL_CUBE,
	};

	inline const char* blockModelToString(BlockModel model)
	{
		switch (model)
		{
		case BlockModel::BLOCK:
			return "BLOCK";
		case BlockModel::SLAB:
			return "SLAB";
		case BlockModel::SLOPE:
			return "SLOPE";
		case BlockModel::STAIR:
			return "STAIR";
		case BlockModel::X_PANEL:
			return "X_PANEL";
		case BlockModel::X_PANEL_CUBE:
			return "X_PANEL_CUBE";
		}

		// don't need this here but clang-tidy keeps complaining and we don't
		// lose anything.
		return "";
	}
} // namespace phx::voxels

