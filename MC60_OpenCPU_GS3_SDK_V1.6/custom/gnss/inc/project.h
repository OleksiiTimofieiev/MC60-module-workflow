#ifndef __PROJECT_H__
#define __PROJECT_H__

#define	GNSS_CHECK	0x1001

// void    timer_GNSS_check_start(void);
// void	timer_GNSS_check_stop(void);
// void	gnss_events_processing(void);

void	activate_gnss(void);
void	deactivate_gnss(void);
bool	gnss_read(void);

#endif
