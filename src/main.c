#include <zephyr/types.h>
#include <stdio.h>
#include <stddef.h>
#include <zephyr/sys/printk.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/gap.h>

void main(void) {
    int err;

    printk("Starting Bluetooth scan...\n");

    // Enable Bluetooth
    err = bt_enable(NULL);
    if (err) {
        printk("Bluetooth initialization failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth initialized\n");

    // Advertising parameters (non-connectable, undirected)
    struct bt_le_adv_param adv_params = BT_LE_ADV_PARAM(
        BT_LE_ADV_OPT_USE_IDENTITY, // Use identity address
        BT_GAP_ADV_FAST_INT_MIN_2,  // Min advertising interval
        BT_GAP_ADV_FAST_INT_MAX_2,  // Max advertising interval
        NULL                        // No whitelist
    );

    // Advertising data
    struct bt_data adv_data[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA(BT_DATA_NAME_COMPLETE, "Zephyr_Beacon", strlen("Zephyr_Beacon")),
    };

    // Start advertising
    err = bt_le_adv_start(&adv_params, adv_data, ARRAY_SIZE(adv_data), NULL, 0);
    if (err) {
        printk("Advertising failed (err %d)\n", err);
        return;
    }

    printk("Beacon is now advertising!\n");