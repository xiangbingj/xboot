#ifndef __SERVO_H__
#define __SERVO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xboot.h>

struct servo_t
{
	char * name;

	void (*set)(struct servo_t * m, int angle);
	int (*get)(struct servo_t * m);
	void * priv;
};

struct servo_t * search_servo(const char * name);
bool_t register_servo(struct device_t ** device, struct servo_t * m);
bool_t unregister_servo(struct servo_t * m);

void servo_set_angle(struct servo_t * m, int angle);
int servo_get_angle(struct servo_t * m);

#ifdef __cplusplus
}
#endif

#endif /* __SERVO_H__ */
