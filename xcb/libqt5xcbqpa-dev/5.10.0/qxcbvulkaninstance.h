// Copyright (C) 2017 The Qt Company Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QXCBVULKANINSTANCE_H
#define QXCBVULKANINSTANCE_H

#if defined(VULKAN_H_) && !defined(VK_USE_PLATFORM_XCB_KHR)
#error "vulkan.h included without xcb WSI"
#endif

#define VK_USE_PLATFORM_XCB_KHR

#include <QtVulkanSupport/private/qbasicvulkanplatforminstance_p.h>
#include <QLibrary>

QT_BEGIN_NAMESPACE

class QXcbWindow;

class QXcbVulkanInstance : public QBasicPlatformVulkanInstance
{
public:
    QXcbVulkanInstance(QVulkanInstance *instance);
    ~QXcbVulkanInstance();

    void createOrAdoptInstance() override;
    bool supportsPresent(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, QWindow *window) override;
    void presentQueued(QWindow *window) override;

    VkSurfaceKHR createSurface(QXcbWindow *window);
    void destroySurface(VkSurfaceKHR surface);

private:
    QVulkanInstance *m_instance;
    QLibrary m_lib;
    PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR m_getPhysDevPresSupport;
    PFN_vkCreateXcbSurfaceKHR m_createSurface;
    PFN_vkDestroySurfaceKHR m_destroySurface;
};

QT_END_NAMESPACE

#endif // QXCBVULKANINSTANCE_H
