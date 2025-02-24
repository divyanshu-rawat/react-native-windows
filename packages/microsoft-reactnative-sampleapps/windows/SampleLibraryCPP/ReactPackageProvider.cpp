// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "CircleViewManagerCPP.h"
#include "CustomUserControlViewManagerCPP.h"
#include "SampleModuleCPP.h"

using namespace winrt::Microsoft::ReactNative::Bridge;
using namespace Microsoft::ReactNative;

namespace winrt::SampleLibraryCPP::implementation {

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept {
  AddAttributedModules(packageBuilder);
  packageBuilder.AddViewManager(L"CustomUserControlViewManagerCPP", [](IReactContext const &reactContext) {
    return winrt::make<CustomUserControlViewManagerCPP>(reactContext);
  });
  packageBuilder.AddViewManager(
      L"CircleViewManagerCPP", [](IReactContext const &reactContext) { return winrt::make<CircleViewManagerCPP>(); });
}

} // namespace winrt::SampleLibraryCPP::implementation
