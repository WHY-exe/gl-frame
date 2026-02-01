#include "app.h"
#include "util/log.h"
#include "util/dump_client.h"

int main() {
    try {
        dmphelper::Client::Instancitiate(DMP_PATH("./"));

        Log::Config config{};
        Log::Init(config);
        
        LOGI("Hello, Opengl App");
        sandbox::App{}.Run();
    } catch (const std::exception &e) {
        LOGE("common exception: {}", e.what());
    } catch (...) {
        LOGE("An unknown error occoured while app is running ...");
    }
    return 0;
}
