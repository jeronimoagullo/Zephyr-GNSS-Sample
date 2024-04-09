/**
 * @file main.c
 * @author Jeronimo Agullo (jeronimoagullo97@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <zephyr/device.h>
#include <zephyr/drivers/gnss.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(zephyr_gnss_sample, LOG_LEVEL_DBG);

static void gnss_data_cb(const struct device *dev, const struct gnss_data *data)
{
	
	if (data->info.fix_status != GNSS_FIX_STATUS_NO_FIX) {
		LOG_INF("date: %02d:%02d:%02d:%03d %02d-%02d-%04d", 
				data->utc.hour, data->utc.minute, data->utc.millisecond/1000, data->utc.millisecond%1000, 
				data->utc.month_day, data->utc.month, data->utc.century_year + 2000);
		LOG_INF("%s location (%lld, %lld) with %d tracked satellites", 
				dev->name, data->nav_data.latitude, data->nav_data.longitude, data->info.satellites_cnt);
	} else {
		LOG_INF("no fix. Searching sattelites...");
	}
}

GNSS_DATA_CALLBACK_DEFINE(DEVICE_DT_GET(DT_ALIAS(gnss)), gnss_data_cb);

#if CONFIG_GNSS_SATELLITES
static void gnss_satellites_cb(const struct device *dev, const struct gnss_satellite *satellites,
			       uint16_t size)
{
	LOG_INF("%s reported %u satellites!", dev->name, size);
}
#endif

GNSS_SATELLITES_CALLBACK_DEFINE(DEVICE_DT_GET(DT_ALIAS(gnss)), gnss_satellites_cb);

int main(void)
{
	return 0;
}
