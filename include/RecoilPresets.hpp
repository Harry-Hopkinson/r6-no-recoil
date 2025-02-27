#ifndef RecoilPresets_HPP
#define RecoilPresets_HPP

bool EnableRC = true;
const char* Modes[] = {"LOW", "MEDIUM", "HIGH", "ULTRA"};
int SelectedMode = 1;

// Recoil settings
struct RecoilPreset
{
    int Vertical;
    int Horizontal;
};
RecoilPreset RecoilPresets[] =
{
    {2, 0}, {3, 0}, {4, 0}, {5, 0}
};
RecoilPreset CurrentRecoil = RecoilPresets[SelectedMode];
bool Running = true;

#endif
