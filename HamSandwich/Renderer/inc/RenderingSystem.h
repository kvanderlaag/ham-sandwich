#pragma once

#include <core/inc/IEngineSystem.h>

class RenderingSystem : public IEngineSystem
{
public:
	RenderingSystem();
	virtual ~RenderingSystem() {};

public:
	void Update(long long elapsed) override;
};