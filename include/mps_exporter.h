#pragma once

#include "mps_plugin.h"

#define EXPORT_PLUGIN(PluginImplType)       \
extern "C" Plugin* get_plugin() {           \
    static PluginImplType* instance;        \
    if (!instance)                          \
        instance = new PluginImplType();    \
    return instance;                        \
}
