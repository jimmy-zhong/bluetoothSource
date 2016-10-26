

# Set transport make variable
ifneq (,$(findstring -DANALOGUE_INPUT_DEVICE,$(DEFS)))
TRANSPORT=none
else
TRANSPORT=usb_vm
endif

# Check for BlueCore version
ifneq (,$(findstring -DBC5_MULTIMEDIA,$(DEFS)))
EXECUTION_MODE=native
endif

# Include Kalimba algorithms that are built from the DSP applications that are included as part of the project
.PHONY : image/sbc_encoder/sbc_encoder.kap \
 #       image/usb_dongle_48_to_16k_stereo/usb_dongle_48_to_16k_stereo.kap \
 #       image/usb_dongle_48_to_8k_stereo/usb_dongle_48_to_8k_stereo.kap \
 #       image/usb_dongle_16k_mono/usb_dongle_16k_mono.kap \
#        image/usb_dongle_8k_mono/usb_dongle_8k_mono.kap \
 #       image/aptx_encoder/aptx_encoder.kap \
 #       image/aptxhd_encoder/aptxhd_encoder.kap \
 #       image/aptx_acl_sprint_encoder/aptx_acl_sprint_encoder.kap

        
# Include SBC encoder
image/sbc_encoder/sbc_encoder.kap : 
	$(mkdir) image/sbc_encoder
	$(copyfile) ../../kalimba/apps/a2dp_source/image/sbc_encoder/sbc_encoder.kap $@
	
image.fs : image/sbc_encoder/sbc_encoder.kap
    
