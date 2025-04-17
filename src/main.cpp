#include "../headers/header.hpp"
// #include "../headers/Tick.h"
const size_t tick_interval_ms = 1000;
long long get_current_time_ms() 
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
void tick_loop() 
{
    size_t last_tick_time_ms = get_current_time_ms();

    while (true) {
        size_t current_time_ms = get_current_time_ms();

        // Verifique se o tempo para o próximo tick já passou
        if (current_time_ms - last_tick_time_ms >= tick_interval_ms) {
            // Execute a lógica do tick
            std::cout << "Tick!" << std::endl;

            // Atualize o tempo do último tick
            last_tick_time_ms = current_time_ms;
        }

        // Aguarde o tempo restante até o próximo tick
        size_t time_to_next_tick_ms = (last_tick_time_ms + tick_interval_ms) - current_time_ms;
        if (time_to_next_tick_ms > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(time_to_next_tick_ms));
        }
    }
}

int main()
{
    tick_loop();
    // seconds sec{2};
    // sleep(sec);
    // std::cout << bold << "Hello World" << noBold;

    return 0;
}