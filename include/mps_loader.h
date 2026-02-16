#pragma once

#include "mps_plugin.h"

typedef Plugin* (*init_plugin_func)();
typedef void (*destroy_plugin_func)(Plugin*);

Plugin* load_plugin(const char* name);
void unload_plugin(Plugin* plugin);
