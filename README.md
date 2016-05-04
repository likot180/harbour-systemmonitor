# System Monitor for SailfishOS

**NB!** This is a fork from custodian/harbour-systemmonitor with SysMon extensions developed for measuring stats related to battery monitoring.

**NB!** Since the same database and the same service name are used as the one used by official SysMon, only one of these version can be installed at the same time.

System Monitor records and shows your SailfishOS device usage detail stats.

Currently you are able to see CPU, Battery and Traffic stats.

There are several changes that I introduced into the excellent framework of System Monitor that allowed me to debug different issues in SailfishOS port. This package is made to share the changes with the hope that it would be useful for others as well. Note that this is unofficial version and some of these changes may not make it to the official SysMon.

The main changes introduced in this unofficial build:

*  Time spent by CPU in deep sleep is measured and reported
*  Battery charging and discharging rate are calculated and displayed in Battery detailed statistics sheet
*  Incompatible with official version! Traffic is reported as rates
*  Reporting successful and failed suspend attempts
*  Support for cell data statistics reported via /sys/class/net/rmnet_usb*, as in Nexus 4 port

Details of the changes
======================

CPU sleep
---------

For each measuring interval, amount of time spent by CPU in deep sleep is measured. Then this time is related to real time difference in this interval and the deep sleep time is reported as a fraction of all time. Thus, if you ask SysMon to record the data every 2 minutes, this estimation would be done for time intervals of 2 minutes.

When your device is not doing anything, screen is off, expect rather large fraction of time being spent in deep sleep (max I have seen is about 95%). During charging it is expected that deep sleep fraction is zero. By following deep sleep fraction you could see if your device is doing what is expected or there is some unexpected battery drain. As a part of CPU deep sleep details sheet, the statistics on amount of successful and failed suspend attempts are shown. 


Battery charging and discharging rates
--------------------------------------

This information is helpful, but should be handled carefully due to calculation made to get the derivative. The options to change conditions for discharging rate are provided (accessible by touching discharging rate graph) and can be changed as required. There are surely better ways to calculate the rates from battery charge that could be implemented in future.


Network traffic
---------------

**This change makes it incompatible with the database of the official version.** Please clear the database after moving between the versions in Settings menu!

Instead of quantities, average rates within the measurement interval are reported. The same database IDs are used. As a result, data recorded by different versions are incompatible and would lead to erroneous plots in the app. So, if you wish to see correct statistics, you have to clear the database when you start using this version or would switch back to the official one.
