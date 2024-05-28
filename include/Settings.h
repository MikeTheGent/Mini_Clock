
#pragma once

namespace Settings {
    typedef enum {
        ok = 0,
        oversizeFile,
        fileNotFound
    } settingStatus;

    settingStatus begin(void);
    const char *get(const char *id);
}
