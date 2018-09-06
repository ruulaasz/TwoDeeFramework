#include "DebugDraw.h"

DebugDraw::DebugDraw()
{

}

DebugDraw::~DebugDraw()
{

}

void DebugDraw::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	SDL_Point *points = new SDL_Point[vertexCount + 1];

	int i = 0;
	for (i; i < vertexCount; i++)
	{
		points[i].x = vertices[i].x * SCALE_TO_RENDER;
		points[i].y = vertices[i].y * SCALE_TO_RENDER;
	}

	points[i].x = vertices[0].x * SCALE_TO_RENDER;
	points[i].y = vertices[0].y * SCALE_TO_RENDER;

	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(m_renderer, points, vertexCount + 1);
}

void DebugDraw::init(SDL_Renderer * _renderer)
{
	m_renderer = _renderer;
}
