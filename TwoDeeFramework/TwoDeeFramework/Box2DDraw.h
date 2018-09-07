#pragma once

#include <Box2D.h>

namespace TDF
{
	class Box2DDraw : public b2Draw
	{
	public:
		Box2DDraw();
		~Box2DDraw();

		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) { vertices; vertexCount; color; }
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
		void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) { center; radius; color; }
		void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) { center; radius; axis; color; }
		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) { p1; p2; color; }
		void DrawTransform(const b2Transform& xf) { xf; }
	};
}