#ifndef __PROJECT_H__
#define __PROJECT_H__

#define INITIAL_GNSS				0x1008
#define GNSS_check_data   			0x202
#define GNSS_check_data_repeat      1000

void	deactivate_gnss(void);
bool	gnss_read(void);
void	init_gnss(void);
void	timer_register_and_start(void);

#endif
