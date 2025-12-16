
void myprint(const char *s);
ssize_t myscan(char *buff, size_t size);
int command_no_arg_exec(const char *file, const char *arg0);
long timespec_diff_ms(struct timespec *start, struct timespec *end);
void itoa(int n, char s[]);
void itoa_long(long n, char s[]);
void string_split(char s[], char *token, char *split[]);
int command_exec(const char *file, char *argv[], char *input_file, char *output_file);