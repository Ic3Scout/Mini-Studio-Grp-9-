#pragma once
#include <SFML/Graphics/View.hpp>

class Camera
{
	sf::View mView;
	bool mFocusPlayer;

public:
	void SetPosition(const sf::Vector2f& pos) { mView.setCenter(pos); }
	void Move(float offsetX, float offsetY) { mView.move({ offsetX, offsetY }); }
	void Resize(float width, float height);
	bool GetFocus() { return mFocusPlayer; }
	void SetFocus(bool value) { mFocusPlayer = value; }

	const sf::View* GetView() const { return &mView; }
};

