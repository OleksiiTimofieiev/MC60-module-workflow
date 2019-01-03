#ifndef __PROJECT_H__
#define __PROJECT_H__

#define	GNSS_CHECK		0x1001
#define	GNSS_TIMER_STOP	0x1007

void	activate_gnss(void);
void	deactivate_gnss(void);
bool	gnss_read(void);

#define GNSS_check_general  0x200
#define GNSS_check_data     0x202

#define GNSS_check_general_repeat   10000
#define GNSS_check_data_repeat      1000

void	timer_GNSS_register_timers(void);

#endif
