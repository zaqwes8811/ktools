
//#define AA "aa"

#define ASM_GEN_ATTR(x) \
static struct attribute x##_attr = { \
	.name = #x, \
	.mode = 0664, \
};

#define ASM_GEN_ATTR_LINK(x) \
	&x##_attr

ASM_GEN_ATTR(aa)
ASM_GEN_ATTR_LINK(aa)

ASM_GEN_ATTR(charging_gun_snd_malfunction);
ASM_GEN_ATTR(charging_limited_snd_charging_power_limited);
ASM_GEN_ATTR(high_voltage_snd_warning_of_thermal_event);
ASM_GEN_ATTR(charging_failure_snd_malfunction);
ASM_GEN_ATTR(motor_overheating_snd_critical_temperature_in_the_motor_or_inverter);
ASM_GEN_ATTR(door_open_snd_doors_opened_in_motion_alarm);
ASM_GEN_ATTR(fail_parking_function_enable_snd_malfunction);
ASM_GEN_ATTR(fail_parking_function_enable_snd_switch_to_r_mode);
ASM_GEN_ATTR(parking_deactivation_reminder_snd_impossible_to_do);
ASM_GEN_ATTR(parking_operation_reminder_snd_reminder);
ASM_GEN_ATTR(traffic_recognition_failure_snd_malfunction);


static struct attribute *sysfs_file_attrs[] = {
	&sysfs_attribute,
	&bell_has_notification_attr,
	&odometry_attr,
	&mqtt_seatbelt_status_attr,
	ASM_GEN_ATTR_LINK(charging_gun_snd_malfunction),
	ASM_GEN_ATTR_LINK(charging_limited_snd_charging_power_limited),
	ASM_GEN_ATTR_LINK(high_voltage_snd_warning_of_thermal_event),
	ASM_GEN_ATTR_LINK(charging_failure_snd_malfunction),
	ASM_GEN_ATTR_LINK(motor_overheating_snd_critical_temperature_in_the_motor_or_inverter),
	ASM_GEN_ATTR_LINK(door_open_snd_doors_opened_in_motion_alarm),
	ASM_GEN_ATTR_LINK(fail_parking_function_enable_snd_malfunction),
	ASM_GEN_ATTR_LINK(fail_parking_function_enable_snd_switch_to_r_mode),
	ASM_GEN_ATTR_LINK(parking_deactivation_reminder_snd_impossible_to_do),
	ASM_GEN_ATTR_LINK(parking_operation_reminder_snd_reminder),
	ASM_GEN_ATTR_LINK(traffic_recognition_failure_snd_malfunction),
	NULL,
};

SSP_SYSFS_LEAF_MATCH

ret = kstrtouint(buf, ASM_MAX_NUM_DIGITS_IN_STR, &value);
RETURN_IF(ret < 0, ret, "%s %s Can't read input as u32\n", LOG_NAME, __func__);

#define ASM_GEN_STORE_CASE(NAME, REGISTER_ID) \
do { \
	if (SSP_SYSFS_LEAF_MATCH(attr->name, #NAME)) { \
		bool valid = value == ASM_SND_STOP || value == ASM_SND_PLAY; \
		*matched = true; \
		RETURN_IF(!valid, -EINVAL,"%s %s Invalid status value to set: %d\n", \
				LOG_NAME, __func__, (int) value); \
		mutex_lock(&asm_state->lock); \
		ret = asm_ipc_set_state(asm_state, (REGISTER_ID), value); \
		mutex_unlock(&asm_state->lock); \
		RETURN_IF(ret < 0, ret, "%s %s Can't send sound, snd: %d, ec: %zd\n", \
				LOG_NAME, __func__, (int)(REGISTER_ID), ret); \
		return count; \
	} \
} while (0);

#define ASM_GEN_SHOW_CASE(NAME, REGISTER_ID) \
do { \
	if (SSP_SYSFS_LEAF_MATCH(attr->name, #NAME)) { \
		*matched = true; \
		mutex_lock(&asm_state->lock); \
		ret = asm_ipc_get_latest_state(asm_state, (REGISTER_ID), value); \
		mutex_unlock(&asm_state->lock); \
		RETURN_IF(ret < 0, ret, "%s %s Can't send sound, snd: %d, ec: %zd\n", \
				LOG_NAME, __func__, (int)(REGISTER_ID), ret); \
		return sysfs_emit(buf, "%d\n", value); \
	} \
} while (0);


#define AAAA (0xFFU)


ASM_GEN_STORE_CASE(aaa, AAAA)
ASM_GEN_SHOW_CASE(aaa, AAAA)