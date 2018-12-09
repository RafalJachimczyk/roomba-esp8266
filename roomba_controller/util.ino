void prepareOledDisplay()
{
  display.clearDisplay();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

char getFreeHeapMem()
{
  freeMem = system_get_free_heap_size();
  char tmp[32];
  snprintf(tmp, sizeof(tmp), "%d", freeMem);
  return *tmp;
}
