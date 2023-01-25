#pragma once

#include "Core/Common.h"
#include "Utility/Utility.h"
#include <SFML/System/Time.hpp>

class Script
{
private: // data

	std::string     uuid                = utility::get_uuid();
	std::string     id                  = "unidentified";
	bool            active              = false;
	bool            repeating           = false;
	class Scene*    parentScene         = nullptr;
	std::string     fileString          = std::string{};
	sf::Time        timeSinceLastRan    = sf::Time::Zero;
	sf::Time        runInterval         = sf::Time::Zero;

public: // ctor(s)/dtor(s)

	Script();
	Script(const Script&) = delete;
	virtual ~Script() = default;
	
	Script
	(
		const std::string&  id,
		const std::string&  fileString  = "",
		bool                active      = true,
		bool                repeating   = false,
		const sf::Time&     runInterval = sf::Time::Zero,
		class Scene*        parentScene = nullptr
	);
	
	Script
	(
		const std::string&  id,
		const std::string&  fileString,
		bool                active,
		bool                repeating,
		float               runIntervalSeconds  = 0.000000f,
		class Scene*        parentScene         = nullptr
	);

public: // core

	virtual void run(float deltaTime) = 0;

public: // getter(s)

	const std::string&      getUuid() const;
	const std::string&      getId() const;
	virtual ScriptLanguage  getScriptLanguage() const = 0;
	bool                    isActive() const;
	bool                    isRepeating() const;
	class Scene*            getParentScene() const;
	const std::string&      getFileString() const;
	const sf::Time&         getTimeSinceLastRan() const;
	const sf::Time&         getRunInterval() const;

public: // setter(s)

	void setId(const std::string& id);
	void setActive(bool active);
	void setRepeating(bool repeating);
	void setParentScene(class Scene* parentScene);
	void setFileString(const std::string& fileString);
	void setRunInterval(const sf::Time& runInterval);
	void setRunInterval(float seconds);

private: // setter(s) (for use within ScriptManager only)

	void setTimeSinceLastRan(const sf::Time& timeSinceLastUpdate);
	void setTimeSinceLastRan(float seconds);

public: // utility

	template <typename Derived> Derived* as() const;

public: // friend(s)

	friend class ScriptManager;

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