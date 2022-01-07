// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomEnums.generated.h"

UENUM( BlueprintType )
enum class ECollectibles : uint8
{
    NONE = 0,
    CYLINDER,
    CONE,
    CAPSULE,
    CUBE
};
