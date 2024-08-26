#ifndef _FADT_H
#define _FADT_H


#include <stdint.h>
#include <stdbool.h>
#include "acpi.h"


// PM_PROFILE macros
typedef enum {
    UNSPECIFIED = 0,
    DESKTOP = 1,
    MOBILE = 2,
    WORKSTATION = 3,
    ENTREPRISE_SERVER = 4,
    SOHO_SERVER = 5,
    APPLIANCE_PC = 6,
    PERFORMANCE_SERVER = 7,
    TABLET = 8
} pm_profile;


// Generic address structure fpour certains membres de la FADT.
typedef struct {

    uint8_t address_space_id;
    uint8_t register_bit_width;
    uint8_t register_bit_offset;
    uint8_t access_size;
    uint64_t address;
} __attribute__((packed)) gas_t;

typedef struct {

    description_header_t h;
    uint32_t firmware_ctrl;
    uint32_t dsdt;
    uint8_t reserved;
    uint8_t preferred_pm_profile;
    uint16_t sci_int;
    uint32_t smi_cmd;
    uint8_t acpi_enable;
    uint8_t acpi_disable;
    uint8_t s4bios_req;
    uint8_t pstate_cnt;
    uint32_t pm1a_evt_blk;
    uint32_t pm1b_evt_blk;
    uint32_t pm1a_cnt_blk;
    uint32_t pm1b_cnt_blk;
    uint32_t pm2_cnt_blk;
    uint32_t pm_tmr_blk;
    uint32_t gpe0_blk;
    uint32_t gpe1_blk;
    uint8_t pm1_evt_len;
    uint8_t pm1_cnt_len;
    uint8_t pm2_cnt_len;
    uint8_t pm_tmr_len;
    uint8_t gpe0_blk_len;
    uint8_t gpe1_blk_len;
    uint8_t gpe1_base;
    uint8_t cst_cnt;
    uint8_t p_lvl2_lat;
    uint8_t p_lvl3_lat;
    uint16_t flush_size;
    uint16_t flush_stride;
    uint8_t duty_offset;
    uint8_t duty_width;
    uint8_t day_alarm;
    uint8_t mon_alarm;
    uint8_t century;
    uint16_t iapc_boot_arch;
    uint8_t reserved1;
    uint32_t flags;
    gas_t reset_reg;
    uint8_t reset_value;
    uint16_t arm_boot_arch;
    uint8_t fadt_minor_version;
    uint64_t x_firmware_ctrl;
    uint64_t x_dsdt;

    gas_t x_pm1a_evt_blk;
    gas_t x_pm1b_evt_blk;
    gas_t x_pm1a_cnt_blk;
    gas_t x_pm1b_cnt_blk;
    gas_t x_pm2_cnt_blk;
    gas_t x_pm_tmr_blk;
    gas_t x_gpe0_blk;
    gas_t x_gpe1_blk;
    gas_t sleep_control_reg;
    gas_t sleep_status_reg;
    
    uint64_t hypervisor_vendor_identity;

} __attribute__((packed)) fadt_t;


extern fadt_t *fadt_structure;

#endif
