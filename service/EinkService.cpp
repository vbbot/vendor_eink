/*
 * SPDX-FileCopyrightText: 2026 @vbbot
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.vbbot.eink-service"

#include "EinkService.h"

#include <android-base/file.h>
#include <android-base/logging.h>

namespace aidl::vendor::vbbot::eink {

static constexpr char kRefreshNode[] =
        "/sys/devices/platform/soc/11f00000.i2c/i2c-7/7-004b/eink_cpld_registers";
static constexpr char kColdNode[] = "/sys/class/leds/lcd-backlight/brightness";
static constexpr char kWarmNode[] = "/sys/class/leds/led-warmlight/brightness";
static constexpr char kKbdNode[]  = "/sys/class/leds/keyboard-backlight/brightness";

bool EinkService::writeSysfs(const std::string& path, const std::string& value) {
    if (!android::base::WriteStringToFile(value, path)) {
        ALOGE("Failed to write '%s' to %s: %s", value.c_str(), path.c_str(), strerror(errno));
        return false;
    }
    return true;
}

ndk::ScopedAStatus EinkService::setRefreshMode(int32_t mode) {
    if (mode < 1 || mode > 4) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    mCurrentMode = mode;
    writeSysfs(kRefreshNode, std::to_string(mode));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus EinkService::forceFullRefresh() {
    writeSysfs(kRefreshNode, "5");
    // Restore the active mode so the display does not remain in full-clear state
    writeSysfs(kRefreshNode, std::to_string(mCurrentMode));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus EinkService::setFrontlight(int32_t cold, int32_t warm) {
    if (cold < 0 || cold > 80 || warm < 0 || warm > 254) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    writeSysfs(kColdNode, std::to_string(cold));
    writeSysfs(kWarmNode, std::to_string(warm));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus EinkService::setKeyboardBacklight(int32_t brightness) {
    if (brightness < 0 || brightness > 254) {
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_ARGUMENT);
    }
    writeSysfs(kKbdNode, std::to_string(brightness));
    return ndk::ScopedAStatus::ok();
}

}  // namespace aidl::vendor::vbbot::eink
