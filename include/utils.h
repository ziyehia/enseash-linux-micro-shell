
void myprint(const char *s);
ssize_t myscan(char *buff, size_t size);
int command_no_arg_exec(const char *file, const char *arg0);
long timespec_diff_ms(struct timespec *start, struct timespec *end);
void itoa(int n, char s[]);
void itoa_long(long n, char s[]);