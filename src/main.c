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

	
}