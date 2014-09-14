#include "Entity.h"

D3DXMATRIXA16* Scene::Entity::GetMatrix(){
	return &matrix;
}
void Scene::Entity::Draw(Renderer::Renderer* renderer, D3DXMATRIXA16* offset){
	renderer->SetWorldMatrix(GetMatrix(), offset, false);	
	//renderer->Draw();
}