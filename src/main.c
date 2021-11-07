volatile int do_not_optimize;

int main(void)
{

#ifdef TARGET_C
    void c_list(void);
    c_list();
#endif

#ifdef TARGET_CPP
    void cpp_list(void);
    cpp_list();
#endif

    return 0;
}


