#pragma once

#include <glm/glm.hpp>
#include <blib/RenderState.h>
#include <blib/gl/Vertex.h>
#include <map>
#include <vector>

#include "Rsw.h"

namespace blib { class ResourceManager; class Shader; class Renderer; class App; class Texture; };
class Map;
class Gnd;
class Rsw;
class Rsm;

#define CHUNKSIZE 64

class MapRenderer
{
private:
#pragma region GND
	typedef blib::VertexP3T2T2 GndVertex;
	class GndChunk
	{
	public:
		bool dirty;
		bool rebuilding;
		blib::VBO* vbo;
		std::map<int, std::pair<int, int> > vertIndices;

		int x, y;


		GndChunk(int x, int y, blib::ResourceManager* resourceManager);

		void render(const Gnd* gnd, blib::App* app, blib::RenderState &gndRenderState, blib::Renderer* renderer);
		void rebuild(const Gnd* gnd, blib::App* app, blib::Renderer* renderer);
	};
	//gnd
	blib::RenderState gndRenderState;
	std::vector<std::vector<GndChunk*> > gndChunks;
	blib::Texture* gndShadow;
#pragma endregion
#pragma region RSW
	blib::RenderState rswRenderState;


#pragma endregion

	blib::ResourceManager* resourceManager;

	const Map* map;
	blib::App* app;


public:
	glm::mat4 cameraMatrix;

	bool drawShadows;
	bool drawObjects;
	bool drawTextureGrid;
	bool drawObjectGrid;
	bool drawQuadTree;

	void init( blib::ResourceManager* resourceManager, blib::App* app );
	void setMap(const Map* map);

	void render(blib::Renderer* renderer);
	void renderGnd(blib::Renderer* renderer);
	void renderRsw( blib::Renderer* renderer );
	void renderModel(Rsw::Model* model, blib::Renderer* renderer);
};
