#include "general.h"

/* diagnostics API */

bool    signal_quality(void)
{
    // <rssi> 0 -113 dBm or less
    // 1      -111 dBm
    // 2...30 -109... -53 dBm
    // 31 -51 dBm or greater
    // 99 Not known or not detectable

    // <ber> (in percent):
    // 0...7 As RXQUAL values in the table in GSM 05.08 subclause 8.2.4
    // 99 Not known or not detectable

    s32     func_result = RIL_AT_FAILED;
    u32     rssi;
    u32     ber;

    // APP_DEBUG("signal quality:\r\n");
    if ((func_result = RIL_NW_GetSignalQuality(&rssi, &ber)) != RIL_AT_SUCCESS)
    {
        APP_DEBUG("RIL_NW_GetSignalQuality ERROR\r\n\0");
        return (FALSE);
    }

    // APP_DEBUG("rssi -> %d\r\n", rssi);
    // APP_DEBUG("ber -> %d\r\n", ber);

    if (rssi >= 0 && rssi <= 31)
    {
        return (TRUE);
    }
    else if (rssi == 99 || ber == 99) // Not known or not detactable;
    {
        return (FALSE);
    }
    return (TRUE);
}

bool    GSM_status(void)
{
    s32     func_result = RIL_AT_FAILED;
    s32     state;

    // APP_DEBUG("GSM reg status:\r\n");
    if ((func_result = RIL_NW_GetGSMState(&state)) != RIL_AT_SUCCESS)
    {
        APP_DEBUG("RIL_NW_GetGSMState ERROR\r\n\0");
        return (FALSE);
    }

    // APP_DEBUG("state -> %d\r\n", state);
    if (state == NW_STAT_REGISTERED)
    {
        return (TRUE);
    }
    else if (state == NW_STAT_UNKNOWN || state == NW_STAT_REG_DENIED
        || NW_STAT_NOT_REGISTERED || NW_STAT_SEARCHING || NW_STAT_REGISTERED_ROAMING)
    {
        return (FALSE);
    }
}

bool    GPRS_status(void)
{
    s32     func_result = RIL_AT_FAILED;
    s32     state;

    // APP_DEBUG("GPRS reg status:\r\n");
    if ((func_result = RIL_NW_GetGPRSState(&state)) != RIL_AT_SUCCESS)
    {
        APP_DEBUG("RIL_NW_GetGSMState ERROR\r\n");
        return (FALSE);
    }

    // APP_DEBUG("state -> %d\r\n", state);

    if (state == NW_STAT_REGISTERED)
    {
        return (TRUE);
    }
    else if (state == NW_STAT_UNKNOWN || state == NW_STAT_REG_DENIED
            || NW_STAT_NOT_REGISTERED || NW_STAT_SEARCHING || NW_STAT_REGISTERED_ROAMING)
    {
        return (FALSE);
    }
}

bool    network_test(void)
{
    bool    test;

    test = signal_quality();
    if (!test)
    {
        APP_DEBUG("Bad signal\r\n");
    }
    else
    {
        APP_DEBUG("Signal good\r\n");
    }
    test = GSM_status();
    if (!test)
    {
        APP_DEBUG("Bad GSM\r\n");
    }
    else
    {
        APP_DEBUG("GSM good\r\n");
    }
    test = GPRS_status();
    if (!test)
    {
        APP_DEBUG("Bad GPRS\r\n");
    }
    else
    {
        APP_DEBUG("GPRS good\r\n");
    }
    if (test)
    {
        return (TRUE);
    }
    return (FALSE);
}
