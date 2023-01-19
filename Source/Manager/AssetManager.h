#pragma once

#include "Asset/Sound.h"
#include "Asset/Music.h"
#include "Asset/Text.h"
#include "Asset/Rectangle.h"
#include "Asset/Circle.h"
#include "Asset/Convex.h"
#include "Asset/Tilemap.h"
#include <mutex>

class AssetManager
{
private: // data

	std::vector<std::shared_ptr<SoundBuffer>>	soundBuffers	= {};
	std::vector<std::shared_ptr<Sound>>			sounds			= {};
	std::vector<std::shared_ptr<Music>>			music			= {};
	std::vector<std::shared_ptr<Font>>			fonts			= {};
	std::vector<std::shared_ptr<Text>>			texts			= {};
	std::vector<std::shared_ptr<Texture>>		textures		= {};
	std::vector<std::shared_ptr<Shape>>			shapes			= {};
	std::vector<std::shared_ptr<Tilemap>>		tilemaps		= {};
	std::mutex									mutex			= std::mutex{};

public: // ctor(s)/dtor(s)

	AssetManager() = default;
	AssetManager(const AssetManager&) = delete;
	AssetManager(AssetManager&&) = delete;
	~AssetManager();

private: // operator overloading

	AssetManager& operator = (const AssetManager&) = delete;
	AssetManager& operator = (AssetManager&&) = delete;

private: // core

	void update(float deltaTime); // for use within Engine.cpp only

public: // sound buffers

	template <typename Derived, typename ... Args> Derived*	createSoundBuffer(Args ... args);
	std::size_t												getSoundBufferCount() const;
	SoundBuffer*											getSoundBuffer(std::size_t index);
	SoundBuffer*											getSoundBuffer(const std::string& id);
	SoundBuffer*											getSoundBufferFront();
	SoundBuffer*											getSoundBufferBack();
	std::vector<std::shared_ptr<SoundBuffer>>&				getSoundBufferData();
	void													removeSoundBuffer(std::size_t index);
	void													removeSoundBuffer(const std::string& id);
	void													removeSoundBuffer(SoundBuffer* soundBuffer); // @TODO add other asset counterparts
	void													removeSoundBuffers(class Scene* scene = nullptr);
	void													iterateSoundBuffers(const std::function<void(SoundBuffer&)>& function, bool reversed = false);

public: // sounds

	template <typename Derived, typename ... Args> Derived*	createSound(Args ... args);
	std::size_t												getSoundCount() const;
	Sound*													getSound(std::size_t index);
	Sound*													getSound(const std::string& id);
	Sound*													getSoundFront();
	Sound*													getSoundBack();
	std::vector<std::shared_ptr<Sound>>&					getSoundData();
	void													removeSound(std::size_t index);
	void													removeSound(const std::string& id);
	void													removeSounds(class Scene* scene = nullptr);
	void													iterateSounds(const std::function<void(Sound&)>& function, bool reversed = false);

public: // music

	template <typename Derived, typename ... Args> Derived*	createMusic(Args ... args);
	std::size_t												getMusicCount() const;
	Music*													getMusic(std::size_t index);
	Music*													getMusic(const std::string& id);
	Music*													getMusicFront();
	Music*													getMusicBack();
	std::vector<std::shared_ptr<Music>>&					getMusicData();
	void													removeMusic(std::size_t index);
	void													removeMusic(const std::string& id);
	void													removeMusics(class Scene* scene = nullptr);
	void													iterateMusics(const std::function<void(Music&)>& function, bool reversed = false);

public: // fonts

	template <typename Derived, typename ... Args> Derived*	createFont(Args ... args);
	std::size_t												getFontCount() const;
	Font*													getFont(std::size_t index);
	Font*													getFont(const std::string& id);
	Font*													getFontFront();
	Font*													getFontBack();
	std::vector<std::shared_ptr<Font>>&						getFontData();
	void													removeFont(std::size_t index);
	void													removeFont(const std::string& id);
	void													removeFonts(class Scene* scene = nullptr);
	void													iterateFonts(const std::function<void(Font&)>& function, bool reversed = false);

public: // texts

	template <typename Derived, typename ... Args> Derived*	createText(Args ... args);
	std::size_t												getTextCount() const;
	Text*													getText(std::size_t index);
	Text*													getText(const std::string& id);
	Text*													getTextFront();
	Text*													getTextBack();
	std::vector<std::shared_ptr<Text>>&						getTextData();
	void													removeText(std::size_t index);
	void													removeText(const std::string& id);
	void													removeTexts(class Scene* scene = nullptr);
	void													iterateTexts(const std::function<void(Text&)>& function, bool reversed = false);

public: // textures

	template <typename Derived, typename ... Args> Derived*	createTexture(Args ... args);
	std::size_t												getTextureCount() const;
	Texture*												getTexture(std::size_t index);
	Texture*												getTexture(const std::string& id);
	Texture*												getTextureFront();
	Texture*												getTextureBack();
	std::vector<std::shared_ptr<Texture>>&					getTextureData();
	void													removeTexture(std::size_t index);
	void													removeTexture(const std::string& id);
	void													removeTextures(class Scene* scene = nullptr);
	void													iterateTextures(const std::function<void(Texture&)>& function, bool reversed = false);

public: // shapes

	template <typename Derived, typename ... Args> Derived*	createShape(Args ... args);
	std::size_t												getShapeCount() const;
	Shape*													getShape(std::size_t index);
	Shape*													getShape(const std::string& id);
	Shape*													getShapeFront();
	Shape*													getShapeBack();
	std::vector<std::shared_ptr<Shape>>&					getShapeData();
	void													removeShape(std::size_t index);
	void													removeShape(const std::string& id);
	void													removeShapes(class Scene* scene = nullptr);
	void													iterateShapes(const std::function<void(Shape&)>& function, bool reversed = false);

public: // tilemaps

	template <typename Derived, typename ... Args> Derived*	createTilemap(Args ... args);
	std::size_t												getTilemapCount() const;
	Tilemap*												getTilemap(std::size_t index);
	Tilemap*												getTilemap(const std::string& id);
	Tilemap*												getTilemapFront();
	Tilemap*												getTilemapBack();
	std::vector<std::shared_ptr<Tilemap>>&					getTilemapData();
	void													removeTilemap(std::size_t index);
	void													removeTilemap(const std::string& id);
	void													removeTilemaps(class Scene* scene = nullptr);
	void													iterateTilemaps(const std::function<void(Tilemap&)>& function, bool reversed = false);

public: // general

	void removeAssets(class Scene* scene = nullptr);

private: // friend(s)

	friend class Engine;

};

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createSoundBuffer(Args ... args)
{
	if (std::is_base_of<SoundBuffer, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->soundBuffers.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->soundBuffers.back().get()->as<Derived>();
	}

	return nullptr;
}

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createSound(Args ... args)
{
	if (std::is_base_of<Sound, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->sounds.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->sounds.back().get()->as<Derived>();
	}

	return nullptr;
}

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createMusic(Args ... args)
{
	if (std::is_base_of<Music, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->music.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->music.back().get()->as<Derived>();
	}

	return nullptr;
}

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createFont(Args ... args)
{
	if (std::is_base_of<Font, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->fonts.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->fonts.back().get()->as<Derived>();
	}

	return nullptr;
}

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createText(Args ... args)
{
	if (std::is_base_of<Text, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->texts.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->texts.back().get()->as<Derived>();
	}

	return nullptr;
}

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createTexture(Args ... args)
{
	if (std::is_base_of<Texture, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->textures.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->textures.back().get()->as<Derived>();
	}

	return nullptr;
}

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createShape(Args ... args)
{
	if (std::is_base_of<Shape, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->shapes.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->shapes.back().get()->as<Derived>();
	}

	return nullptr;
}

template <typename Derived, typename ... Args>
inline Derived* AssetManager::createTilemap(Args ... args)
{
	if (std::is_base_of<Tilemap, Derived>::value)
	{
		std::lock_guard<std::mutex> _(this->mutex);
		this->tilemaps.emplace_back(std::move(std::make_shared<Derived>(args ...)));
		return this->tilemaps.back().get()->as<Derived>();
	}

	return nullptr;
}