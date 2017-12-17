
#pragma once

#include "stdafx.h"
#include <unordered_map>
#include <iterator>
#include <memory>
#include <functional>
#include <SFML\Graphics.hpp>

template<typename T>
class ResourceManager
{
protected:
	std::unordered_map<std::string, std::unique_ptr<T>> m_resources;

public:
	ResourceManager() { };
	~ResourceManager() { };

	T& get(const std::string& filePath)
	{
		using namespace std; using namespace sf;

		auto it = m_resources.find(filePath);

		if (it != m_resources.end())
			return *(it->second);

		auto loadFile = fromFile<T>(filePath);
		unique_ptr<T> resource(new T());

		loadFile(*resource);

		// Store refrence to resource before we move the pointer
		// into the map so we can return it
		T& resourceRef = *resource;

		m_resources.insert(pair<string, unique_ptr<T>>(filePath, std::move(resource)));

		return resourceRef;
	}

private:
	template <class R>
	std::function<bool(R&)> fromFile(const std::string& filePath)
	{
		return std::function<bool(R&)>(
			[&](R& resource) {
			bool result = resource.loadFromFile(filePath);
			return result;
		});
	}
};