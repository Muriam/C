struct termios term; // структура для перечисления свойств терминала
enum keys {undefined=0, l=1, s=2, r=3, t=4, i=5, f5=6, f6=7, down=8, up=9, k_left=10, k_right=11, enter=12, esc=13 }; // перечисление клавиш
int rk_readkey(enum keys *k);
int rk_mytermsave(void);
int rk_mytermregime(int regime,int vtime,int vmin,int echo,int sigint);

