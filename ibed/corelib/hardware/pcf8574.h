#ifndef _PCF8574_H_
  #define _PCF8574_H_

#ifdef __cplusplus
extern "C"{
#endif

extern int pcf8574_init(void);
extern void pcf8574_deinit(void);
extern int pcf8574_write(char buf);
extern int pcf8574_read(char *buf);

#ifdef __cplusplus
}
#endif


#endif


