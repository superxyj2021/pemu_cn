//
// Created by cpasjuste on 29/05/18.
//

#include "skeleton/pemu.h"
#include "psnes_config.h"

using namespace c2d;
using namespace pemu;

PSNESConfig::PSNESConfig(c2d::Io *io, int version) : PEMUConfig(io, "PSNES", version) {
    printf("PSNESConfig(%s, v%i)\n", getPath().c_str(), version);

    auto group = getGroup(PEMUConfig::GrpId::EMULATION);
    if (!group) {
        printf("PSNESConfig: error, group not found (MENU_ROM_OPTIONS)\n");
        return;
    }

    group->addOption({"AUDIO_SYNC", {"OFF", "ON"}, 0, PEMUConfig::OptId::EMU_AUDIO_SYNC,
                      "ON: PERFECT AUDIO - OFF: MINOR AUDIO STUTTERING (FAVOR FPS)"});
    group->addOption({"CHEATS", {"OFF", "ON"}, 1, PEMUConfig::OptId::EMU_PSNES_CHEATS});
    group->addOption({"BLOCk_INVALID_VRAM", {"OFF", "ON"}, 1, PEMUConfig::OptId::EMU_PSNES_BLOCK_VRAM});
    group->addOption({"TRANSPARENCY", {"OFF", "ON"}, 1, PEMUConfig::OptId::EMU_PSNES_TRANSPARENCY});
    group->addOption({"DISPLAY_MESSAGES", {"OFF", "ON"}, 1, PEMUConfig::OptId::EMU_PSNES_DISPLAY_MESSAGES});
    group->addOption({"FRAMESKIP",
                      {"OFF", "AUTO", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
                      0, PEMUConfig::OptId::EMU_PSNES_FRAMESKIP});
#ifdef __VITA__
    get(PEMUConfig::OptId::EMU_PSNES_FRAMESKIP)->setArrayIndex(3);
#endif
    group->addOption({"TURBO_MODE", {"OFF", "ON"}, 0, PEMUConfig::OptId::EMU_PSNES_TURBO_MODE});
    group->addOption({"TURBO_FRAMESKIP",
                      {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                       "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25"},
                      15, PEMUConfig::OptId::EMU_PSNES_TURBO_FRAMESKIP});

    // no need for auto-scaling mode
    getOption(PEMUConfig::OptId::EMU_SCALING_MODE)->setArray({"ASPECT", "INTEGER"}, 0);

    // "romlist.cpp" (RomList::build) will also reload config, but we need new roms paths
    PEMUConfig::load();

    // add custom rom path
    PEMUConfig::addRomPath("SNES", io->getDataPath() + "roms/", {4, 0, "Super Nintendo"});
    PEMUConfig::save();

    // create roms paths if needed
    auto paths = getRomPaths();
    for (const auto &path: paths) {
        io->create(path.path);
    }
}
