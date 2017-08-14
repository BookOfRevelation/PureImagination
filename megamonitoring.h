#ifndef MEGAMONITORING_H
#define MEGAMONITORING_H


class MegaMonitoring
{
public:
    MegaMonitoring();

    static int getTotalRAM();
    static int getAvailRAM();

    static double getUsedPercentRAM();
};

#endif // MEGAMONITORING_H
