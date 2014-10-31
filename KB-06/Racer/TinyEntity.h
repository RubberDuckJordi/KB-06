
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

	private:
		pengine::Object3D* tinyModel;
	};
}