/*
 * Copyright (c) 2016 syscl/lighting/Yating Zhou. All rights reserved.
 *
 * Thanks to Apple and Voodoo Project, but it is
 * time for us to push the envelope and add some really interesting stuff.
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial
 * 4.0 Unported License => http://creativecommons.org/licenses/by-nc/4.0
 */

#include <IOKit/IOPlatformExpert.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IOKitKeys.h>
#include <i386/proc_reg.h>
#include <sys/sysctl.h>
#include "FakeSMBIOS.hpp"

#include <libkern/version.h>
extern kmod_info_t kmod_info;

OSDefineMetaClassAndStructors(FakeSMBIOS, IOService)

bool FakeSMBIOS::init(OSDictionary *dict)
{
    IOLog("FakeSMBIOS: Version %s starting on OS X Darwin %d.%d.\n", kmod_info.version, version_major, version_minor);
    bool ret = super::init(dict);
    if (ret != true)
    {
        IOLog("FakeSMBIOS::init() %p failed\n", this);
        return ret;
    }
    IOLog("FakeSMBIOS::init() %p\n", this);
    setProperty("Build", "Release");
    setProperty("Author", "syscl");
    return ret;
}

bool FakeSMBIOS::start(IOService* provider)
{
    bool ret = super::start(provider);
    if (ret != true)
    {
        IOLog("FakeSMBIOS::start() failed\n");
        return ret;
    }
    IOLog("FakeSMBIOS::start() %p\n", this);
    fRoot = getServiceRoot();
    if (!provider || !fRoot)
    {
        IOLog("FakeSMBIOS: unable to get provider or Service Root\n");
        return false;
    }

    // get properties from Info.plist
    OSDictionary* providerDict = OSDynamicCast(OSDictionary, getProperty("FakeProperties"));
    OSObject*     dictStr = NULL;
    UInt8         length;
    // inject compatible
    dictStr = providerDict->getObject("compatible");
    if (dictStr)
    {
        OSString* gFakeCompatible = OSDynamicCast(OSString, dictStr);
        length = gFakeCompatible->getLength();
        if (length)
        {
            IOLog("FakeSMBIOS: Inject compatible %s\n", gFakeCompatible->getCStringNoCopy());
            fRoot->setProperty("product-name", OSData::withBytes(gFakeCompatible->getCStringNoCopy(), length + 1));
        }
    }
    // inject product-name
    dictStr = providerDict->getObject("product-name");
    if (dictStr)
    {
      OSString* gFakeProductName = OSDynamicCast(OSString, dictStr);
      length = gFakeProductName->getLength();
      if (length)
      {
        IOLog("FakeSMBIOS: Inject model %s\n", gFakeProductName->getCStringNoCopy());
        fRoot->setProperty("product-name", OSData::withBytes(gFakeProductName->getCStringNoCopy(), length + 1));
      }
    }
    // inject model
    dictStr = providerDict->getObject("model");
    if (dictStr)
    {
      OSString* gFakeModel = OSDynamicCast(OSString, dictStr);
      length = gFakeModel->getLength();
      if (length)
      {
        IOLog("FakeSMBIOS: Inject model %s\n", gFakeModel->getCStringNoCopy());
        fRoot->setProperty("model", OSData::withBytes(gFakeModel->getCStringNoCopy(), length + 1));
        fRoot->setName(gFakeModel->getCStringNoCopy());
      }
    }

    publishResource("FakeSMBIOS");
    registerService();

    return ret;
}

void FakeSMBIOS::stop(IOService* provider)
{
    IOLog("FakeSMBIOS::stop() %p\n", this);
    super::stop(provider);
}

void FakeSMBIOS::free(void)
{
    IOLog("FakeSMBIOS::free() %p\n", this);
    fRoot->release();
    super::free();
}
