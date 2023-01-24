#pragma once

#include "Core/Common.h"
#include "Utility/Utility.h"

class Script
{
private: // data

	std::string		uuid			= utility::get_uuid();
	std::string		id				= "unidentified";
	bool			active			= false;
	class Scene*	parentScene		= nullptr;
	std::string		fileString		= std::string{};

public: // ctor(s)/dtor(s)

	Script();
	Script(const Script&) = delete;
	Script(const std::string& id, bool active = true, class Scene* parentScene = nullptr);
	virtual ~Script() = default;

public: // core

	virtual bool loadFromFile(const std::string& fileString) = 0;
	virtual void update(float deltaTime) = 0;

public: // getter(s)

	const std::string&	getUuid() const;
	const std::string&	getId() const;
	bool				isActive() const;
	class Scene*		getParentScene() const;
	const std::string&	getFileString() const;

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setParentScene(class Scene* parentScene);

protected: // setter(s) (for use in direct derived classed)

	void setFileString(const std::string& fileString);

public: // utility

	template <typename Derived> Derived* as() const;

};

template<typename Derived>
inline Derived* Script::as() const
{
	if (std::is_base_of<Script, Derived>::value)
	{
		return dynamic_cast<Derived*>(const_cast<Script*>(this));
	}

	return nullptr;
}