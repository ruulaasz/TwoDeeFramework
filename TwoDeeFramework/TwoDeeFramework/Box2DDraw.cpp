#include "Box2DDraw.h"
#include "SDL_Manager.h"
#include "Box2DManager.h"

namespace TDF
{
	Box2DDraw::Box2DDraw()
	{

	}

	Box2DDraw::~Box2DDraw()
	{

	}

	void Box2DDraw::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
	{
		SDL_Point *points = new SDL_Point[vertexCount + 1];

		int i = 0;
		for (i; i < vertexCount; i++)
		{
			points[i].x = static_cast<int>(vertices[i].x * SCALE_TO_RENDER);
			points[i].y = static_cast<int>(vertices[i].y * SCALE_TO_RENDER);
		}

		points[i].x = static_cast<int>(vertices[0].x * SCALE_TO_RENDER);
		points[i].y = static_cast<int>(vertices[0].y * SCALE_TO_RENDER);

		SDL_SetRenderDrawColor(SDL_Manager::GetInstance().m_renderer , static_cast<uint8>(color.r), static_cast<uint8>(color.g), static_cast<uint8>(color.b), SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLines(SDL_Manager::GetInstance().m_renderer, points, vertexCount + 1);
	}
}