#pragma once
#include <Box2D.h>
#include <TDF.h>

#define SCALE_TO_WORLD 0.01
#define SCALE_TO_RENDER 100

class DebugDraw : public b2Draw
{
public:
	DebugDraw();
	~DebugDraw();

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {}
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {}
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
	void DrawTransform(const b2Transform& xf) {}

	void init(SDL_Renderer* _renderer);

	SDL_Renderer* m_renderer;
};

