################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zcl-framework-core/subdir.mk
-include update-tc-link-key/subdir.mk
-include strong-random/subdir.mk
-include simple-metering-client/subdir.mk
-include simple-main/subdir.mk
-include serial/EFR32/subdir.mk
-include serial/subdir.mk
-include scenes/subdir.mk
-include scan-dispatch/subdir.mk
-include reporting/subdir.mk
-include packet-handoff/subdir.mk
-include nvm3/EFR32/subdir.mk
-include nvm3/subdir.mk
-include network-steering/subdir.mk
-include mbedtls/EFR32/subdir.mk
-include idle-sleep/subdir.mk
-include identify/subdir.mk
-include hal-library/EFR32_xx/subdir.mk
-include hal-library/EFR32_2/subdir.mk
-include hal-library/EFR32/subdir.mk
-include groups-server/subdir.mk
-include form-and-join/subdir.mk
-include find-and-bind-target/subdir.mk
-include external-generated-files/subdir.mk
-include emlib/subdir.mk
-include emdrv/subdir.mk
-include ember-minimal-printf/subdir.mk
-include efr32/subdir.mk
-include debug-jtag/EFR32/subdir.mk
-include debug-basic-library/EFR32/subdir.mk
-include counters/subdir.mk
-include coexistence-stub/EFR32/subdir.mk
-include ccm-encryption/subdir.mk
-include button-interface/EFR32/subdir.mk
-include antenna-stub/subdir.mk
-include address-table/subdir.mk
-include adc/EFR32/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	$(MAKE) --no-print-directory pre-build
	$(MAKE) --no-print-directory main-build

# Main-build Target
main-build: SmartWater.axf

# Tool invocations
SmartWater.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal/micro/cortexm3/efm32/gcc-cfg.ld" -L"C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal/micro/cortexm3/" -Xlinker --defsym=FLASH_SIZE=786432 -Xlinker --defsym=RAM_SIZE=65536 -Xlinker --defsym=FLASH_PAGE_SIZE=8192 -Xlinker --defsym=SIMEEPROM_SIZE=32768 -Xlinker --defsym=PSSTORE_SIZE=0 -Xlinker --defsym=LONGTOKEN_SIZE=0 -Xlinker --defsym=HEADER_SIZE=512 -Xlinker --defsym=BTL_SIZE=16384 -Xlinker --defsym=LOCKBITS_IN_MAINFLASH_SIZE=8192 -Xlinker --defsym=APP_BTL=1 -Xlinker --defsym=EMBER_MALLOC_HEAP_SIZE=0 -Xlinker --gc-sections -Xlinker -Map="SmartWater.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o SmartWater.axf -Wl,--start-group "./SmartWater_callbacks.o" "./call-command-handler.o" "./callback-stub.o" "./command-interpreter2.o" "./crc.o" "./ember-base-configuration.o" "./ember-configuration.o" "./endian.o" "./library.o" "./mem-util.o" "./random.o" "./security-address-cache.o" "./stack-handler-stub.o" "./token-def.o" "./zigbee-device-common.o" "./zigbee-device-library.o" "./znet-bookkeeping.o" "./znet-cli.o" "./adc/EFR32/adc-efr32.o" "./address-table/address-table-cli.o" "./address-table/address-table.o" "./antenna-stub/antenna-stub.o" "./button-interface/EFR32/button-interface.o" "./ccm-encryption/ccm-star.o" "./coexistence-stub/EFR32/coexistence-802154.o" "./coexistence-stub/EFR32/coulomb-counter-802154.o" "./counters/counters-cli.o" "./counters/counters-ota.o" "./counters/counters-soc.o" "./debug-basic-library/EFR32/SEGGER_RTT.o" "./debug-jtag/EFR32/debug-jtag-efr32.o" "./efr32/assert-crash-handlers.o" "./efr32/button.o" "./efr32/buzzer-efr32.o" "./efr32/cstartup-common.o" "./efr32/diagnostic.o" "./efr32/ext-device.o" "./efr32/faults-v7m.o" "./efr32/isr-stubs.o" "./efr32/led.o" "./efr32/mfg-token.o" "./efr32/micro-common.o" "./efr32/micro.o" "./efr32/sleep-efm32.o" "./efr32/token.o" "./ember-minimal-printf/ember-printf.o" "./emdrv/dmadrv.o" "./emdrv/gpiointerrupt.o" "./emdrv/sl_sleeptimer.o" "./emdrv/sl_sleeptimer_hal_rtcc.o" "./emdrv/tempdrv.o" "./emdrv/uartdrv.o" "./emdrv/ustimer.o" "./emlib/em_adc.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_cryotimer.o" "./emlib/em_emu.o" "./emlib/em_eusart.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_ldma.o" "./emlib/em_leuart.o" "./emlib/em_msc.o" "./emlib/em_prs.o" "./emlib/em_rmu.o" "./emlib/em_rtcc.o" "./emlib/em_se.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_wdog.o" "./emlib/system_efr32mg21.o" "./external-generated-files/bootloader-interface-app.o" "./external-generated-files/bootloader-interface.o" "./external-generated-files/btl_interface.o" "./external-generated-files/btl_interface_storage.o" "./find-and-bind-target/find-and-bind-target-cli.o" "./find-and-bind-target/find-and-bind-target.o" "./form-and-join/form-and-join-afv2.o" "./form-and-join/form-and-join-node-adapter.o" "./form-and-join/form-and-join.o" "./groups-server/groups-server-cli.o" "./groups-server/groups-server.o" "./hal-library/EFR32/hal-config-gpio.o" "./hal-library/EFR32/hal-config.o" "./hal-library/EFR32/sl_mpu.o" "./hal-library/EFR32/sl_power_manager.o" "./hal-library/EFR32/sl_power_manager_debug.o" "./hal-library/EFR32/sl_power_manager_hal_s0_s1.o" "./hal-library/EFR32/sl_power_manager_hal_s2.o" "./hal-library/EFR32/sl_slist.o" "./hal-library/EFR32_2/sl_hfxo_manager.o" "./hal-library/EFR32_2/sl_hfxo_manager_hal_s2.o" "./hal-library/EFR32_xx/pa_conversions_efr32.o" "./hal-library/EFR32_xx/pa_curves_efr32.o" "./identify/identify-cli.o" "./identify/identify.o" "./idle-sleep/idle-sleep-cli.o" "./idle-sleep/idle-sleep-soc.o" "./idle-sleep/idle-sleep.o" "./mbedtls/EFR32/aes.o" "./mbedtls/EFR32/aes_aes.o" "./mbedtls/EFR32/asn1parse.o" "./mbedtls/EFR32/asn1write.o" "./mbedtls/EFR32/base64.o" "./mbedtls/EFR32/bignum.o" "./mbedtls/EFR32/ccm.o" "./mbedtls/EFR32/chacha20.o" "./mbedtls/EFR32/chachapoly.o" "./mbedtls/EFR32/cipher.o" "./mbedtls/EFR32/cipher_wrap.o" "./mbedtls/EFR32/cmac.o" "./mbedtls/EFR32/crypto_aes.o" "./mbedtls/EFR32/crypto_ecp.o" "./mbedtls/EFR32/crypto_gcm.o" "./mbedtls/EFR32/crypto_management.o" "./mbedtls/EFR32/cryptoacc_aes.o" "./mbedtls/EFR32/cryptoacc_gcm.o" "./mbedtls/EFR32/cryptoacc_management.o" "./mbedtls/EFR32/ctr_drbg.o" "./mbedtls/EFR32/des.o" "./mbedtls/EFR32/ecdh.o" "./mbedtls/EFR32/ecdsa.o" "./mbedtls/EFR32/ecjpake.o" "./mbedtls/EFR32/ecp.o" "./mbedtls/EFR32/ecp_curves.o" "./mbedtls/EFR32/entropy.o" "./mbedtls/EFR32/error.o" "./mbedtls/EFR32/gcm.o" "./mbedtls/EFR32/mbedtls_ccm.o" "./mbedtls/EFR32/mbedtls_cmac.o" "./mbedtls/EFR32/mbedtls_ecdsa_ecdh.o" "./mbedtls/EFR32/mbedtls_sha.o" "./mbedtls/EFR32/md.o" "./mbedtls/EFR32/md5.o" "./mbedtls/EFR32/oid.o" "./mbedtls/EFR32/pem.o" "./mbedtls/EFR32/pk.o" "./mbedtls/EFR32/pk_wrap.o" "./mbedtls/EFR32/pkparse.o" "./mbedtls/EFR32/platform_util.o" "./mbedtls/EFR32/poly1305.o" "./mbedtls/EFR32/psa_crypto.o" "./mbedtls/EFR32/psa_crypto_cipher.o" "./mbedtls/EFR32/psa_crypto_client.o" "./mbedtls/EFR32/psa_crypto_driver_wrappers.o" "./mbedtls/EFR32/psa_crypto_ecp.o" "./mbedtls/EFR32/psa_crypto_hash.o" "./mbedtls/EFR32/psa_crypto_mac.o" "./mbedtls/EFR32/psa_crypto_slot_management.o" "./mbedtls/EFR32/psa_crypto_storage.o" "./mbedtls/EFR32/rsa.o" "./mbedtls/EFR32/rsa_internal.o" "./mbedtls/EFR32/se_aes.o" "./mbedtls/EFR32/se_gcm.o" "./mbedtls/EFR32/se_jpake.o" "./mbedtls/EFR32/sha1.o" "./mbedtls/EFR32/sha256.o" "./mbedtls/EFR32/sha512.o" "./mbedtls/EFR32/sl_entropy.o" "./mbedtls/EFR32/sl_mbedtls.o" "./mbedtls/EFR32/sl_psa_its_nvm3.o" "./mbedtls/EFR32/sl_se_management.o" "./mbedtls/EFR32/sl_se_manager.o" "./mbedtls/EFR32/sl_se_manager_attestation.o" "./mbedtls/EFR32/sl_se_manager_cipher.o" "./mbedtls/EFR32/sl_se_manager_entropy.o" "./mbedtls/EFR32/sl_se_manager_hash.o" "./mbedtls/EFR32/sl_se_manager_key_derivation.o" "./mbedtls/EFR32/sl_se_manager_key_handling.o" "./mbedtls/EFR32/sl_se_manager_signature.o" "./mbedtls/EFR32/sl_se_manager_util.o" "./mbedtls/EFR32/sli_crypto_transparent_driver_aead.o" "./mbedtls/EFR32/sli_crypto_transparent_driver_cipher.o" "./mbedtls/EFR32/sli_crypto_transparent_driver_hash.o" "./mbedtls/EFR32/sli_crypto_transparent_driver_mac.o" "./mbedtls/EFR32/sli_crypto_trng_driver.o" "./mbedtls/EFR32/sli_cryptoacc_transparent_driver_aead.o" "./mbedtls/EFR32/sli_cryptoacc_transparent_driver_cipher.o" "./mbedtls/EFR32/sli_cryptoacc_transparent_driver_hash.o" "./mbedtls/EFR32/sli_cryptoacc_transparent_driver_key_derivation.o" "./mbedtls/EFR32/sli_cryptoacc_transparent_driver_key_management.o" "./mbedtls/EFR32/sli_cryptoacc_transparent_driver_mac.o" "./mbedtls/EFR32/sli_cryptoacc_transparent_driver_signature.o" "./mbedtls/EFR32/sli_protocol_crypto_crypto.o" "./mbedtls/EFR32/sli_protocol_crypto_radioaes.o" "./mbedtls/EFR32/sli_psa_driver_common.o" "./mbedtls/EFR32/sli_psa_driver_ghash.o" "./mbedtls/EFR32/sli_psa_driver_init.o" "./mbedtls/EFR32/sli_psa_trng.o" "./mbedtls/EFR32/sli_radioaes_management.o" "./mbedtls/EFR32/sli_se_driver_aead.o" "./mbedtls/EFR32/sli_se_driver_builtin_keys.o" "./mbedtls/EFR32/sli_se_driver_cipher.o" "./mbedtls/EFR32/sli_se_driver_key_derivation.o" "./mbedtls/EFR32/sli_se_driver_key_management.o" "./mbedtls/EFR32/sli_se_driver_mac.o" "./mbedtls/EFR32/sli_se_driver_signature.o" "./mbedtls/EFR32/sli_se_opaque_driver_aead.o" "./mbedtls/EFR32/sli_se_opaque_driver_cipher.o" "./mbedtls/EFR32/sli_se_opaque_driver_mac.o" "./mbedtls/EFR32/sli_se_opaque_key_derivation.o" "./mbedtls/EFR32/sli_se_transparent_driver_aead.o" "./mbedtls/EFR32/sli_se_transparent_driver_cipher.o" "./mbedtls/EFR32/sli_se_transparent_driver_hash.o" "./mbedtls/EFR32/sli_se_transparent_driver_mac.o" "./mbedtls/EFR32/sli_se_transparent_key_derivation.o" "./mbedtls/EFR32/ssl_cache.o" "./mbedtls/EFR32/ssl_ciphersuites.o" "./mbedtls/EFR32/ssl_cli.o" "./mbedtls/EFR32/ssl_cookie.o" "./mbedtls/EFR32/ssl_msg.o" "./mbedtls/EFR32/ssl_srv.o" "./mbedtls/EFR32/ssl_ticket.o" "./mbedtls/EFR32/ssl_tls.o" "./mbedtls/EFR32/threading.o" "./mbedtls/EFR32/x509.o" "./mbedtls/EFR32/x509_create.o" "./mbedtls/EFR32/x509_crl.o" "./mbedtls/EFR32/x509_crt.o" "./mbedtls/EFR32/x509_csr.o" "./mbedtls/EFR32/x509write_crt.o" "./mbedtls/EFR32/x509write_csr.o" "./network-steering/network-steering-cli.o" "./network-steering/network-steering-soc.o" "./network-steering/network-steering-v2.o" "./network-steering/network-steering.o" "./nvm3/EFR32/nvm3_default.o" "./nvm3/EFR32/nvm3_hal_flash.o" "./nvm3/nvm3_lock.o" "./packet-handoff/packet-handoff.o" "./reporting/reporting-cli.o" "./reporting/reporting-default-configuration.o" "./reporting/reporting.o" "./scan-dispatch/scan-dispatch.o" "./scenes/scenes-cli.o" "./scenes/scenes.o" "./serial/EFR32/serial.o" "./serial/com.o" "./simple-main/simple-main.o" "./simple-metering-client/simple-metering-client-cli.o" "./simple-metering-client/simple-metering-client.o" "./strong-random/strong-random-api.o" "./update-tc-link-key/update-tc-link-key-cli.o" "./update-tc-link-key/update-tc-link-key.o" "./zcl-framework-core/af-event.o" "./zcl-framework-core/af-main-common.o" "./zcl-framework-core/af-main-soc.o" "./zcl-framework-core/af-node.o" "./zcl-framework-core/af-security-common.o" "./zcl-framework-core/af-trust-center.o" "./zcl-framework-core/attribute-size.o" "./zcl-framework-core/attribute-storage.o" "./zcl-framework-core/attribute-table.o" "./zcl-framework-core/client-api.o" "./zcl-framework-core/core-cli.o" "./zcl-framework-core/crypto-state.o" "./zcl-framework-core/message.o" "./zcl-framework-core/multi-network.o" "./zcl-framework-core/network-cli.o" "./zcl-framework-core/option-cli.o" "./zcl-framework-core/plugin-cli.o" "./zcl-framework-core/print-formatter.o" "./zcl-framework-core/print.o" "./zcl-framework-core/process-cluster-message.o" "./zcl-framework-core/process-global-message.o" "./zcl-framework-core/security-cli.o" "./zcl-framework-core/service-discovery-common.o" "./zcl-framework-core/service-discovery-soc.o" "./zcl-framework-core/time-util.o" "./zcl-framework-core/util.o" "./zcl-framework-core/zcl-cli.o" "./zcl-framework-core/zdo-cli.o" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/debug-basic-library-cortexm3-gcc-efr32mg21-rail/debug-basic-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/source-route-library-cortexm3-gcc-efr32mg21-rail/source-route-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/end-device-bind-stub-library-cortexm3-gcc-efr32mg21-rail/end-device-bind-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/sim-eeprom2-to-nvm3-upgrade-stub-library-cortexm3-gcc-efr32mg21-rail/sim-eeprom2-to-nvm3-upgrade-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/cbke-283k1-stub-library-cortexm3-gcc-efr32mg21-rail/cbke-283k1-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/debug-extended-stub-library-cortexm3-gcc-efr32mg21-rail/debug-extended-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/cbke-library-dsa-verify-stub-cortexm3-gcc-efr32mg21-rail/cbke-library-dsa-verify-stub.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/autogen/librail_release/librail_efr32xg21_gcc_release.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/nvm3/lib/libnvm3_CM33_gcc.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/cbke-stub-library-cortexm3-gcc-efr32mg21-rail/cbke-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/multi-pan-stub-library-cortexm3-gcc-efr32mg21-rail/multi-pan-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/hal-library-cortexm3-gcc-efr32mg21-rail/hal-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/security-library-link-keys-stub-cortexm3-gcc-efr32mg21-rail/security-library-link-keys-stub.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/binding-table-library-cortexm3-gcc-efr32mg21-rail/binding-table-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/cbke-163k1-stub-library-cortexm3-gcc-efr32mg21-rail/cbke-163k1-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/cbke-library-dsa-sign-stub-cortexm3-gcc-efr32mg21-rail/cbke-library-dsa-sign-stub.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/gp-stub-library-cortexm3-gcc-efr32mg21-rail/gp-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/multi-network-stub-library-cortexm3-gcc-efr32mg21-rail/multi-network-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/zigbee-pro-stack-cortexm3-gcc-efr32mg21-rail/zigbee-pro-stack.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/cbke-library-dsa-verify-283k1-stub-cortexm3-gcc-efr32mg21-rail/cbke-library-dsa-verify-283k1-stub.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/zll-stub-library-cortexm3-gcc-efr32mg21-rail/zll-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/install-code-library-cortexm3-gcc-efr32mg21-rail/install-code-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/zigbee-r22-support-stub-library-cortexm3-gcc-efr32mg21-rail/zigbee-r22-support-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/build/packet-validate-library-cortexm3-gcc-efr32mg21-rail/packet-validate-library.a" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: SmartWater.hex'
	arm-none-eabi-objcopy -O ihex "SmartWater.axf" "SmartWater.hex"
	@echo ' '

	@echo 'Building bin file: SmartWater.bin'
	arm-none-eabi-objcopy -O binary "SmartWater.axf" "SmartWater.bin"
	@echo ' '

	@echo 'Building s37 file: SmartWater.s37'
	arm-none-eabi-objcopy -O srec "SmartWater.axf" "SmartWater.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "SmartWater.axf" -A
	@echo ' '

	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) SmartWater.axf
	-@echo ' '

pre-build:
	-cmd //c 'C:\_MCU\_PROJE~1\SMARTT~1\SMARTH~1\SMART_~1\SMARTW~1/SmartWater-prebuild.bat' 'SmartWater' 'C:/_MCU/_Projects/SmartThings/SmartHeat/Smart_Heat_Electric/SmartWater' '' 'C:\SiliconLabs\SimplicityStudio\v5'
	-@echo ' '

post-build:
	-cmd //c 'C:\_MCU\_PROJE~1\SMARTT~1\SMARTH~1\SMART_~1\SMARTW~1/SmartWater-postbuild.bat' 'SmartWater' 'C:/_MCU/_Projects/SmartThings/SmartHeat/Smart_Heat_Electric/SmartWater' '' 'C:\SiliconLabs\SimplicityStudio\v5'
	-@echo ' '

.PHONY: all clean dependents main-build pre-build post-build

-include ../makefile.targets
