#pragma once

#include <chrono>

class IEngineSystem
{
public:
	IEngineSystem() {};
	virtual ~IEngineSystem() {};

public:
	// Interface
	virtual void Update(long long elapsed_ns) = 0;
};