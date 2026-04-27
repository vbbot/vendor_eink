/*
 * SPDX-FileCopyrightText: 2026 @vbbot
 * SPDX-License-Identifier: Apache-2.0
 */

package vendor.vbbot.eink;

interface IEinkService {
    // Refresh mode: 1=BALANCED 2=CLEAR 3=SMOOTH 4=SPEED
    void setRefreshMode(int mode);

    // Write 5 to cpld (force full clear), then restore current mode
    void forceFullRefresh();

    // cold: 0-80, warm: 0-254
    void setFrontlight(int cold, int warm);

    // brightness: 0-254
    void setKeyboardBacklight(int brightness);
}
