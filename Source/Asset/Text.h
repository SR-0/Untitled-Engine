#pragma once

#include "Asset/Font.h"
#include <SFML/Graphics/Text.hpp>

class Text : public sf::Text, public Asset<Text>
{
private: // data

	std::size_t renderLayer     = 0;
	bool        renderEnabled   = true;

public: // ctor(s)/dtor(s)

	Text(const std::string& id = "unidentified", class Scene* parentScene = nullptr, class Port* port = nullptr);
	Text(const Font* font, class Scene* parentScene = nullptr, class Port* port = nullptr);
	Text(const std::string& id, Font* font, class Scene* parentScene = nullptr, class Port* port = nullptr);
	virtual ~Text();

public: // getter(s)

	const std::size_t&  getRenderLayer() const;
	bool                isRenderEnabled() const;
	sf::Uint8           getOpacity() const;
	bool                isTransparent() const;
	bool                isOpaque() const;

public: // setter(s)

	void setRenderLayer(std::size_t renderLayer);
	void setRenderLayerFront();
	void setRenderLayerBack();
	void setRenderEnabled(bool renderEnabled);
	void setOpacity(float opacity);
	void setOpaque();
	void setTransparent();

public: // utility

	void fadeIn(float alphaIncrement, const sf::Uint8& max = 255);
	void fadeOut(float alphaDecrement, const sf::Uint8& min = 0);

};


