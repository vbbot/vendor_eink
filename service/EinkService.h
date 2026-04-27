/*
 * SPDX-FileCopyrightText: 2026 @vbbot
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/vendor/vbbot/eink/BnEinkService.h>

namespace aidl::vendor::vbbot::eink {

class EinkService : public BnEinkService {
  public:
    ndk::ScopedAStatus setRefreshMode(int32_t mode) override;
    ndk::ScopedAStatus forceFullRefresh() override;
    ndk::ScopedAStatus setFrontlight(int32_t cold, int32_t warm) override;
    ndk::ScopedAStatus setKeyboardBacklight(int32_t brightness) override;

  private:
    int32_t mCurrentMode = 1;

    static bool writeSysfs(const std::string& path, const std::string& value);
};

}  // namespace aidl::vendor::vbbot::eink
