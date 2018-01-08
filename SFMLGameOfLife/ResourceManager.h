
#pragma once

#include "stdafx.h"
#include <assert.h>
#include <unordered_map>
#include <iterator>
#include <memory>
#include <functional>
#include <SFML\Graphics.hpp>

template<typename T>
class ResourceManager
{

public:
	ResourceManager() { };
	~ResourceManager() { };

	T& get(const std::string& filePath)
	{

		{
			T* existingResource = findResource(filePath);

			if (existingResource) return *existingResource;
		}

		unique_ptr<T> resource = make_unique<T>();

		resource->loadFromFile(filePath);

		return insertResource(filePath, move(resource));
	}

	// Used to handle loading shaders or for calling other resource loadFromFileOverloads that take
	// two parameters.
	template <typename Param>
	T& get(const std::string& filePath, const Param& secondParam)
	{
		using namespace std; using namespace sf;

		{
			T* existingResource = findResource(filePath);

			if (existingResource) return *existingResource;
		}

		unique_ptr<T> resource = make_unique<T>();

		resource->loadFromFile(filePath, secondParam);

		return insertResource(filePath, move(resource));
	}

protected:
	std::unordered_map<std::string, std::unique_ptr<T>> m_resources;

private:
	T& insertResource(const std::string& filePath, std::unique_ptr<T> resource)
	{
		using namespace std; using namespace sf;
		// Store refrence to resource before we move the pointer
		// into the map so we can return it
		T& resourceRef = *resource;

		auto inserted = m_resources.insert(pair<string, unique_ptr<T>>(filePath, move(resource)));

		assert(inserted.second);

		return resourceRef;
	}

	T* findResource(const std::string& filePath)
	{
		using namespace std; using namespace sf;

		auto it = m_resources.find(filePath);

		if (it != m_resources.end())
			return it->second.get();

		return nullptr;
	}
};