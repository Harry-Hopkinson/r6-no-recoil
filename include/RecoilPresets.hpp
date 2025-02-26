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
    {3, 0}, {5, 0}, {12, 0}, {20, 0}
};
RecoilPreset CurrentRecoil = RecoilPresets[SelectedMode];
