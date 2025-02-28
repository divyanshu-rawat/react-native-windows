// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "DynamicAutomationPeer.h"
#include "DynamicAutomationProperties.h"
#include "ViewControl.h"
#include "ViewPanel.h"

#include <wrl\module.h>

int32_t WINRT_CALL WINRT_CanUnloadNow() noexcept
{
    if (!::Microsoft::WRL::Module<::Microsoft::WRL::InProc>::GetModule().Terminate())
    {
        return 1; // S_FALSE
    }

    if (winrt::get_module_lock())
    {
        return 1; // S_FALSE
    }

    winrt::clear_factory_cache();
    return 0; // S_OK
}

int32_t WINRT_CALL WINRT_GetActivationFactory(void* classId, void** factory) noexcept
{
    try
    {
        *factory = nullptr;
        uint32_t length{};
        wchar_t const* const buffer = WINRT_WindowsGetStringRawBuffer(classId, &length);
        std::wstring_view const name{ buffer, length };

        auto requal = [](std::wstring_view const& left, std::wstring_view const& right) noexcept
        {
            return std::equal(left.rbegin(), left.rend(), right.rbegin(), right.rend());
        };

        if (requal(name, L"react.uwp.DynamicAutomationPeer"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::react::uwp::factory_implementation::DynamicAutomationPeer>());
            return 0;
        }

        if (requal(name, L"react.uwp.DynamicAutomationProperties"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::react::uwp::factory_implementation::DynamicAutomationProperties>());
            return 0;
        }

        if (requal(name, L"react.uwp.ViewControl"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::react::uwp::factory_implementation::ViewControl>());
            return 0;
        }

        if (requal(name, L"react.uwp.ViewPanel"))
        {
            *factory = winrt::detach_abi(winrt::make<winrt::react::uwp::factory_implementation::ViewPanel>());
            return 0;
        }
       
        return ::Microsoft::WRL::Module<::Microsoft::WRL::InProc>::GetModule().GetActivationFactory(static_cast<HSTRING>(classId), reinterpret_cast<::IActivationFactory**>(factory));
    }
    catch (...) { return winrt::to_hresult(); }
}
