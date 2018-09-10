#pragma once

#include <Box2D.h>

namespace TDF
{
	//!  A class for box2D debug rendering
	class Box2DDraw : public b2Draw
	{
	public:
		//! Default constructor.
		/*!
		Initialize the members of the class.
		*/
		Box2DDraw();

		//! Default destructor.
		~Box2DDraw();

		//! Draws the solid polygons.
		/*!
		\param vertices,  an array of vertices.
		\param vertexCount, the number of vertices.
		\param color, the color of the render.
		*/
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		void DrawPolygon(const b2Vec2* vertices,
						 int32 vertexCount,
						 const b2Color& color) { vertices; vertexCount; color; }

		void DrawCircle(const b2Vec2& center, 
					    float32 radius, 
						const b2Color& color) { center; radius; color; }

		void DrawSolidCircle(const b2Vec2& center, 
							float32 radius, 
							const b2Vec2& axis, 
							const b2Color& color) { center; radius; axis; color; }

		void DrawSegment(const b2Vec2& p1, 
						 const b2Vec2& p2, 
						 const b2Color& color) { p1; p2; color; }

		void DrawTransform(const b2Transform& xf) { xf; }
	};
}