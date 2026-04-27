/*
 * SPDX-FileCopyrightText: 2026 @vbbot
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.vbbot.eink-service"

#include "EinkService.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::vendor::vbbot::eink::EinkService;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<EinkService> service = ndk::SharedRefBase::make<EinkService>();

    const std::string instance = std::string(EinkService::descriptor) + "/default";
    binder_status_t status =
            AServiceManager_addService(service->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to register eink service: " << status;

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;
}
