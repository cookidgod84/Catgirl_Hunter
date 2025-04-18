#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FWorld_genModule : public IModuleInterface
{
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};