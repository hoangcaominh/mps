#pragma once

#include "mps_plugin.h"

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#define EXPORT_PLUGIN(PluginImplType)                   \
EXTERN_C {                                              \
void destroy_plugin(Plugin* plugin) {                   \
    if (plugin) {                                       \
        delete plugin;                                  \
        plugin = nullptr;                               \
    }                                                   \
}                                                       \
\
Plugin* init_plugin() {                                 \
    PluginImplType* instance = new PluginImplType();    \
    if (!instance->init()) {                            \
        destroy_plugin(instance);                       \
        instance = nullptr;                             \
    }                                                   \
    return instance;                                    \
}                                                       \
}
