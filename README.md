# FakeSMBIOS

This project targets at filling the truncated SMBIOS information for macOS.

# How to install
You can inject FakeSMBIOS.kext through Clover/Chameleon

# How to tune FakeSMBIOS
- Opne Info.plist under FakeSMBIOS.kext/Contents
- Expand ```/IOKitPersonalities/Platform SMBIOS Match/FakeProperties```
- Change compatible, model, product-name as you like(In our case, MacBookPro13,1)

# Contribution
Credit also Voodoo Project

# Change
2016-12-21
- Fixed some bugs
- Refined code
