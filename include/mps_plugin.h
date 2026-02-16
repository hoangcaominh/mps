#pragma once

#include <any>

class PluginMetadata {
public:
    const char* name;
    const char* version;
};

class Plugin {
    friend Plugin* load_plugin(const char* name);
    friend void unload_plugin(Plugin* plugin);
public:
    PluginMetadata metadata;
    virtual bool do_command(const char* command, const std::any& payload) = 0;
    virtual bool init() = 0;
    virtual ~Plugin() = default;
private:
    void* handle;
};
