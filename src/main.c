#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static void task1_loop(void *par1, void *par2, void *par3);
static void task2_loop(void *par1, void *par2, void *par3);
static void task3_loop(void *par1, void *par2, void *par3);

K_THREAD_DEFINE(task1_thread, 300,  task1_loop, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(task2_thread, 300,  task2_loop, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(task3_thread, 300,  task3_loop, NULL, NULL, NULL, 7, 0, 0);

#define SLEEP_TIME_MAX_MS 2
#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static void task1_loop(void *par1, void *par2, void *par3)
{
	uint32_t delay = 0;

	printk("Started %s\n", __func__ );
	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep((int32_t)(delay % SLEEP_TIME_MAX_MS));
		delay++;
	}
}

static void task2_loop(void *par1, void *par2, void *par3)
{
	uint32_t delay = 1;

	printk("Started %s\n", __func__ );
	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep((int32_t)(delay % SLEEP_TIME_MAX_MS));
		delay++;
	}
}

static void task3_loop(void *par1, void *par2, void *par3)
{
	uint32_t delay = 2;

	printk("Started %s\n", __func__ );
	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep((int32_t)(delay % SLEEP_TIME_MAX_MS));
		delay++;
	}
}

void main(void)
{
	int ret;

	if (!device_is_ready(led.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	printk("Initialized %s\n", __func__ );
}
