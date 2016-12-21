/*
 * Copyright (c) 2016 syscl/lighting/Yating Zhou. All rights reserved.
 *
 * Thanks to Apple and Voodoo Project, but it is
 * time for us to push the envelope and add some really interesting stuff.
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial
 * 4.0 Unported License => http://creativecommons.org/licenses/by-nc/4.0
 */

class FakeSMBIOS : public IOService
{
    OSDeclareDefaultStructors(FakeSMBIOS)
    typedef IOService super;
    
protected:
    IOService*          fRoot;
    
public:
    virtual bool        init(OSDictionary *dict);
    virtual bool		start(IOService* provider);
    virtual void		stop(IOService* provider);
    virtual void		free(void);

};
