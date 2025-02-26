#pragma once

#include <iostream>
#include <map>

struct RecoilPreset
{
    int Vertical;
    int Horizontal;
};

std::map<std::string, RecoilPreset> RecoilPresets =
{
    {"LOW", {3, 0}},
    {"MEDIUM", {5, 0}},
    {"HIGH", {12, 0}},
    {"ULTRA", {20, 0}}
};

const char* Modes[] = {"LOW", "MEDIUM", "HIGH", "ULTRA"};

bool EnableRC = true;
bool RequireToggle = true;
std::string RecoilControlMode = "MEDIUM";
RecoilPreset Recoil = RecoilPresets[RecoilControlMode];
