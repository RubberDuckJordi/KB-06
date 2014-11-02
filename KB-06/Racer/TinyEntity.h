
#include "Entity.h"
#include "Object3D.h"

namespace racer
{
	class TinyEntity : public pengine::Entity
	{
	public:
		void UpdateLogic(float deltaTime, std::map<pengine::Input, long>* actions);
		void Render(pengine::Renderer* renderer);
		void SetObject3D(pengine::Object3D* object);
		void CacheToRenderer(pengine::Renderer* renderer);
		void SetAll(float x, float y, float z, float yaw, float pitch, float roll, float scaleX, float scaleY, float scaleZ);
	private:
		pengine::Object3D* tinyModel;
		float maxRadius;
		float maxScale;
	};
}