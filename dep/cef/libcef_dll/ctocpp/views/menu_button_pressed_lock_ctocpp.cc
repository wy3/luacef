// Copyright (c) 2019 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=f91e3d3dfc7beb8f08e75639f4129a1fdd0f8d22$
//

#include "libcef_dll/ctocpp/views/menu_button_pressed_lock_ctocpp.h"

// CONSTRUCTOR - Do not edit by hand.

CefMenuButtonPressedLockCToCpp::CefMenuButtonPressedLockCToCpp() {}

template <>
cef_menu_button_pressed_lock_t* CefCToCppRefCounted<
    CefMenuButtonPressedLockCToCpp,
    CefMenuButtonPressedLock,
    cef_menu_button_pressed_lock_t>::UnwrapDerived(CefWrapperType type,
                                                   CefMenuButtonPressedLock*
                                                       c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template <>
base::AtomicRefCount CefCToCppRefCounted<
    CefMenuButtonPressedLockCToCpp,
    CefMenuButtonPressedLock,
    cef_menu_button_pressed_lock_t>::DebugObjCt ATOMIC_DECLARATION;
#endif

template <>
CefWrapperType
    CefCToCppRefCounted<CefMenuButtonPressedLockCToCpp,
                        CefMenuButtonPressedLock,
                        cef_menu_button_pressed_lock_t>::kWrapperType =
        WT_MENU_BUTTON_PRESSED_LOCK;