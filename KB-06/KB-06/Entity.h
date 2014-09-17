#ifndef __SCENE_ENTITY_H__
#define __SCENE_ENTITY_H__

#include "renderer.h"
#include "Vertex.h"
#include "logger.h"
#include "Input.h"

namespace Scene
{
	class Entity 
	{
	public:
		Entity();
		~Entity();

		virtual void Update(std::map<Input::Input, long>* actions) = 0;
		
		void SetPosition(float x, float y, float z);
		void SetRotation(float yaw, float pitch, float roll);
		void SetScale(float scaleX, float scaleY, float scaleZ);

		void AddPosition(float x, float y, float z);
		void AddRotation(float yaw, float pitch, float roll);
		void AddScale(float scaleX, float scaleY, float scaleZ);

		Resource::Vertex* GetPosition();
		Resource::Vertex* GetRotation();
		Resource::Vertex* GetScale();

		void SetMesh(Resource::Mesh* mesh);

		virtual void Draw(Renderer::Renderer* renderer, Resource::Vertex* position, Resource::Vertex* rotation);

	protected:
		Resource::Vertex position;
		Resource::Vertex rotation;
		Resource::Vertex scale;

		Resource::Mesh* mesh;
		Logger::Logger* logger;

	};
}

#endif
