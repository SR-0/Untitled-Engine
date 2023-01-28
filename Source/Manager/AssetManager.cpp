#include "Manager/AssetManager.h"
#include "Core/Global.h"
#include <algorithm>





#pragma region CTOR(S)/DTOR(S)

AssetManager::~AssetManager()
{
	this->removeAssets();
}

#pragma endregion CTOR(S)/DTOR(S)





#pragma region CORE

void AssetManager::update(float deltaTime)
{
	for (auto& sound : this->sounds)
		if (sound->isActive())
			sound->callUpdate(deltaTime);

	for (auto& track : this->music)
		if (track->isActive())
			track->callUpdate(deltaTime);

	for (auto& text : this->texts)
		if (text->isActive())
			text->callUpdate(deltaTime);

	for (auto& shape : this->shapes)
	{
		if (shape->isActive())
		{
			if (shape->isAnimated())
				shape->updateAnimation(deltaTime);
			shape->callUpdate(deltaTime);
		}
	}

	for (auto& tilemap : this->tilemaps)
		if (tilemap->isActive())
			tilemap->callUpdate(deltaTime);
}

#pragma endregion CORE





#pragma region SOUND BUFFERS

std::size_t AssetManager::getSoundBufferCount() const
{
	return this->soundBuffers.size();
}

SoundBuffer* AssetManager::getSoundBuffer(std::size_t index)
{
	return this->soundBuffers[index].get();
}

SoundBuffer* AssetManager::getSoundBuffer(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->soundBuffers.size(); index++)
	{
		if ((!uuid ? this->soundBuffers[index]->getId() : this->soundBuffers[index]->getUuid()) == id)
		{
			return this->soundBuffers[index].get();
		}
	}

	return nullptr;
}

SoundBuffer* AssetManager::getSoundBufferFront()
{
	return this->soundBuffers.front().get();
}

SoundBuffer* AssetManager::getSoundBufferBack()
{
	return this->soundBuffers.back().get();
}

std::vector<std::shared_ptr<SoundBuffer>>& AssetManager::getSoundBufferData()
{
	return this->soundBuffers;
}

void AssetManager::removeSoundBuffer(std::size_t index)
{
	this->soundBuffers.erase(this->soundBuffers.begin() + index);
}

void AssetManager::removeSoundBuffer(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->soundBuffers.size(); index++)
	{
		if ((!uuid ? this->soundBuffers[index]->getId() : this->soundBuffers[index]->getUuid()) == id)
		{
			this->soundBuffers.erase(this->soundBuffers.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeSoundBuffer(SoundBuffer* soundBuffer)
{
	for (std::size_t i = 0; i < this->soundBuffers.size(); i++)
	{
		if (this->soundBuffers[i].get() == soundBuffer)
		{
			this->soundBuffers.erase(this->soundBuffers.begin() + i);
			break;
		}
	}
}

void AssetManager::removeSoundBuffers(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->soundBuffers.size(); index++)
		{
			if (static_cast<bool>(this->soundBuffers[index]->getParentScene())			&&
				static_cast<bool>(this->soundBuffers[index]->getParentScene() == scene)	)
			{
				this->soundBuffers.erase(this->soundBuffers.begin() + index);
				index--;
			}
		}

		return;
	}

	this->soundBuffers.clear();
}

void AssetManager::iterateSoundBuffers(const std::function<void(SoundBuffer&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->soundBuffers.rbegin(); iter != this->soundBuffers.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->soundBuffers.begin(); iter != this->soundBuffers.end(); iter++)
		return function(*iter->get());
}

#pragma endregion SOUND BUFFERS





#pragma region SOUNDS

std::size_t AssetManager::getSoundCount() const
{
	return this->sounds.size();
}

Sound* AssetManager::getSound(std::size_t index)
{
	return this->sounds[index].get();
}

Sound* AssetManager::getSound(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->sounds.size(); index++)
	{
		if ((!uuid ? this->sounds[index]->getId() : this->sounds[index]->getUuid()) == id)
		{
			return this->sounds[index].get();
		}
	}

	return nullptr;
}

Sound* AssetManager::getSoundFront()
{
	return this->sounds.front().get();
}

Sound* AssetManager::getSoundBack()
{
	return this->sounds.back().get();
}

std::vector<std::shared_ptr<Sound>>& AssetManager::getSoundData()
{
	return this->sounds;
}

void AssetManager::removeSound(std::size_t index)
{
	this->sounds.erase(this->sounds.begin() + index);
}

void AssetManager::removeSound(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->sounds.size(); index++)
	{
		if ((!uuid ? this->sounds[index]->getId() : this->sounds[index]->getUuid()) == id)
		{
			this->sounds.erase(this->sounds.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeSound(Sound* sound)
{
	for (std::size_t i = 0; i < this->sounds.size(); i++)
	{
		if (this->sounds[i].get() == sound)
		{
			this->sounds.erase(this->sounds.begin() + i);
			break;
		}
	}
}

void AssetManager::removeSounds(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->sounds.size(); index++)
		{
			if (static_cast<bool>(this->sounds[index]->getParentScene())			&&
				static_cast<bool>(this->sounds[index]->getParentScene() == scene)	)
			{
				this->sounds.erase(this->sounds.begin() + index);
				index--;
			}
		}

		return;
	}

	this->sounds.clear();
}

void AssetManager::iterateSounds(const std::function<void(Sound&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->sounds.rbegin(); iter != this->sounds.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->sounds.begin(); iter != this->sounds.end(); iter++)
		return function(*iter->get());
}

#pragma endregion SOUNDS





#pragma region MUSIC

std::size_t AssetManager::getMusicCount() const
{
	return this->music.size();
}

Music* AssetManager::getMusic(std::size_t index)
{
	return this->music[index].get();
}

Music* AssetManager::getMusic(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->music.size(); index++)
	{
		if ((!uuid ? this->music[index]->getId() : this->music[index]->getUuid()) == id)
		{
			return this->music[index].get();
		}
	}

	return nullptr;
}

Music* AssetManager::getMusicFront()
{
	return this->music.front().get();
}

Music* AssetManager::getMusicBack()
{
	return this->music.back().get();
}

std::vector<std::shared_ptr<Music>>& AssetManager::getMusicData()
{
	return this->music;
}

void AssetManager::removeMusic(std::size_t index)
{
	this->music.erase(this->music.begin() + index);
}

void AssetManager::removeMusic(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->music.size(); index++)
	{
		if ((!uuid ? this->music[index]->getId() : this->music[index]->getUuid()) == id)
		{
			this->music.erase(this->music.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeMusic(Music* music)
{
	for (std::size_t i = 0; i < this->music.size(); i++)
	{
		if (this->music[i].get() == music)
		{
			this->music.erase(this->music.begin() + i);
			break;
		}
	}
}

void AssetManager::removeMusics(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->music.size(); index++)
		{
			if (static_cast<bool>(this->music[index]->getParentScene())				&&
				static_cast<bool>(this->music[index]->getParentScene() == scene)	)
			{
				this->music.erase(this->music.begin() + index);
				index--;
			}
		}

		return;
	}

	this->music.clear();
}

void AssetManager::iterateMusics(const std::function<void(Music&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->music.rbegin(); iter != this->music.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->music.begin(); iter != this->music.end(); iter++)
		return function(*iter->get());
}

#pragma endregion MUSIC





#pragma region FONTS

std::size_t AssetManager::getFontCount() const
{
	return this->fonts.size();
}

Font* AssetManager::getFont(std::size_t index)
{
	return this->fonts[index].get();
}

Font* AssetManager::getFont(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->fonts.size(); index++)
	{
		if ((!uuid ? this->fonts[index]->getId() : this->fonts[index]->getUuid()) == id)
		{
			return this->fonts[index].get();
		}
	}

	return nullptr;
}

Font* AssetManager::getFontFront()
{
	return this->fonts.front().get();
}

Font* AssetManager::getFontBack()
{
	return this->fonts.back().get();
}

std::vector<std::shared_ptr<Font>>& AssetManager::getFontData()
{
	return this->fonts;
}

void AssetManager::removeFont(std::size_t index)
{
	this->fonts.erase(this->fonts.begin() + index);
}

void AssetManager::removeFont(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->fonts.size(); index++)
	{
		if ((!uuid ? this->fonts[index]->getId() : this->fonts[index]->getUuid()) == id)
		{
			this->fonts.erase(this->fonts.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeFont(Font* font)
{
	for (std::size_t i = 0; i < this->fonts.size(); i++)
	{
		if (this->fonts[i].get() == font)
		{
			this->fonts.erase(this->fonts.begin() + i);
			break;
		}
	}
}

void AssetManager::removeFonts(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->fonts.size(); index++)
		{
			if (static_cast<bool>(this->fonts[index]->getParentScene()) &&
				static_cast<bool>(this->fonts[index]->getParentScene() == scene))
			{
				this->fonts.erase(this->fonts.begin() + index);
				index--;
			}
		}

		return;
	}

	this->fonts.clear();
}

void AssetManager::iterateFonts(const std::function<void(Font&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->fonts.rbegin(); iter != this->fonts.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->fonts.begin(); iter != this->fonts.end(); iter++)
		return function(*iter->get());
}

#pragma endregion FONTS





#pragma region TEXTS

std::size_t AssetManager::getTextCount() const
{
	return this->texts.size();
}

Text* AssetManager::getText(std::size_t index)
{
	return this->texts[index].get();
}

Text* AssetManager::getText(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->texts.size(); index++)
	{
		if ((!uuid ? this->texts[index]->getId() : this->texts[index]->getUuid()) == id)
		{
			return this->texts[index].get();
		}
	}

	return nullptr;
}

Text* AssetManager::getTextFront()
{
	return this->texts.front().get();
}

Text* AssetManager::getTextBack()
{
	return this->texts.back().get();
}

std::vector<std::shared_ptr<Text>>& AssetManager::getTextData()
{
	return this->texts;
}

void AssetManager::removeText(std::size_t index)
{
	this->texts.erase(this->texts.begin() + index);
}

void AssetManager::removeText(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->texts.size(); index++)
	{
		if ((!uuid ? this->texts[index]->getId() : this->texts[index]->getUuid()) == id)
		{
			this->texts.erase(this->texts.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeText(Text* text)
{
	for (std::size_t i = 0; i < this->texts.size(); i++)
	{
		if (this->texts[i].get() == text)
		{
			this->texts.erase(this->texts.begin() + i);
			break;
		}
	}
}

void AssetManager::removeTexts(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->texts.size(); index++)
		{
			if (static_cast<bool>(this->texts[index]->getParentScene()) &&
				static_cast<bool>(this->texts[index]->getParentScene() == scene))
			{
				this->texts.erase(this->texts.begin() + index);
				index--;
			}
		}

		return;
	}

	this->texts.clear();
}

void AssetManager::iterateTexts(const std::function<void(Text&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->texts.rbegin(); iter != this->texts.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->texts.begin(); iter != this->texts.end(); iter++)
		return function(*iter->get());
}

#pragma endregion TEXTS





#pragma region TEXTURES

std::size_t AssetManager::getTextureCount() const
{
	return this->textures.size();
}

Texture* AssetManager::getTexture(std::size_t index)
{
	return this->textures[index].get();
}

Texture* AssetManager::getTexture(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->textures.size(); index++)
	{
		if ((!uuid ? this->textures[index]->getId() : this->textures[index]->getUuid()) == id)
		{
			return this->textures[index].get();
		}
	}

	return nullptr;
}

Texture* AssetManager::getTextureFront()
{
	return this->textures.front().get();
}

Texture* AssetManager::getTextureBack()
{
	return this->textures.back().get();
}

std::vector<std::shared_ptr<Texture>>& AssetManager::getTextureData()
{
	return this->textures;
}

void AssetManager::removeTexture(std::size_t index)
{
	this->textures.erase(this->textures.begin() + index);
}

void AssetManager::removeTexture(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->textures.size(); index++)
	{
		if ((!uuid ? this->textures[index]->getId() : this->textures[index]->getUuid()) == id)
		{
			this->textures.erase(this->textures.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeTexture(Texture* texture)
{
	for (std::size_t i = 0; i < this->textures.size(); i++)
	{
		if (this->textures[i].get() == texture)
		{
			this->textures.erase(this->textures.begin() + i);
			break;
		}
	}
}

void AssetManager::removeTextures(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->textures.size(); index++)
		{
			if (static_cast<bool>(this->textures[index]->getParentScene()) &&
				static_cast<bool>(this->textures[index]->getParentScene() == scene))
			{
				this->textures.erase(this->textures.begin() + index);
				index--;
			}
		}

		return;
	}

	this->textures.clear();
}

void AssetManager::iterateTextures(const std::function<void(Texture&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->textures.rbegin(); iter != this->textures.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->textures.begin(); iter != this->textures.end(); iter++)
		return function(*iter->get());
}

#pragma endregion TEXTURES





#pragma region SHAPES

std::size_t AssetManager::getShapeCount() const
{
	return this->shapes.size();
}

Shape* AssetManager::getShape(std::size_t index)
{
	return this->shapes[index].get();
}

Shape* AssetManager::getShape(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->shapes.size(); index++)
	{
		if ((!uuid ? this->shapes[index]->getId() : this->shapes[index]->getUuid()) == id)
		{
			return this->shapes[index].get();
		}
	}

	return nullptr;
}

Shape* AssetManager::getShapeFront()
{
	return this->shapes.front().get();
}

Shape* AssetManager::getShapeBack()
{
	return this->shapes.back().get();
}

std::vector<std::shared_ptr<Shape>>& AssetManager::getShapeData()
{
	return this->shapes;
}

void AssetManager::removeShape(std::size_t index)
{
	this->shapes.erase(this->shapes.begin() + index);
}

void AssetManager::removeShape(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->shapes.size(); index++)
	{
		if ((!uuid ? this->shapes[index]->getId() : this->shapes[index]->getUuid()) == id)
		{
			this->shapes.erase(this->shapes.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeShape(Shape* shape)
{
	for (std::size_t i = 0; i < this->shapes.size(); i++)
	{
		if (this->shapes[i].get() == shape)
		{
			this->shapes.erase(this->shapes.begin() + i);
			break;
		}
	}
}

void AssetManager::removeShapes(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->shapes.size(); index++)
		{
			if (static_cast<bool>(this->shapes[index]->getParentScene()) &&
				static_cast<bool>(this->shapes[index]->getParentScene() == scene))
			{
				this->shapes.erase(this->shapes.begin() + index);
				index--;
			}
		}

		return;
	}

	this->shapes.clear();
}

void AssetManager::iterateShapes(const std::function<void(Shape&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->shapes.rbegin(); iter != this->shapes.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->shapes.begin(); iter != this->shapes.end(); iter++)
		return function(*iter->get());
}

#pragma endregion SHAPES





#pragma region TILEMAPS

std::size_t AssetManager::getTilemapCount() const
{
	return this->tilemaps.size();
}

Tilemap* AssetManager::getTilemap(std::size_t index)
{
	return this->tilemaps[index].get();
}

Tilemap* AssetManager::getTilemap(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->tilemaps.size(); index++)
	{
		if ((!uuid ? this->tilemaps[index]->getId() : this->tilemaps[index]->getUuid()) == id)
		{
			return this->tilemaps[index].get();
		}
	}

	return nullptr;
}

Tilemap* AssetManager::getTilemapFront()
{
	return this->tilemaps.front().get();
}

Tilemap* AssetManager::getTilemapBack()
{
	return this->tilemaps.back().get();
}

std::vector<std::shared_ptr<Tilemap>>& AssetManager::getTilemapData()
{
	return this->tilemaps;
}

void AssetManager::removeTilemap(std::size_t index)
{
	this->tilemaps.erase(this->tilemaps.begin() + index);
}

void AssetManager::removeTilemap(const std::string& id, bool uuid)
{
	for (std::size_t index = 0; index < this->tilemaps.size(); index++)
	{
		if ((!uuid ? this->tilemaps[index]->getId() : this->tilemaps[index]->getUuid()) == id)
		{
			this->tilemaps.erase(this->tilemaps.begin() + index);
			index--;
		}
	}
}

void AssetManager::removeTilemap(Tilemap* tilemap)
{
	for (std::size_t i = 0; i < this->tilemaps.size(); i++)
	{
		if (this->tilemaps[i].get() == tilemap)
		{
			this->tilemaps.erase(this->tilemaps.begin() + i);
			break;
		}
	}
}

void AssetManager::removeTilemaps(Scene* scene)
{
	if (static_cast<bool>(scene))
	{
		for (std::size_t index = 0; index < this->tilemaps.size(); index++)
		{
			if (static_cast<bool>(this->tilemaps[index]->getParentScene()) &&
				static_cast<bool>(this->tilemaps[index]->getParentScene() == scene))
			{
				this->tilemaps.erase(this->tilemaps.begin() + index);
				index--;
			}
		}

		return;
	}

	this->tilemaps.clear();
}

void AssetManager::iterateTilemaps(const std::function<void(Tilemap&)>& function, bool reversed)
{
	if (reversed)
		for (auto iter = this->tilemaps.rbegin(); iter != this->tilemaps.rend(); iter++)
			return function(*iter->get());

	for (auto iter = this->tilemaps.begin(); iter != this->tilemaps.end(); iter++)
		return function(*iter->get());
}

#pragma endregion TILEMAPS





#pragma region GENERAL

void AssetManager::removeAssets(Scene* scene)
{
	this->removeTilemaps(scene);
	this->removeShapes(scene);
	this->removeTextures(scene);
	this->removeTexts(scene);
	this->removeFonts(scene);
	this->removeMusics(scene);
	this->removeSounds(scene);
	this->removeSoundBuffers(scene);
}

#pragma endregion GENERAL