#include "mps.h"
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

Plugin* load_plugin(const char* name) {
    void* handle = dlopen(name, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "failed to open plugin %s: %s\n", name, dlerror());
        return nullptr;
    }

    get_plugin_func get_plugin = (get_plugin_func)dlsym(handle, "get_plugin");
    if (!get_plugin) {
        fprintf(stderr, "failed to find get_plugin() from %s\n", name);
        return nullptr;
    }

    Plugin* plugin = get_plugin();
    if (!plugin) {
        fprintf(stderr, "failed to get plugin instance from %s\n", name);
        return nullptr;
    }

    bool result = plugin->init();
    if (!result) {
        fprintf(stderr, "failed to initialize plugin from %s\n", name);
        return nullptr;
    }

    printf("loaded plugin %s (%s)\n", plugin->name, name);
    return plugin;
}

void unload_plugin(Plugin* plugin) {
    if (plugin) {
        delete plugin;
        plugin = nullptr;
    }
}
