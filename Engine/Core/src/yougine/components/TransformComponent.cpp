#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y, float z)
{
	this->position = new Vector3(x, y, z);
}

/**
 * \return positionの実体を返す。
 */
Vector3 TransformComponent::GetPosition()
{
	return *this->position;
}

void TransformComponent::SetPosition(Vector3 position)
{
	this->position = &position;
}

