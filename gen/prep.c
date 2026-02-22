// Get Nth argument.
#define CPP_NTH(_0, _1, _2, _3, _4, n, ...) n
// Get number of arguments (uses gcc/clang extension for empty argument).
#define CPP_ARGC(...) CPP_NTH(_0, ##__VA_ARGS__, 4, 3, 2, 1, 0)

// Utility to concatenate preprocessor tokens.
#define CONCAT2(lhs, rhs) lhs##rhs
#define CONCAT1(lhs, rhs) CONCAT2(lhs, rhs)

#define ARGS0()
#define ARGS1() a0
#define ARGS2() a1, ARGS1()
#define ARGS3() a2, ARGS2()
#define ARGS4() a3, ARGS3()
#define ARGS5() a4, ARGS4()

// Invoke correct ARGSn macro depending on #arguments.
#define ARGS(...) CONCAT1(ARGS, CPP_ARGC(__VA_ARGS__))()

#define TYPEDARGS0()
#define TYPEDARGS1(ty)      ty a0
#define TYPEDARGS2(ty, ...) ty a1, TYPEDARGS1(__VA_ARGS__)
#define TYPEDARGS3(ty, ...) ty a2, TYPEDARGS2(__VA_ARGS__)
#define TYPEDARGS4(ty, ...) ty a3, TYPEDARGS3(__VA_ARGS__)
#define TYPEDARGS5(ty, ...) ty a4, TYPEDARGS4(__VA_ARGS__)

// Invoke correct TYPEDARGSn macro depending on #arguments.
#define TYPEDARGS(...) CONCAT1(TYPEDARGS, CPP_ARGC(__VA_ARGS__))(__VA_ARGS__)

#define MOCK_WRAPPER_IMPL(ret, fn) \
  /* do common work */             \
  static ret wrap_##fn(...);

// Utility to generate wrapper boilerplate.
#define WRAP(ret, fn, ...)                    \
  __maybe_unused ret wrap_##fn(TYPEDARGS(__VA_ARGS__)) { \
    return fn(ARGS(__VA_ARGS__));      \
  }

#define STATIC_WRAP(ret, fn, ...)                    \
  __maybe_unused static ret wrap_##fn(TYPEDARGS(__VA_ARGS__)) { \
    pr_err("dpu trace: %s\n", __func__); \
    return fn(ARGS(__VA_ARGS__));      \
  }
STATIC_WRAP(void, decon_crc_dump_regs, u32);
STATIC_WRAP(void, decon_dump_regs, u32);
STATIC_WRAP(void, decon_dump_win_regs, u32, u32);
STATIC_WRAP(void, decon_enable_dsc_lockstep_en, u32, u32);
WRAP(void, decon_reg_all_win_shadow_update_req, u32);
STATIC_WRAP(void, decon_reg_clear_crc, u32, u32);
STATIC_WRAP(void, decon_reg_clear_crc_region, u32, u32);
STATIC_WRAP(void, decon_reg_clear_int_all, u32);
STATIC_WRAP(void, decon_reg_clear_window_update_req, u32, u32);
WRAP(void, decon_reg_config_swb_size, u32, u32, u32);
STATIC_WRAP(void, decon_reg_config_win_channel, u32, u32, int);
STATIC_WRAP(void, decon_reg_configure_lcd, u32, const struct decon_config *);
STATIC_WRAP(void, decon_reg_direct_on_off, u32, u32);
STATIC_WRAP(int, decon_reg_disable, u32, const struct decon_config *);
STATIC_WRAP(void, decon_reg_disable_window, u32, u32);
STATIC_WRAP(u32, decon_reg_dmaid2chmap, u32);
STATIC_WRAP(int, decon_reg_enable, u32, const struct decon_config *);
STATIC_WRAP(void, decon_reg_get_crc3, u32, struct decon_crc *);
STATIC_WRAP(void, decon_reg_get_crc4, u32, struct decon_crc *);
STATIC_WRAP(const struct decon_cal_info *, decon_reg_get_devdata, u32);
WRAP(u32, decon_reg_get_frame_cnt, u32);
STATIC_WRAP(u32, decon_reg_get_interrupt_and_clear, u32, enum decon_irq);
WRAP(u64, decon_reg_get_rsc_ch, u32);
WRAP(u64, decon_reg_get_rsc_win, u32);
STATIC_WRAP(u32, decon_reg_get_sel_atb, u32, enum decon_out_type);
WRAP(bool, decon_reg_get_trigger_mask, u32);
STATIC_WRAP(u32, decon_reg_get_window_status, u32, u32);
STATIC_WRAP(u32, decon_reg_get_window_update_req, u32, u32);
STATIC_WRAP(int, decon_reg_init, u32, const struct decon_config *);
STATIC_WRAP(void, decon_reg_init_trigger, u32, const struct decon_config *);
STATIC_WRAP(void, decon_reg_per_frame_off, u32);
STATIC_WRAP(void, decon_reg_read_resource_status, u32, u32);
STATIC_WRAP(int, decon_reg_reset, u32);
STATIC_WRAP(void, decon_reg_reset_data_path, u32, const struct decon_config *);
STATIC_WRAP(void, decon_reg_set_allow_window_update_start, u32, u32);
STATIC_WRAP(void, decon_reg_set_bpc, u32, u32);
STATIC_WRAP(void, decon_reg_set_clkgate_mode, u32, u32);
STATIC_WRAP(void, decon_reg_set_crc3, u32, u32);
STATIC_WRAP(void, decon_reg_set_crc4, u32, u32, bool);
STATIC_WRAP(void, decon_reg_set_crc_int, u32, u32, u32);
WRAP(void, decon_reg_set_cwb_enable, u32, u32);
STATIC_WRAP(void, decon_reg_set_data_path, u32, const struct decon_config *);
STATIC_WRAP(void, decon_reg_set_dither, u32, const struct decon_config *, bool);
STATIC_WRAP(void, decon_reg_set_dpif_crc_con, u32, u32);
STATIC_WRAP(void, decon_reg_set_dsc, u32, struct dsc_config);
STATIC_WRAP(void, decon_reg_set_ewr_mode, u32, u32);
STATIC_WRAP(void, decon_reg_set_extra_interrupt_enable_sfi, u32, u32, u32);
STATIC_WRAP(void, decon_reg_set_fs_crc, u32, u32);
STATIC_WRAP(void, decon_reg_set_interrupt_enable_sfi, u32, u32);
STATIC_WRAP(void, decon_reg_set_interrupts, u32, u32);
STATIC_WRAP(void, decon_reg_set_latency_monitor_enable, u32, u32);
STATIC_WRAP(void, decon_reg_set_latency_monitor_enable, u32, u32);
STATIC_WRAP(void, decon_reg_set_operation_mode, u32, enum decon_op_mode);
STATIC_WRAP(void, decon_reg_set_outfifo_size_ctl0, u32, u32, u32);
STATIC_WRAP(void, decon_reg_set_outfifo_size_ctl1, u32, u32);
STATIC_WRAP(void, decon_reg_set_outfifo_size_ctl2, u32, u32, u32);
WRAP(void, decon_reg_set_pll_sleep, u32, u32);
WRAP(void, decon_reg_set_pll_wakeup, u32, u32);
STATIC_WRAP(void, decon_reg_set_pslave_err, u32, u32);
STATIC_WRAP(void, decon_reg_set_rgb_order, u32, enum decon_rgb_order);
STATIC_WRAP(void, decon_reg_set_sram_enable, u32);
WRAP(void, decon_reg_set_start_crc, u32, u32, u32);
STATIC_WRAP(void, decon_reg_set_win_alpha_mult, u32, u32, u32);
STATIC_WRAP(void, decon_reg_set_win_enable, u32, u32, u32);
STATIC_WRAP(void, decon_reg_set_win_mapcolor, u32, u32, u32);
STATIC_WRAP(void, decon_reg_set_win_plane_alpha, u32, u32, u32, u32);
STATIC_WRAP(u32, decon_reg_set_window_start_enable, u32, u32);
STATIC_WRAP(void, decon_reg_set_window_update_req, u32, u32);
STATIC_WRAP(void, decon_reg_set_winmap, u32, u32, u32, u32);
STATIC_WRAP(int, decon_reg_start, u32, const struct decon_config *);
WRAP(int, decon_reg_stop, u32, const struct decon_config *, bool, u32);
STATIC_WRAP(int, decon_reg_stop_inst_dp, u32, u32);
STATIC_WRAP(int, decon_reg_stop_inst_dsi, u32, const struct decon_config *, u32);
STATIC_WRAP(int, decon_reg_stop_perframe_dp, u32, u32);
WRAP(void, decon_reg_update_req_and_unmask, u32, struct decon_mode);
WRAP(void, decon_reg_update_req_dqe, u32);
WRAP(void, decon_reg_update_req_dqe_cgc, u32);
STATIC_WRAP(void, decon_reg_update_req_global, u32);
STATIC_WRAP(int, decon_reg_wait_global_update_done, u32);
WRAP(int, decon_reg_wait_idle_status_timeout, u32, unsigned long);
STATIC_WRAP(int, decon_reg_wait_run_is_off_timeout, u32, unsigned long);
STATIC_WRAP(int, decon_reg_wait_run_status_timeout, u32, unsigned long);
WRAP(int, decon_reg_wait_update_done_timeout, u32, unsigned long);
STATIC_WRAP(int, decon_reg_wait_window_update_done, u32, u32);
STATIC_WRAP(void, dsc_reg_log_cfg, u32, const struct dsc_config);
STATIC_WRAP(void, dsc_reg_set_auto_clock_gate, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_dcg_all, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_dual_slice, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_flatness_det_th, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_grpcntline, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps, u32, u32, const struct dsc_config);
STATIC_WRAP(void, dsc_reg_set_pps_00_version, u32, u32, u8, u8);
STATIC_WRAP(void, dsc_reg_set_pps_03_bits_per_components, u32, u32, u8);
STATIC_WRAP(void, dsc_reg_set_pps_03_linebuf_depth, u32, u32, u8);
STATIC_WRAP(void, dsc_reg_set_pps_04_comp_cfg, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_05_bits_per_pixel, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_06_07_picture_height, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_08_09_picture_width, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_10_11_slice_height, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_12_13_slice_width, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_14_15_chunk_size, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_16_17_init_xmit_delay, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_18_19_init_dec_delay, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_21_initial_scale_value, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_22_23_scale_increment_interval, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_24_25_scale_decrement_interval, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_27_first_line_bpg_offset, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_28_29_nfl_bpg_offset, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_30_31_slice_bpg_offset, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_32_33_initial_offset, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_34_35_final_offset, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_36_flatness_min_qp, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_37_flatness_max_qp, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_41_rc_quant_incr_limit0, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_42_rc_quant_incr_limit1, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_58_59_rc_range_param_0, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_60_63_rc_range_param_12, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_64_67_rc_range_param_34, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_68_71_rc_range_param_56, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_72_75_rc_range_param_78, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_76_79_rc_range_param_9a, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_80_83_rc_range_param_bc, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_pps_84_87_rc_range_param_de, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_remainder, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_set_slice_mode_change, u32, u32, u32);
STATIC_WRAP(void, dsc_reg_swreset, u32, u32);
WRAP(u32, is_decon_using_ch, u64, u32);
WRAP(u32, is_decon_using_win, u64, u32);
STATIC_WRAP(void, sramc_d_reg_clear_irq, u32, u32);
WRAP(void, sramc_d_reg_get_irq_and_clear, u32);
STATIC_WRAP(void, sramc_d_reg_init, u32);
STATIC_WRAP(void, sramc_d_reg_set_irq_enable, u32);
STATIC_WRAP(void, sramc_d_reg_set_irq_mask, u32, u32);
STATIC_WRAP(void, sramc_d_reg_set_pslave_err, u32, u32);
STATIC_WRAP(void, sramc_g_reg_init, u32);
STATIC_WRAP(u32, win_end_pos, int, int, u32, u32);
STATIC_WRAP(u32, win_start_pos, int, int);
