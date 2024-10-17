// Definiciones de pines para CAMERA MODELO AI THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void configuracionCamara() {
  // Configurar los parámetros de la cámara
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Seleccione un tamaño de fotograma más bajo si la cámara no es compatible con PSRAM
  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Inicializar la cámara
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("El inicio de la cámara falló con el error 0x%x", err);
    return;
  }

  // Ajustes de calidad de la cámara
  sensor_t * seteoCamara = esp_camera_sensor_get();
  seteoCamara->set_brightness(seteoCamara, 0);
  seteoCamara->set_contrast(seteoCamara, 0);
  seteoCamara->set_saturation(seteoCamara, 0);
  seteoCamara->set_special_effect(seteoCamara, 0);
  seteoCamara->set_whitebal(seteoCamara, 1);
  seteoCamara->set_awb_gain(seteoCamara, 1);
  seteoCamara->set_wb_mode(seteoCamara, 0);
  seteoCamara->set_exposure_ctrl(seteoCamara, 1);
  seteoCamara->set_aec2(seteoCamara, 0);
  seteoCamara->set_ae_level(seteoCamara, 0);
  seteoCamara->set_aec_value(seteoCamara, 300);
  seteoCamara->set_gain_ctrl(seteoCamara, 1);
  seteoCamara->set_agc_gain(seteoCamara, 0);
  seteoCamara->set_gainceiling(seteoCamara, (gainceiling_t)0);
  seteoCamara->set_bpc(seteoCamara, 0);
  seteoCamara->set_wpc(seteoCamara, 1);
  seteoCamara->set_raw_gma(seteoCamara, 1);
  seteoCamara->set_lenc(seteoCamara, 1);
  seteoCamara->set_hmirror(seteoCamara, 0);
  seteoCamara->set_vflip(seteoCamara, 0);
  seteoCamara->set_dcw(seteoCamara, 1);
  seteoCamara->set_colorbar(seteoCamara, 0);
}
