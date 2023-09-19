//
// Created by cpasjuste on 29/05/18.
//

#include "skeleton/pemu.h"
#include "pnes_config.h"

using namespace c2d;
using namespace pemu;

PNESConfig::PNESConfig(c2d::Io *io, int version) : PEMUConfig(io, "PNES", version) {
    printf("PNESConfig(%s, v%i)\n", getPath().c_str(), version);

    // no need for auto-scaling mode on pnes
    getOption(PEMUConfig::Id::ROM_SCALING_MODE)->setArray({"ASPECT", "INTEGER"}, 0);

#ifdef __SWITCH__
    // on nintendo switch invert A/B buttons
    getOption(PEMUConfig::Id::JOY_A)->setInteger(KEY_JOY_B_DEFAULT);
    getOption(PEMUConfig::Id::JOY_B)->setInteger(KEY_JOY_A_DEFAULT);
#endif

    // "c2dui_romlist" will also reload config, but we need new roms paths
    load();
}

std::string PNESConfig::getCoreVersion() {
    return "Nestopia 1.52.0";
}

std::vector<std::string> PNESConfig::getCoreSupportedExt() {
    return {".zip", ".nes", ".nez", ".unf", ".unif"};
}
