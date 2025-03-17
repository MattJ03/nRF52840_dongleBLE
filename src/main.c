#include <zephyr/types.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/printk.h>
#include <bluetooth/blutetooth.h>
#include <bluetooth/hci.h>

void main(void) {
	int err;

	printf("Starting Bluetooth scan...\n");

	//enabling bluetooth

	err = BT_enable(NULL);
	if(err) {
		printf("Bluetooth initialisation failed (err %d)\n", err);
		return;
	}

	printf("Bluetooth initialised\n");

	struct bt_le_adv_param *adv_params = BT_LE_ADV_NCONN_IDENTITY;
    struct bt_data adv_data[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA(BT_DATA_NAME_COMPLETE, "Zephyr_Beacon", 14),
    };

    // Start advertising
    err = bt_le_adv_start(adv_params, adv_data, ARRAY_SIZE(adv_data), NULL, 0);
    if (err) {
        printk("Advertising failed (err %d)\n", err);
        return;
    }

    printk("Beacon is now advertising!\n");
}
}