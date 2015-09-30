//
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
#include "commontypes.h"
#include "daccess.h"
#include "forward_declarations.h"
#include "commonmacros.h"
#include "palredhawkcommon.h"
#include "palredhawk.h"
#include "assert.h"
#include "slist.h"
#include "holder.h"
#include "spinlock.h"
#include "rhbinder.h"
#ifdef FEATURE_VSD
#include "virtualcallstub.h"
#endif // FEATURE_VSD
#include "cachedinterfacedispatch.h"

#include "syncclean.hpp"

void SyncClean::Terminate()
{
    CleanUp();
}

void SyncClean::CleanUp ()
{
#ifdef FEATURE_VSD
    // Give others we want to reclaim during the GC sync point a chance to do it
    VirtualCallStubManager::ReclaimAll();
#elif defined(FEATURE_CACHED_INTERFACE_DISPATCH)
    // Update any interface dispatch caches that were unsafe to modify outside of this GC.
    ReclaimUnusedInterfaceDispatchCaches();
#endif
}
