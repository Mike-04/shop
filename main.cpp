//
// Created by White Fox on 3/31/2024.
//

#include "tests.h"
#include "ui.h"
#include "repo.h"
#include "service.h"


int main() {
    test_all();
    Repository repo = Repository();
    Service service = Service(repo);
    UI ui = UI(service);
    ui.run();

    return 0;
}
