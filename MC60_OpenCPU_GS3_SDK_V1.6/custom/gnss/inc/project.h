#ifndef __PROJECT_H__
#define __PROJECT_H__

#define	GNSS_CHECK	0x1001

void    timer_GNSS_check_start(void);
void	gnss_events_processing(u32	gnss_status);

void	activate_gnss(void);
void	deactivate_gnss(void);
void	gnss_read(void);

#endif
