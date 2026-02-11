#pragma once

class Metadata {
public:
    const char* name;
    const char* version;
};

class Plugin : public Metadata {
public:
    virtual bool do_command(const char* command) = 0;
    virtual bool init() = 0;
    virtual ~Plugin() = default;
};
