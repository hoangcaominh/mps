#include "mps.h"
#include <stdio.h>
#include <dlfcn.h>

Plugin* load_plugin(const char* name) {
    Plugin* plugin = nullptr;
    init_plugin_func init_plugin = nullptr;

    void* handle = dlopen(name, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "failed to open plugin %s: %s\n", name, dlerror());
        goto exit_load_plugin;
    }

    init_plugin = (init_plugin_func)dlsym(handle, "init_plugin");
    if (!init_plugin) {
        fprintf(stderr, "failed to find init_plugin() from %s\n", name);
        goto exit_load_plugin;
    }

    plugin = init_plugin();
    if (!plugin) {
        fprintf(stderr, "failed to initialize plugin from %s\n", name);
        goto exit_load_plugin;
    }

    plugin->handle = handle;
    printf("loaded plugin %s (%s)\n", plugin->metadata.name, name);
exit_load_plugin:
    return plugin;
}

void unload_plugin(Plugin* plugin) {
    if (!plugin)
        return;

    destroy_plugin_func destroy_plugin = nullptr;
    void* handle = plugin->handle;

    destroy_plugin = (destroy_plugin_func)dlsym(handle, "destroy_plugin");
    destroy_plugin(plugin);

    if (dlclose(handle) != 0) {
        fprintf(stderr, "failed to close plugin: %s\n", dlerror());
    }
}
