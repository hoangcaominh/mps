#pragma once

#include "mps_plugin.h"

typedef Plugin* (*get_plugin_func)();

Plugin* load_plugin(const char* name);
void unload_plugin(Plugin* plugin);
