#include <iostream>
#include <chrono>

namespace runtime {
    class base {

    public:
        virtual void print_me() const = 0;

        virtual void process() = 0;

    };


    class derived_i: public base {

        int m_value;
    public:
        derived_i(int v)
            : m_value(v)
        {}

        virtual void print_me() const {
            std::cout << "VIRTUAL::derived_i"
                      << "< value: "
                      << m_value
                      << std::endl;
        }

        virtual void process() {
            m_value=m_value*m_value/100000;
        }
    };


    class derived_c: public base {

        double m_a, m_b;
    public:
        derived_c(float a, float b)
            : base()
            , m_a(a)
            , m_b(b)
        {}

        virtual void print_me() const {
            std::cout << "VIRTUAL::derived_c"
                      << "< value: ("
                      << m_a << " + i" << m_b << ")"
                      << std::endl;
        }

        virtual void process() {
            m_a = m_a + 1;
            m_b = m_b + 1;
        }
    };

    /** run virtual members */
    inline void run(base & d, const int N) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            d.process();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        std::cout << "Time: " << diff.count() << std::endl;
    }

} // namespace runtime

namespace compiletime {

    template <typename Derived>
    class base {

        int count;
    public:
        base(): count(0)
        {}

        void print_me() const {
            static_cast<const Derived*>(this)->print_me_();
        }

        void process() {
            static_cast<Derived*>(this)->process_();
        }
    };

    class derived_i: public base<derived_i> {
        using base_type = base<derived_i>;

        int m_value;
    public:
        derived_i(int v)
            : base_type()
            , m_value(v)
        {}

        void print_me_() const {
            std::cout << "CRTP::derived_i"
                      << "< value: "
                      << m_value
                      << std::endl;
        }

        void process_() {
            m_value=m_value*m_value/100000;
        }
    };

    class derived_c: public base<derived_c> {
        using base_type = base<derived_c>;

        double m_a, m_b;
    public:
        derived_c(float a, float b)
            : base_type()
            , m_a(a)
            , m_b(b)
        {}

        void print_me_() const {
            std::cout << "CRTP::derived_c"
                      << "< value: ("
                      << m_a << " + i" << m_b << ")"
                      << std::endl;
        }

        void process_() {
            m_a = m_a + 1;
            m_b = m_b + 1;
        }
    };

    /** run base classes members */
    template <typename T>
    inline void run(T & d, const int N) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            d.process();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        std::cout << "Time: " << diff.count() << std::endl;
    }


    /** Run native members */
    template <typename T>
    inline void run_(T & d, const int N) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            d.process_();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        std::cout << "Time: " << diff.count() << std::endl;
    }


} // namespace compiletime


int main(int argc, char** argv) {

    const int N = atoi(argv[1]);


    {
        runtime::derived_i* c = new runtime::derived_i( 42 );

        c->print_me();

        runtime::run(*c, N);

        c->print_me();
    }

    std::cout << std::endl;

    {
        compiletime::derived_i *d = new compiletime::derived_i( 42 );

        d->print_me();


        compiletime::run(*d, N);

        d->print_me();


        std::cout << "\nCall the native member of derived_i\n";
        d->print_me();

        compiletime::run_(*d, N);

        d->print_me();
    }

    std::cout << std::endl;


    {
        runtime::derived_c* c = new runtime::derived_c( 1.0, 2.0 );

        c->print_me();

        runtime::run(*c, N);

        c->print_me();
    }

    std::cout << std::endl;

    {
        compiletime::derived_c* c = new compiletime::derived_c(1.0, 2.0);

        c->print_me();

        compiletime::run(*c, N);

        c->print_me();

        std::cout << "\nCall the native member of derived_c\n";
        c->print_me();

        compiletime::run_(*c, N);

        c->print_me();
    }

    std::cout << std::endl;

}
