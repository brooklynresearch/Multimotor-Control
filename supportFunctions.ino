// Support functions.


// This is the configuration function for the three dSPIN parts. Read the inline
//  comments for more info.
void dSPINConfig(void)
{
  boardA.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardA.configStepMode(STEP_FS_32);   // 0 microsteps per step
  boardA.setMaxSpeed(400);        // 10000 steps/s max
  boardA.setFullSpeed(400);       // microstep below 10000 steps/s
  boardA.setAcc(400);             // accelerate at 10000 steps/s/s
  boardA.setDec(400);
  boardA.setSlewRate(CONFIG_SR_530V_us);   // Upping the edge speed increases torque.
  boardA.setOCThreshold(OC_5625mA);  // OC threshold 750mA
  boardA.setPWMFreq(CONFIG_PWM_DIV_2, CONFIG_PWM_MUL_2); // 31.25kHz PWM freq
  boardA.setOCShutdown(CONFIG_OC_SD_DISABLE); // don't shutdown on OC
  boardA.setVoltageComp(CONFIG_VS_COMP_DISABLE); // don't compensate for motor V
  boardA.setSwitchMode(SW_USER);    // Switch is not hard stop
  boardA.setOscMode(CONFIG_INT_16MHZ_OSCOUT_16MHZ); // for boardA, we want 16MHz
                                    //  internal osc, 16MHz out. boardB and
                                    //  boardC will be the same in all respects
                                    //  but this, as they will bring in and
                                    //  output the clock to keep them
                                    //  all in phase.
  boardA.setAccKVAL(255);           // We'll tinker with these later, if needed.
  boardA.setDecKVAL(255);
  boardA.setRunKVAL(255);
  boardA.setHoldKVAL(32);           // This controls the holding current; keep it low.
  
 
  boardB.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardB.configStepMode(STEP_FS_32);   // 0 microsteps per step
  boardB.setMaxSpeed(400);        // 10000 steps/s max
  boardB.setFullSpeed(400);       // microstep below 10000 steps/s
  boardB.setAcc(400);             // accelerate at 10000 steps/s/s
  boardB.setDec(400);
  boardB.setSlewRate(CONFIG_SR_530V_us);   // Upping the edge speed increases torque.
  boardB.setOCThreshold(OC_5625mA);  // OC threshold 750mA
  boardB.setPWMFreq(CONFIG_PWM_DIV_2, CONFIG_PWM_MUL_2); // 31.25kHz PWM freq
  boardB.setOCShutdown(CONFIG_OC_SD_DISABLE); // don't shutdown on OC
  boardB.setVoltageComp(CONFIG_VS_COMP_DISABLE); // don't compensate for motor V
  boardB.setSwitchMode(SW_USER );    // Switch is not hard stop
  boardB.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // for boardA, we want 16MHz
                                    //  internal osc, 16MHz out. boardB and
                                    //  boardC will be the same in all respects
                                    //  but this, as they will bring in and
                                    //  output the clock to keep them
                                    //  all in phase.
  boardB.setAccKVAL(255);           // We'll tinker with these later, if needed.
  boardB.setDecKVAL(255);
  boardB.setRunKVAL(255);
  boardB.setHoldKVAL(32);           // This controls the holding current; keep it low.
  
  
  
 
  boardC.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardC.configStepMode(STEP_FS_32);   // 0 microsteps per step
  boardC.setMaxSpeed(400);        // 10000 steps/s max
  boardC.setFullSpeed(400);       // microstep below 10000 steps/s
  boardC.setAcc(800);             // accelerate at 10000 steps/s/s
  boardC.setDec(800);
  boardC.setSlewRate(SR_530V_us);
  boardC.setOCThreshold(OC_5625mA);  // OC threshold 750mA
  boardC.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  boardC.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC
  boardC.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
  boardC.setSwitchMode(SW_USER);    // Switch is not hard stop
  boardC.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // for boardA, we want 16MHz
                                    //  internal osc, 16MHz out. boardB and
                                    //  boardC will be the same in all respects
                                    //  but this, as they will bring in and
                                    //  output the clock to keep them
                                    //  all in phase.
  boardC.setAccKVAL(255);           // We'll tinker with these later, if needed.
  boardC.setDecKVAL(255);
  boardC.setRunKVAL(255);
  boardC.setHoldKVAL(32);           // This controls the holding current; keep it low.
  
  
  
  boardD.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardD.configStepMode(STEP_FS_32);   // 0 microsteps per step
  boardD.setMaxSpeed(400);        // 10000 steps/s max
  boardD.setFullSpeed(400);       // microstep below 10000 steps/s
  boardD.setAcc(400);             // accelerate at 10000 steps/s/s
  boardD.setDec(400);
  boardD.setSlewRate(CONFIG_SR_530V_us);   // Upping the edge speed increases torque.
  boardD.setOCThreshold(OC_5625mA);  // OC threshold 750mA
  boardD.setPWMFreq(CONFIG_PWM_DIV_2, CONFIG_PWM_MUL_2); // 31.25kHz PWM freq
  boardD.setOCShutdown(CONFIG_OC_SD_DISABLE); // don't shutdown on OC
  boardD.setVoltageComp(CONFIG_VS_COMP_DISABLE); // don't compensate for motor V
  boardD.setSwitchMode(SW_USER );    // Switch is not hard stop
  boardD.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // for boardA, we want 16MHz
                                    //  internal osc, 16MHz out. boardB and
                                    //  boardC will be the same in all respects
                                    //  but this, as they will bring in and
                                    //  output the clock to keep them
                                    //  all in phase.
  boardD.setAccKVAL(255);           // We'll tinker with these later, if needed.
  boardD.setDecKVAL(255);
  boardD.setRunKVAL(255);
  boardD.setHoldKVAL(32);           // This controls the holding current; keep it low.
  
  
  
 
  boardE.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardE.configStepMode(STEP_FS_32);   // 0 microsteps per step
  boardE.setMaxSpeed(400);        // 10000 steps/s max
  boardE.setFullSpeed(400);       // microstep below 10000 steps/s
  boardE.setAcc(400);             // accelerate at 10000 steps/s/s
  boardE.setDec(400);
  boardE.setSlewRate(CONFIG_SR_530V_us);   // Upping the edge speed increases torque.
  boardE.setOCThreshold(OC_5625mA);  // OC threshold 750mA
  boardE.setPWMFreq(CONFIG_PWM_DIV_2, CONFIG_PWM_MUL_2); // 31.2k5kHz PWM freq
  boardE.setOCShutdown(CONFIG_OC_SD_DISABLE); // don't shutdown on OC
  boardE.setVoltageComp(CONFIG_VS_COMP_DISABLE); // don't compensate for motor V
  boardE.setSwitchMode(SW_USER );    // Switch is not hard stop
  boardE.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // for boardA, we want 16MHz
                                    //  internal osc, 16MHz out. boardB and
                                    //  boardC will be the same in all respects
                                    //  but this, as they will bring in and
                                    //  output the clock to keep them
                                    //  all in phase.
  boardE.setAccKVAL(255);           // We'll tinker with these later, if needed.
  boardE.setDecKVAL(255);
  boardE.setRunKVAL(255);
  boardE.setHoldKVAL(32);           // This controls the holding current; keep it low.
  
 

}
  
