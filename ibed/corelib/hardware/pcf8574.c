#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <linux/i2c-dev.h>


#define PCF8574_ADDR    0x40

static int fd_s = -1;

int pcf8574_init(void)
{
	int iRet = -1;
	fd_s = open("/dev/i2c-0", O_RDWR);
	if(fd_s == -1)
	{
		perror("open pcf8574 failed!\n");
		return -1;
	}
	printf("open pcf8574 success.\n");

	iRet = ioctl(fd_s, I2C_SLAVE, PCF8574_ADDR >> 1);
	if(iRet < 0)
	{
		printf("set pcf8574 address failed: %x \n", iRet);
		close(fd_s);
		return -1;
	}
	printf("set pcf8574 address success.\n");

	return 0;
}

void pcf8574_deinit(void)
{
	if(fd_s != -1)
		close(fd_s);
}

int pcf8574_write(char buf)
{
	int iRet = -1;
	if(fd_s == -1)
	{
		perror("write to pcf8574 failed, please init pcf8574 first.\n");
		return -1;		
	}

	iRet = write(fd_s, &buf, 1);

	if(iRet < 0)
	{
		printf("write to pcf8574 failed: %x.\n", iRet);
		return -1;
	}

	return 0;
}


int pcf8574_read(char *buf)
{
	int iRet = -1;
	if(fd_s == -1)
	{
		perror("read from pcf8574 failed, please init pcf8574 first.\n");
		return -1;
	}

	iRet = read(fd_s, buf, 1);
	if(iRet < 0)
	{
		printf("read from pcf8574 failed: %x.\n", iRet);
		return -1;
	}

	return 0;
}


