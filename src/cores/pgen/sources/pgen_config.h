//
// Created by cpasjuste on 29/05/18.
//

#ifndef PGEN_CONFIG_H
#define PGEN_CONFIG_H

#include "skeleton/pemu_config.h"

class PGENConfig : public pemu::PEMUConfig {
public:
    PGENConfig(c2d::Io *io, int version);

    ~PGENConfig() override {
        printf("PGENConfig::~PGENConfig()\n");
    }

    std::string getCoreVersion() override;

    std::vector<std::string> getCoreSupportedExt() override;
};

#endif //PGEN_CONFIG_H