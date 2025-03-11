#include "Camera.h"

void Camera::Resize(float width, float height)
{
	mView.reset(sf::FloatRect(0, 0, width, height));
}
