volatile int do_not_optimize;

int main(void)
{
    void c_list(void);
    c_list();

    void cpp_list(void);
    cpp_list();

    return 0;
}


